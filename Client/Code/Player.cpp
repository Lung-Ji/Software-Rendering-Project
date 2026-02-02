#include "../Include/PCH.h"
#include "Player.h"
 
Player::Player(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
Player::Player(const GameObject& _RHS)		: GameObject(_RHS)		{}
Player::~Player()													{}

HRESULT Player::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	_defaultSpeed = 10.f;
	_speed = _defaultSpeed;

	return S_OK;
}
INT	Player::Update_GameObject(const _float& _DT) {

	Key_Input(_DT);

	GameObject::Update_GameObject(_DT);

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}
VOID Player::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID Player::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	Component_Texture->Set_Texture(L"»ç°ú1.jpg");

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Player::Component_Initialize() {
	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Extra/Example");
	return S_OK;
}
void Player::Key_Input(const _float& _DT)
{
	_vec3		vDir;
	Component_Transform->Get_Info(INFO_LOOK, &vDir);

	if((KEY_HOLD(DIK_W) && KEY_HOLD(DIK_A)) || (KEY_HOLD(DIK_W) && KEY_HOLD(DIK_D)) ||
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
		Component_Transform->Move_Pos(D3DXVec3Normalize(&vDir, &vDir), _speed, _DT);
	}

	if (KEY_HOLD(DIK_S))
	{
		Component_Transform->Move_Pos(D3DXVec3Normalize(&vDir, &vDir), -_speed, _DT);
	}

	Component_Transform->Get_Info(INFO_RIGHT, &vDir);

	if (KEY_HOLD(DIK_A))
	{
		Component_Transform->Move_Pos(D3DXVec3Normalize(&vDir, &vDir), -_speed, _DT);
	}

	if (KEY_HOLD(DIK_D))
	{
		Component_Transform->Move_Pos(D3DXVec3Normalize(&vDir, &vDir), _speed, _DT);
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