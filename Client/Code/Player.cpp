#include "../Include/PCH.h"
#include "Player.h"

Player::Player(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
Player::Player(const GameObject& _RHS)		: GameObject(_RHS)		{}
Player::~Player()													{}

HRESULT Player::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	_state = pState::STATE_STANDING;
	_see = pSee::SEE_DOWN;

	_defaultSpeed = 12.f;
	_speed = 0.f;

	_isJump = false;
	_defultJumpSpeed = 50.f;
	_jumpSpeed = 0.f;
	_g = 0.5f;
	_frame = 1;

	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_vec3 cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };
	
	_float angle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&cameraDir, &cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	angle = angle / D3DX_PI * 180.f;

	Component_Transform->Set_Scale({ 1.f, 1.f, 1.f });
	Component_Transform->Rotation(ROT_Y, 45.f);
	Component_Transform->Rotation(ROT_X, angle);
	Component_Transform->Set_Pos({ 5.f, 1.f, 5.f });

	Debug = false;

	return S_OK;
}
INT	Player::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	_frameTick += _DT;

	Gravity(_DT);
	Key_Input(_DT);

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

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Extra/Example");
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Player/Stand");
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Player/Run");

	return S_OK;
}
void Player::Key_Input(const _float& _DT)
{
	if (KEY_DOWN(DIK_F3)) {	//	마우스 커서 고정 여부 TRUE = 고정, FALSE = 고정 해제
		Debug ? Debug = FALSE : Debug = TRUE;
	}

	if (!Debug)
	{
		_vec3		upDir, rightDir;
		upDir = { 1.f, 0.f, 1.f };
		rightDir = { 1.f, 0.f, -1.f };
		D3DXVec3Normalize(&upDir, &upDir);
		D3DXVec3Normalize(&rightDir, &rightDir);

		//Component_Transform->Get_Info(INFO_LOOK, &vDir);
		if(_speed == 0.f)
			_state = pState::STATE_STANDING;
		Component_Transform->Set_Scale({ 1.f, 1.f, 1.f });

		if (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_A))
		{
			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
			if (_state != pState::STATE_RUN_LU)
			{
				_frame = 1;
				_state = pState::STATE_RUN_LU;
				_see = pSee::SEE_LU;
			}

		}
		else if (KEY_HOLD(DIK_S) && KEY_HOLD(DIK_A))
		{
			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
			if (_state != pState::STATE_RUN_LD)
			{
				_frame = 1;
				_state = pState::STATE_RUN_LD;
				_see = pSee::SEE_LD;
			}
		}
		else if (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_D))
		{
			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
			if (_state != pState::STATE_RUN_RU)
			{
				_frame = 1;
				_state = pState::STATE_RUN_RU;
				_see = pSee::SEE_RU;
			}
		}
		else if (KEY_HOLD(DIK_S) && KEY_HOLD(DIK_D))
		{
			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
			if (_state != pState::STATE_RUN_RD)
			{
				_frame = 1;
				_state = pState::STATE_RUN_RD;
				_see = pSee::SEE_RD;
			}
		}
		else if (KEY_HOLD(DIK_W))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
			_speed = _defaultSpeed;
			if (_state != pState::STATE_RUN_UP)
			{
				_frame = 1;
				_state = pState::STATE_RUN_UP;
				_see = pSee::SEE_UP;
			}
		}

		else if (KEY_HOLD(DIK_S))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
			_speed = _defaultSpeed;
			if (_state != pState::STATE_RUN_DOWN)
			{
				_frame = 1;
				_state = pState::STATE_RUN_DOWN;
				_see = pSee::SEE_DOWN;
			}
		}

		else if (KEY_HOLD(DIK_A))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
			_speed = _defaultSpeed;
			if (_state != pState::STATE_RUN_LEFT)
			{
				_frame = 1;
				_state = pState::STATE_RUN_LEFT;
				_see = pSee::SEE_LEFT;
			}
		}
		else if (KEY_HOLD(DIK_D))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
			_speed = _defaultSpeed;
			if (_state != pState::STATE_RUN_RIGHT)
			{
				_frame = 1;
				_state = pState::STATE_RUN_RIGHT;
				_see = pSee::SEE_RIGHT;
			}
		}
		else
		{
			_speed = 0.f;
		}
		//if (KEY_DOWN(DIK_C) && !_isJump)
		//{
		//	_isJump = true;
		//	_jumpSpeed = _defaultSpeed;
		//}
	}

}

