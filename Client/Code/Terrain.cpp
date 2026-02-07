#include "../Include/PCH.h"
#include "Terrain.h"

Terrain::Terrain(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Terrain::Terrain(const GameObject& _RHS) : GameObject(_RHS) {}
Terrain::~Terrain() {}

HRESULT Terrain::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	Terrain::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}
VOID Terrain::LateUpdate_GameObject(const _float& _DT) {
	//GameObject::LateUpdate_GameObject(_DT);
}
VOID Terrain::Render_GameObject() {

	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, StaticTexture);

	Component_Buffer->Render_Buffer();
	GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
HRESULT Terrain::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_TERRAIN;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture = ADD_COMPONENT_TEXTURE;

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Extra/Example");

	StaticTexture = Component_Texture->Find_Texture(L"Tile01.tga");
	return S_OK;
}
Terrain* Terrain::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Terrain* TRR = new Terrain(_GRPDEV);
	if (FAILED(TRR->Ready_GameObject())) {
		MSG_BOX("Cannot Create Terrain.");
		Safe_Release(TRR);
		return nullptr;
	}
	return TRR;
}
VOID Terrain::Free() {
	GameObject::Free();
}