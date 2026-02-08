#include "TileInfo.h"

TileInfo::TileInfo(LPDIRECT3DDEVICE9 _GRPDEV) : Component(_GRPDEV), m_iTileNumber(0),
m_eTileState(TILE_STATE::STATE_END), m_bPortal(false), m_iTextureCount(0), m_eTileSide(TILE_SIDE::TILE_END), m_eTileMode(TILEMODE_CHANGE::MODE_END) {
}
TileInfo::TileInfo(const TileInfo& _RHS) : Component(_RHS),  m_eTileSide(_RHS.m_eTileSide), m_bPortal(_RHS.m_bPortal),
m_eTileState(_RHS.m_eTileState), m_eTileMode(_RHS.m_eTileMode), m_pTileName(_RHS.m_pTileName), m_iTileNumber(_RHS.m_iTileNumber) {
		
		

}
TileInfo::~TileInfo() { }

HRESULT TileInfo::Ready_Component() {

	return S_OK;
}
INT	TileInfo::Update_Component(const _float& _DT) {

	
	return 0;
}
VOID TileInfo::LateUpdate_Component(const _float& _DT) {

}

TileInfo* TileInfo::Create(LPDIRECT3DDEVICE9 _GRPDEV) {


	TileInfo* pTileInfo = new TileInfo(_GRPDEV);

	if (FAILED(pTileInfo->Ready_Component())) {
		MSG_BOX("Cannot Create TileInfo.");
		Safe_Release(pTileInfo);
		return nullptr;
	}

	return pTileInfo;
}

Component* TileInfo::Clone() {
	return new TileInfo(*this);
}
VOID TileInfo::Free() {

	Component::Free();
}