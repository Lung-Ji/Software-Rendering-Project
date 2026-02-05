#include "CubeTile.h"
#include "../Include/PCH.h"

CubeTile::CubeTile(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV),m_pBuffer(nullptr),m_pTransform(nullptr), m_eTileState(TILE_STATE::STATE_END),m_iTileNumber(0), m_eTileSide(TILE_SIDE::TILE_END){}
CubeTile::CubeTile(const GameObject& _RHS) : GameObject(_RHS) {}
CubeTile::~CubeTile() { Free(); }

HRESULT CubeTile::Ready_GameObject() {

	if (FAILED(Component_Initialize())) return E_FAIL;

	return S_OK;
}
INT	CubeTile::Update_GameObject(const _float& _DT) {

	return GameObject::Update_GameObject(_DT);

}
VOID CubeTile::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

}

VOID CubeTile::Render_GameObject()
{
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	m_pBuffer->Render_Buffer();

}

HRESULT CubeTile::Component_Initialize() {

	m_pBuffer = ADD_COMPONENT_CUBE;
	m_pTransform = ADD_COMPONENT_TRANSFORM;

	return S_OK;
}

CubeTile* CubeTile::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	CubeTile* pCubeTile = new CubeTile(_GRPDEV);
	if (FAILED(pCubeTile->Ready_GameObject())) {
		MSG_BOX("Cannot Create CubeTile.");
		Safe_Release(pCubeTile);
		return nullptr;
	}
	return pCubeTile;
}
VOID CubeTile::Free() {
	GameObject::Free();
}