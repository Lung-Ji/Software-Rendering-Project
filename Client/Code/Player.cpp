#include "../Include/PCH.h"
#include "Player.h"

Player::Player(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
Player::Player(const GameObject& _RHS)		: GameObject(_RHS)		{}
Player::~Player()													{}

HRESULT Player::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	_pState				= pState::STATE_IDLE;
	_eState				= eState::STATE_STANDING;
	_see				= pSee::SEE_DOWN;
	_defaultSpeed		= 8.f;
	_dashSpeed			= 0.f;
	_dashTime			= 0.f;
	_speed				= 0.f;
	_slideTime			= 0.f;
	_g					= 30.f;
	_frame				= 1;

	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_vec3 cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };
	
	_float angle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&cameraDir, &cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	_cameraAngle = angle / D3DX_PI * 180.f;

	Component_Transform->Rotation(ROT_X, 90.f - _cameraAngle);
	Component_Transform->Set_Pos({ 5.f, 1.f, 5.f });


	Debug = false;

	return S_OK;
}
INT	Player::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	_frameTick += _DT;

	Gravity(_DT);

	switch (_pState)
	{
	case pState::STATE_IDLE:
		IDLE_STATE(_DT);
		break;
	case pState::STATE_DASH:
		break;
	case pState::STATE_ATTACK:
		break;
	case pState::STATE_LANDING :
		break;
	default:
		break;
	}
	

	return 0;
}
VOID Player::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID Player::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	SetGrahpic();

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Player::Component_Initialize() {
	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;
	//Component_FSM		= ADD_COMPONENT_FSM;

	Component_Collider = ADD_COMPONENT_COLLIDER;					// 충돌체 컴포넌트 추가
	Component_Collider->Set_CenterPos(Component_Transform);			// 충돌체가 오브젝트를 따라 다니도록
	Component_Collider->Set_Scale(0.5f, 0.5f, 0.5f);				// 충돌체의 범위 조절

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Player/Stand");
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Player/Run");
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Player/Slide");
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Player/Attack");

	return S_OK;
}
void Player::IDLE_STATE(const _float& _DT)
{
	// Idle_Final_Input(_DT);

	if (KEY_DOWN(DIK_F3)) {	//	마우스 커서 고정 여부 TRUE = 고정, FALSE = 고정 해제
		Debug ? Debug = FALSE : Debug = TRUE;
	}

	if (!Debug)
	{
		_vec3		upDir, rightDir;
		upDir = { 0.f, 0.f, 1.f };
		rightDir = { 1.f, 0.f, 0.f };
		D3DXVec3Normalize(&upDir, &upDir);
		D3DXVec3Normalize(&rightDir, &rightDir);

		//Component_Transform->Get_Info(INFO_LOOK, &vDir);
		if (_speed == 0.f)
		{
			if (_eState != eState::STATE_STANDING)
			{
				_eState = eState::STATE_STANDING;
				//_frame = 1;
			}
		}

		bool mouseLB = KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80;

		if (!mouseLB && _frame > 8)
			_frame = 1;

		if (mouseLB)
		{
			POINT point;
			GetCursorPos(&point);
			ScreenToClient(hWnd, &point);

			_vec2 playerPos = { WINCX / 2 , WINCY / 2 };

			if (point.x <= playerPos.x && point.y >= playerPos.y)
				_eState = eState::STATE_ATTACK_LD;
			else if(point.x > playerPos.x && point.y > playerPos.y)
				_eState = eState::STATE_ATTACK_RD;
			else if (point.x < playerPos.x && point.y < playerPos.y)
				_eState = eState::STATE_ATTACK_LU;
			else if (point.x >= playerPos.x && point.y <= playerPos.y)
				_eState = eState::STATE_ATTACK_RU;

		}
			
		Component_Transform->Set_Scale({ 1.f, 1.f, 1.f });

		if (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_A))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_BACK_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_BACK_RD;
				break;
			case eState::STATE_RUN_LU:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_LU;
				_see = pSee::SEE_LU;
				break;
			}

			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);

			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_LU;

			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);


		}
		else if (KEY_HOLD(DIK_S) && KEY_HOLD(DIK_A))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_BACK_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_BACK_RD;
				break;
			case eState::STATE_RUN_LD:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_LD;
				_see = pSee::SEE_LD;
				break;
			}

			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);

			if(mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_LD;

			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);

		}
		else if (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_D))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_BACK_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_BACK_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_RD;
				break;
			case eState::STATE_RUN_RU:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_RU;
				_see = pSee::SEE_RU;
			}

			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);

			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_RU;

			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);

		}
		else if (KEY_HOLD(DIK_S) && KEY_HOLD(DIK_D))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_BACK_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_BACK_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_RD;
				break;
			case eState::STATE_RUN_RD:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_RD;
				_see = pSee::SEE_RD;
			}

			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);

			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_RD;

			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);

		}
		else if (KEY_HOLD(DIK_W))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_BACK_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_BACK_RD;
				break;
			case eState::STATE_RUN_UP:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_UP;
				_see = pSee::SEE_UP;
				break;
			}

			_speed = _defaultSpeed;
			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_UP;
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);

		}

		else if (KEY_HOLD(DIK_S))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_BACK_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_BACK_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_RD;
				break;
			case eState::STATE_RUN_DOWN:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_DOWN;
				_see = pSee::SEE_DOWN;
			}

			_speed = _defaultSpeed;
			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_DOWN;
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
		}

		else if (KEY_HOLD(DIK_A))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_BACK_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_BACK_RD;
				break;
			case eState::STATE_RUN_LEFT:
				break;
			default:
				_eState = eState::STATE_RUN_LEFT;
				_see = pSee::SEE_LEFT;
			}

			_speed = _defaultSpeed;
			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_LEFT;
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);

		}
		else if (KEY_HOLD(DIK_D))
		{
			switch (_eState)
			{
			case eState::STATE_ATTACK_LU:
				_eState = eState::STATE_ATTACK_RUN_BACK_LU;
				break;
			case eState::STATE_ATTACK_RU:
				_eState = eState::STATE_ATTACK_RUN_RU;
				break;
			case eState::STATE_ATTACK_LD:
				_eState = eState::STATE_ATTACK_RUN_BACK_LD;
				break;
			case eState::STATE_ATTACK_RD:
				_eState = eState::STATE_ATTACK_RUN_RD;
				break;
			case eState::STATE_RUN_RIGHT:
				break;
			default:
				//_frame = 1;
				_eState = eState::STATE_RUN_RIGHT;
				_see = pSee::SEE_RIGHT;
			}

			_speed = _defaultSpeed;
			if (mouseLB)
				_speed *= 0.5f;
			else
				_eState = eState::STATE_RUN_RIGHT;
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
		}
		else
		{
			if (_speed > 0.f)
			{
				if (_slideTime < 0.001f && _speed <= _defaultSpeed * 0.5) {
					_speed = 0.f; _slideTime = 0.f;
				}

				_slideTime += _DT;
				_speed -= _DT * _g;
				if (_speed < 0.f){
					_speed = 0.f;
					_slideTime = 0.f;
				}
					
				float tempSpeed = _speed;
				switch (_see)
				{
				case pSee::SEE_LEFT :
					_eState = eState::STATE_STANDING;
					Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
					break;
				case pSee::SEE_RIGHT:
					_eState = eState::STATE_STANDING;
					Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
					break;
				case pSee::SEE_UP:
					_eState = eState::STATE_STANDING;
					Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
					break;
				case pSee::SEE_DOWN:
					_eState = eState::STATE_STANDING;
					Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
					break;
				case pSee::SEE_LU:
					_eState = eState::STATE_STANDING;
					tempSpeed = tempSpeed * cos(D3DX_PI * 0.25f);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -tempSpeed, _DT);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), tempSpeed, _DT);
					break;
				case pSee::SEE_RU:
					_eState = eState::STATE_STANDING;
					tempSpeed = tempSpeed * cos(D3DX_PI * 0.25f);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), tempSpeed, _DT);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), tempSpeed, _DT);
					break;
				case pSee::SEE_LD:
					_eState = eState::STATE_STANDING;
					tempSpeed = tempSpeed * cos(D3DX_PI * 0.25f);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -tempSpeed, _DT);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -tempSpeed, _DT);
					break;
				case pSee::SEE_RD:
					_eState = eState::STATE_STANDING;
					tempSpeed = tempSpeed * cos(D3DX_PI * 0.25f);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), tempSpeed, _DT);
					Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -tempSpeed, _DT);
					break;
				default:
					_speed = 0.f;
					break;
				}
			}
		}
	}
}

