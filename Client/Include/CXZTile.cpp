#include "CXZTile.h"
#include "../Include/PCH.h"

CXZTile::CXZTile(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_fFrame(0.f), m_pBuffer(nullptr), m_pTransform(nullptr), m_pTileInfo(nullptr){}
CXZTile::CXZTile(const GameObject& _RHS) : GameObject(_RHS) {}
CXZTile::~CXZTile() { Free(); }

HRESULT CXZTile::Ready_GameObject(TILE_SIDE eid) {

	if (FAILED(Component_Initialize(eid))) return E_FAIL;
	
	return S_OK;
}
INT	CXZTile::Update_GameObject(const _float& _DT) {

	
	GameObject::Update_GameObject(_DT);
	m_fFrame = 6+ _DT;
	
	if (m_fFrame > 6)
		m_fFrame = 0;
		
		return 0;

}
VOID CXZTile::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

}

VOID CXZTile::Render_GameObject()
{
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	if (m_pTileInfo->Get_TileStateName() == TILE_STATE::STATE_ANIMATION)
	{
		m_pTileInfo->Set_Texture(m_fFrame);
	}else GRPDEV->SetTexture(0, m_pTileInfo->Get_TileTexture());
	if(m_pBuffer!=nullptr)
	m_pBuffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CXZTile::Set_Buffer(TILE_SIDE eid)
{
	switch (eid)
	{
	case TILE_SIDE::TILE_FRONT:
		m_pBuffer = ADD_COMPONENT_TILEFRONT;
		break;
	case TILE_SIDE::TILE_RIGHT:
		m_pBuffer = ADD_COMPONENT_TILERIGHT;
		break;
	case TILE_SIDE::TILE_LEFT:
		m_pBuffer = ADD_COMPONENT_TILELEFT;
		break;
	case TILE_SIDE::TILE_BACK:
		m_pBuffer = ADD_COMPONENT_TILEBACK;
		break;
	case TILE_SIDE::TILE_OTHER:
		m_pBuffer = ADD_COMPONENT_TILE;
		break;
	}
}

HRESULT CXZTile::Component_Initialize(TILE_SIDE eid) {

	m_pTransform = ADD_COMPONENT_TRANSFORM;
	m_pTileInfo  = ADD_COMPONENT_TILEINFO;
	
	switch (eid)
	{
	case TILE_SIDE::TILE_FRONT:
		m_pBuffer = ADD_COMPONENT_TILEFRONT;
		break;
	case TILE_SIDE::TILE_RIGHT:
		m_pBuffer = ADD_COMPONENT_TILERIGHT;
		break;
	case TILE_SIDE::TILE_LEFT:
		m_pBuffer = ADD_COMPONENT_TILELEFT;
		break;
	case TILE_SIDE::TILE_OTHER:
		m_pBuffer = ADD_COMPONENT_TILE;
		break;
	}

	return S_OK;
}

CXZTile* CXZTile::Create(LPDIRECT3DDEVICE9 _GRPDEV, TILE_SIDE eid) {
	
	CXZTile* pCXZTile = new CXZTile(_GRPDEV);
	
	if (FAILED(pCXZTile->Ready_GameObject(eid))) {
		MSG_BOX("Cannot Create CXZTile.");
		Safe_Release(pCXZTile);
		return nullptr;
	}
	
	return pCXZTile;
}
VOID CXZTile::Free() {
	GameObject::Free();
}