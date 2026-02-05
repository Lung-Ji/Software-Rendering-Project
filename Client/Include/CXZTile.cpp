#include "CXZTile.h"
#include "../Include/PCH.h"

CXZTile::CXZTile(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV),m_pBuffer(nullptr), m_pTexture(nullptr), m_pTransform(nullptr), m_iTileNumber(0), m_eTileSide(TILE_SIDE::TILE_END) {}
CXZTile::CXZTile(const GameObject& _RHS) : GameObject(_RHS) {}
CXZTile::~CXZTile() { Free(); }

HRESULT CXZTile::Ready_GameObject(LPDIRECT3DDEVICE9 _GRPDEV, Engine::TILE_SIDE eId, const _tchar* pName) {

	if (FAILED(Component_Initialize())) return E_FAIL;

	wstring  path = L"../../Resource/Tile";
	wstring WideRootPath = path + L"/"+pName;
	D3DXCreateTextureFromFile(_GRPDEV, WideRootPath.c_str(), (LPDIRECT3DTEXTURE9*)&m_pTexture);
	
	return S_OK;
}
INT	CXZTile::Update_GameObject(const _float& _DT) {

	return GameObject::Update_GameObject(_DT);

}
VOID CXZTile::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

}

VOID CXZTile::Render_GameObject()
{
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	GRPDEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // 확대 시 필터링
	GRPDEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	GRPDEV->SetTexture(0, m_pTexture);
	m_pBuffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

HRESULT CXZTile::Component_Initialize() {

	m_pTransform = ADD_COMPONENT_TRANSFORM;
	//switch (m_eTileSide)
	//{
	//case TILE_SIDE::TILE_FRONT:
	//	m_pBuffer = ADD_COMPONENT_TILEFRONT;
	//	break;
	//case TILE_SIDE::TILE_RIGHT:
	//	m_pBuffer = ADD_COMPONENT_TILERIGHT;
	//	break;
	//case TILE_SIDE::TILE_LEFT:
	//	m_pBuffer = ADD_COMPONENT_TILELEFT;
	//	break;
	//case TILE_SIDE::TILE_BACK:
	//	m_pBuffer = ADD_COMPONENT_TILEBACK;
	//	break;
	//case TILE_SIDE::TILE_OTHER:
	//	m_pBuffer = ADD_COMPONENT_TILE;
	//	break;
	//}
		
	m_pBuffer = ADD_COMPONENT_TILE;

	return S_OK;
}

CXZTile* CXZTile::Create(LPDIRECT3DDEVICE9 _GRPDEV, Engine::TILE_SIDE eId, const _tchar* pName) {
	
	if (pName == nullptr)
		return nullptr;

	CXZTile* pCXZTile = new CXZTile(_GRPDEV);
	
	pCXZTile->Set_TileId(eId);
	pCXZTile->Set_TileName(pName);


	if (FAILED(pCXZTile->Ready_GameObject(_GRPDEV, eId, pName))) {
		MSG_BOX("Cannot Create CXZTile.");
		Safe_Release(pCXZTile);
		return nullptr;
	}
	
	return pCXZTile;
}
VOID CXZTile::Free() {
	Safe_Release(m_pTexture);
	GameObject::Free();
}