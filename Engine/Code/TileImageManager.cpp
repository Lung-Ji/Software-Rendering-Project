#include "TileImageManager.h"
#include "Buffer.h"
#include "Component.h"
IMPLEMENT_SINGLETON(TileImageManager)
TileImageManager::TileImageManager() {}
TileImageManager::~TileImageManager()
{
	Free();
}

HRESULT TileImageManager::Add_Tile(GameObject* pObject, _vec3 vPos, TILE_SIDE eTile)
{

	if (pObject == nullptr)
	{
		return E_FAIL;
	}
	//Tile에서 전달받은 위치에 큐브를 생성
	Component* pComponent = pObject->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM);
	Transform* pTransform = dynamic_cast<Transform*>(pComponent);

	switch (eTile)
	{
	case TILE_SIDE::TILE_FRONT:
		pTransform->Set_Pos(vPos.x, vPos.y, vPos.z + 2);
		break;
	case TILE_SIDE::TILE_RIGHT:
		pTransform->Set_Pos(vPos.x + 2, vPos.y, vPos.z);
		break;
	case TILE_SIDE::TILE_LEFT:
		pTransform->Set_Pos(vPos.x - 2, vPos.y, vPos.z);
		break;
	case TILE_SIDE::TILE_BACK:
		pTransform->Set_Pos(vPos.x, vPos.y, vPos.z - 2);
		break;
	case TILE_SIDE::TILE_OTHER:
		pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);
		break;
	}
//	m_vecTileImage.push_back(pObject);

	return S_OK;
}

void TileImageManager::Delete_TileImage(_vec3 vPos, _vec3 Origin, _vec3 vDir)
{
	
}

HRESULT TileImageManager::Update_TileImageList(const _float& fTimeDetla)
{
//	for (auto& iter : m_vecTileImage)
//		iter->Update_GameObject(fTimeDetla);

	return S_OK;
}

void TileImageManager::Render_TileImageList()
{
//	for (auto& iter : m_vecTileImage)
//		iter->Render_GameObject();

}

void TileImageManager::Free()
{
	for (auto& iter : m_vecTileImage)
	{
		Safe_Release(iter);
	}

	m_vecTileImage.clear();
}