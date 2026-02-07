#include "../Include/PCH.h"
#include "NPC.h"

NPC::NPC(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)	{}
NPC::NPC(const GameObject& _RHS)	: GameObject(_RHS)		{}
NPC::~NPC()													{}

HRESULT NPC::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	NPC::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID NPC::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID NPC::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	Component_Texture->Set_Texture(0);

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT NPC::Component_Initialize() {

	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;

	return S_OK;
}
NPC* NPC::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	NPC* NPN = new NPC(_GRPDEV);
	if (FAILED(NPN->Ready_GameObject())) {
		MSG_BOX("Cannot Create NPC.");
		Safe_Release(NPN);
		return nullptr;
	}
	return NPN;
}
VOID NPC::Free() {
	GameObject::Free();
}