#include "../Include/PCH.h"
#include "Player.h"

Player::Player(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
Player::Player(const GameObject& _RHS)		: GameObject(_RHS)		{}
Player::~Player()													{}

HRESULT Player::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	_defaultSpeed = 15.f;
	_speed = _defaultSpeed;

	_isJump = false;
	_defultJumpSpeed = 50.f;
	_jumpSpeed = 0.f;
	_g = 0.5f;

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

	Component_Texture->Set_Texture(L"사과1.jpg");

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Player::Component_Initialize() {
	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;
	//Component_FSM		= ADD_COMPONENT_FSM;

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Extra/Example");

	return S_OK;
}
void Player::Key_Input(const _float& _DT)
{

	if (!Debug)
	{
		_vec3		upDir, rightDir;
		upDir = { 1.f, 0.f, 1.f };
		rightDir = { 1.f, 0.f, -1.f };
		D3DXVec3Normalize(&upDir, &upDir);
		D3DXVec3Normalize(&rightDir, &rightDir);

		//Component_Transform->Get_Info(INFO_LOOK, &vDir);

		if ((KEY_HOLD(DIK_W) && KEY_HOLD(DIK_A)) || (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_D)) ||
			(KEY_HOLD(DIK_S) && KEY_HOLD(DIK_A)) || (KEY_HOLD(DIK_S) && KEY_HOLD(DIK_D)))
		{
			_speed = _defaultSpeed * cos(D3DX_PI * 0.25f);
		}
		else
		{
			_speed = _defaultSpeed;
		}

		if (KEY_HOLD(DIK_W))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), _speed, _DT);
		}

		if (KEY_HOLD(DIK_S))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&upDir, &upDir), -_speed, _DT);
		}

		if (KEY_HOLD(DIK_A))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), -_speed, _DT);
		}

		if (KEY_HOLD(DIK_D))
		{
			Component_Transform->Move_Pos(D3DXVec3Normalize(&rightDir, &rightDir), _speed, _DT);
		}
		//if (KEY_DOWN(DIK_C) && !_isJump)
		//{
		//	_isJump = true;
		//	_jumpSpeed = _defaultSpeed;
		//}
	}
	


	if (KEY_DOWN(DIK_P)) {	//	마우스 커서 고정 여부 TRUE = 고정, FALSE = 고정 해제
		Debug ? Debug = FALSE : Debug = TRUE;
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