void Player::DASH_STATE(const _float& _DT)
{
	_vec3		upDir, rightDir;
	upDir = { 0.f, 0.f, 1.f };
	rightDir = { 1.f, 0.f, 0.f };
	D3DXVec3Normalize(&upDir, &upDir);
	D3DXVec3Normalize(&rightDir, &rightDir);

	if (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_A)) {
		_eState = eState::STATE_DASH_LU;
		_see = pSee::SEE_LU;

		_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);

		Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
		Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
	}
	else if (KEY_HOLD(DIK_A))
	{
		_eState = eState::STATE_DASH_LEFT;
		_see = pSee::SEE_LEFT;
		_speed = _defaultSpeed;
		Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
	}
	else if (KEY_HOLD(DIK_D))
	{
		_eState = eState::STATE_DASH_RIGHT;
		_see = pSee::SEE_RIGHT;
		_speed = _defaultSpeed;
		Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
	}
	else if (KEY_HOLD(DIK_U))
	{
		_eState = eState::STATE_DASH_UP;
		_see = pSee::SEE_UP;
		_speed = _defaultSpeed;
		Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
	}
	else if (KEY_HOLD(DIK_S))
	{
		_eState = eState::STATE_DASH_DOWN;
		_see = pSee::SEE_DOWN;
		_speed = _defaultSpeed;
		Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
	}

	switch (_eState)
	{

	}
	if (_dashSpeed <= 0)
		_pState = pState::STATE_IDLE;
}

