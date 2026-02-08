#include "../Include/PCH.h"
#include "BossMonster.h"

BossMonster::BossMonster(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
BossMonster::BossMonster(const GameObject& _RHS) : GameObject(_RHS) {}
BossMonster::~BossMonster() {}

HRESULT BossMonster::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	BossMonster::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID BossMonster::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID BossMonster::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT BossMonster::Component_Initialize() {

	Component_Buffer =		ADD_COMPONENT_RECTTEX;
	Component_Transform =	ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(0.f, 0.f, 1.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(1.f, 1.f, 1.f);
	
	return S_OK;
}
BossMonster* BossMonster::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	BossMonster* MST = new BossMonster(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create BossMonster.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID BossMonster::Free() {

	GameObject::Free();
}