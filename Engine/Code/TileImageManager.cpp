#include "TileImageManager.h"
#include "Buffer.h"
#include "Component.h"
IMPLEMENT_SINGLETON(TileImageManager)
TileImageManager::TileImageManager() {}
TileImageManager::~TileImageManager()
{
	Free();
}

HRESULT TileImageManager::Add_TileImage(Texture* pTexture, TILE_IMAGEPAGE eid)
{
	if (m_vecTileImage->size() == TILE_IMAGEPAGE::IMAGEPAGE_END)
	{
		Safe_Release(pTexture);
		return E_FAIL;
	}
	
	m_vecTileImage[eid].push_back(pTexture);

	return S_OK;
}

void TileImageManager::Delete_TileImage(_vec3 vPos, _vec3 Origin, _vec3 vDir)
{
	
}

HRESULT TileImageManager::Update_TileImageList(const _float& fTimeDetla)
{
	return S_OK;
}

void TileImageManager::Render_TileImageList()
{
}

void TileImageManager::Free()
{
	for (size_t i = 0; i < TILE_IMAGEPAGE::IMAGEPAGE_END; ++i)
	{
		for (auto& iter : m_vecTileImage[i])
		{
			Safe_Release(iter);
		}
		m_vecTileImage[i].clear();
	}

	
}