void Player::ATTACK_STATE(const _float& _DT)
{
}

void Player::Idle_Final_Input(const _float& _DT)
{
	if (KEY_DOWN(DIK_LSHIFT)) {
		_pState = pState::STATE_DASH;
		_frame = 1;

	}
}

void Player::Gravity(const _float& _DT)
{
	//_vec3 pos;
	//Component_Transform->Get_Info(INFO_POS, &pos);
	//float tempy = pos.y;

	//if (pos.y > 1.f || _isJump)
	//{
	//	_jumpSpeed -= _g;
	//	tempy += _jumpSpeed * _DT;
	//	_vec3		vDir;
	//	Component_Transform->Get_Info(INFO_UP, &vDir);

	//	Component_Transform->Move_Pos(D3DXVec3Normalize(&vDir, &vDir), _jumpSpeed, _DT);
	//}

	//if (tempy < 1.f)
	//{
	//	_isJump = false;
	//	_jumpSpeed = 0.f;

	//	Component_Transform->Set_Pos({ pos.x, 1.f, pos.z });
	//}
}
void Player::SetGrahpic()
{
	TCHAR FileName[128] = L"";

	Component_Transform->Set_Scale({ 2.f, 2.f, 2.f });

	switch (_eState)
	{
	case eState::STATE_STANDING :
		switch (_see)
		{
		case pSee::SEE_DOWN :
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Player_Stand_Down%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_Down_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_UP:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Player_Stand_UP%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_Up_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_RIGHT:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"StandRS0%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_Right_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_LEFT:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Player_Stand_Left%d.png", _frame);
			}
			else{
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_Left_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_LU:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Player_Stand_LT%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_LU_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_RU:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Player_Stand_RT%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_RU_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_LD:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Stand_LB0%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_LD_Slide%d.png", _frame);
			}
			break;
		case pSee::SEE_RD:
			if (_speed <= 0) {
				if (_frame > 8) _frame = 1;
				wsprintfW(FileName, L"Stand_RB0%d.png", _frame);
			}
			else {
				if (_frame > 4) _frame = 1;
				if (_slideTime < 0.1f) _frame = 1;
				wsprintfW(FileName, L"Player_RD_Slide%d.png", _frame);
			}
			break;
		}
		if (_speed <= 0)
			Anim(FileName, 0.1f, 8);
		else
			Anim(FileName, 0.1f, 4);
		
		break;
	case eState::STATE_RUN_UP:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_UP%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;
	case eState::STATE_RUN_DOWN:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_Down%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;
	case eState::STATE_RUN_LEFT:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_LEFT%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;
	case eState::STATE_RUN_LU:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_LU%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;

	case eState::STATE_RUN_LD:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_LD%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;

	case eState::STATE_RUN_RIGHT:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_Right%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;

	case eState::STATE_RUN_RU:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"RTRun0%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;

	case eState::STATE_RUN_RD:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Run_RD%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;

	case eState::STATE_ATTACK_LU:
		wsprintfW(FileName, L"Player_Attack_Stand_LU%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;

	case eState::STATE_ATTACK_LD:
		wsprintfW(FileName, L"Player_Attack_Stand_LD%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;
	case eState::STATE_ATTACK_RU:
		wsprintfW(FileName, L"Player_Attack_Stand_RU%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;

	case eState::STATE_ATTACK_RD:
		wsprintfW(FileName, L"Player_Attack_Stand_RD%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;
	case eState::STATE_ATTACK_RUN_LU:
		wsprintfW(FileName, L"Player_Attack_LU%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;
	case eState::STATE_ATTACK_RUN_LD:
		wsprintfW(FileName, L"Player_Attack_LD%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;
	case eState::STATE_ATTACK_RUN_RU:
		wsprintfW(FileName, L"Player_Attack_RU%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;
	case eState::STATE_ATTACK_RUN_RD:
		wsprintfW(FileName, L"Player_Attack_RD%d.png", _frame);
		Anim(FileName, 0.1f, 10);
		break;
	case eState::STATE_ATTACK_RUN_BACK_LU:
		wsprintfW(FileName, L"Player_Attack_LU%d.png", _frame);
		Anim(FileName, 0.1f, 10, true);
		break;
	case eState::STATE_ATTACK_RUN_BACK_LD:
		wsprintfW(FileName, L"Player_Attack_LD%d.png", _frame);
		Anim(FileName, 0.1f, 10, true);
		break;
	case eState::STATE_ATTACK_RUN_BACK_RU:
		wsprintfW(FileName, L"Player_Attack_RU%d.png", _frame);
		Anim(FileName, 0.1f, 10, true);
		break;
	case eState::STATE_ATTACK_RUN_BACK_RD:
		if (_frame > 10) _frame = 1;
		wsprintfW(FileName, L"Player_Attack_RD%d.png", _frame);
		Anim(FileName, 0.1f, 10, true);
		break;
	default:
		if (_frame > 8) _frame = 1;
		wsprintfW(FileName, L"Player_Stand_Down%d.png", _frame);
		Anim(FileName, 0.1f, 8);
		break;
	}
}
void Player::Anim(TCHAR FileName[128], float delay, int maxIdx, bool reverse)
{
	Component_Texture->Set_Texture(FileName);

	if (!reverse)
	{
		if (_frameTick > delay)
		{
			if (++_frame > maxIdx)
				_frame = 1;

			_frameTick = 0.f;
		}
	}
	else
	{
		if (_frameTick > delay)
		{
			if (--_frame < 1)
				_frame = maxIdx;

			_frameTick = 0.f;
		}
	}

}
Player* Player::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Player* PLAYER = new Player(_GRPDEV);
	if (FAILED(PLAYER->Ready_GameObject())) {
		MSG_BOX("Cannot Create Player.");
		Safe_Release(PLAYER);
		return nullptr;
	}
	return PLAYER;
}
VOID	Player::Free() {
	GameObject::Free();
}