void Player::Gravity(const _float& _DT)
{
	_vec3 pos;
	Component_Transform->Get_Info(INFO_POS, &pos);
	float tempy = pos.y;

	if (pos.y > 1.f || _isJump)
	{
		_jumpSpeed -= _g;
		tempy += _jumpSpeed * _DT;
		_vec3		vDir;
		Component_Transform->Get_Info(INFO_UP, &vDir);

		Component_Transform->Move_Pos(D3DXVec3Normalize(&vDir, &vDir), _jumpSpeed, _DT);
	}

	if (tempy < 1.f)
	{
		_isJump = false;
		_jumpSpeed = 0.f;

		Component_Transform->Set_Pos({ pos.x, 1.f, pos.z });
	}
}
void Player::SetGrahpic()
{
	TCHAR FileName[128] = L"";

	_vec3 size = { 0.44f, 1.f, 1.f };
	size *= 1.2;

	switch (_state)
	{
	case pState::STATE_STANDING :
		Component_Transform->Set_Scale(size);

		switch (_see)
		{
		case pSee::SEE_DOWN :
			wsprintfW(FileName, L"Spr_Yeon_Stand_000_0%d.png", _frame);
			break;
		case pSee::SEE_UP:
			wsprintfW(FileName, L"Spr_Yeon_Stand_180_0%d.png", _frame);
			break;
		case pSee::SEE_RIGHT:
			wsprintfW(FileName, L"Spr_Yeon_Stand_095_0%d.png", _frame);
			break;
		case pSee::SEE_LEFT:
			wsprintfW(FileName, L"Spr_Yeon_Stand_090_0%d.png", _frame);
			break;
		case pSee::SEE_LU:
			wsprintfW(FileName, L"Spr_Yeon_Stand_135_0%d.png", _frame);
			break;
		case pSee::SEE_RU:
			wsprintfW(FileName, L"Spr_Yeon_Stand_130_0%d.png", _frame);
			break;
		case pSee::SEE_LD:
			wsprintfW(FileName, L"Spr_Yeon_Stand_045_0%d.png", _frame);
			break;
		case pSee::SEE_RD:
			wsprintfW(FileName, L"Spr_Yeon_Stand_040_0%d.png", _frame);
			break;
		}

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;
	case pState::STATE_RUN_UP:
		Component_Transform->Set_Scale(size);

		wsprintfW(FileName, L"Spr_Yeon_Run_180_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;
	case pState::STATE_RUN_DOWN:
		Component_Transform->Set_Scale(size);

		wsprintfW(FileName, L"Spr_Yeon_Run_000_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	case pState::STATE_RUN_LEFT:
		wsprintfW(FileName, L"Spr_Yeon_Run_090_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	case pState::STATE_RUN_LU:
		wsprintfW(FileName, L"Spr_Yeon_Run_135_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	case pState::STATE_RUN_LD:
		wsprintfW(FileName, L"Spr_Yeon_Run_045_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	case pState::STATE_RUN_RIGHT:
		wsprintfW(FileName, L"Spr_Yeon_Run_080_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	case pState::STATE_RUN_RU:
		wsprintfW(FileName, L"Spr_Yeon_Run_130_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	case pState::STATE_RUN_RD:
		wsprintfW(FileName, L"Spr_Yeon_Run_040_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;

	default:
		wsprintfW(FileName, L"Spr_Yeon_Stand_000_0%d.png", _frame);

		Component_Texture->Set_Texture(FileName);

		if (_frameTick > 0.1f)
		{
			if (++_frame > 8)
				_frame = 1;

			_frameTick = 0.f;
		}
		break;
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