#include "../Include/PCH.h"
#include "Monster.h"

Monster::Monster(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)	{}
Monster::Monster(const GameObject& _RHS)	: GameObject(_RHS)		{}
Monster::~Monster()													{}

HRESULT Monster::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	Monster::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Monster::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID Monster::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	Component_Texture->Set_Texture(L"Fire.png");

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Monster::Component_Initialize() {

	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(0.f, 0.f, 1.f);
	Component_Transform->Set_Rotation(20.f, 20.f, 20.f);
	Component_Transform->Set_Scale(2.f, 2.f, 2.f);

	Component_Texture	= ADD_COMPONENT_TEXTURE;
	Component_FSM		= ADD_COMPONENT_FSM;

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Monster");
	Component_FSM->FSM_StateInit(MONSTER_IDLE::GetInstance()->Instance());
	
	return S_OK;
}
Monster* Monster::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Monster* MST = new Monster(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create Monster.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID Monster::Free() {

	MONSTER_IDLE::DestroyInstance();
	MONSTER_ATTACK::DestroyInstance();
	MONSTER_CHASE::DestroyInstance();
	MONSTER_DAMAGED::DestroyInstance();
	MONSTER_DEAD::DestroyInstance();

	GameObject::Free();
}