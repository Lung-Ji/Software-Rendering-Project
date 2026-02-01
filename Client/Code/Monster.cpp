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
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}
VOID Monster::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID Monster::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	//Component_Texture->Set_Texture(0);

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Monster::Component_Initialize() {

	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;

	
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
	GameObject::Free();
}