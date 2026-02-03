#include "TileManager.h"
#include "Buffer.h"
#include "Component.h"
IMPLEMENT_SINGLETON(TileManager)
TileManager::TileManager() : m_eMode(TILEMODE_CHANGE::MODE_END){}
TileManager::~TileManager()
{
	Free();
}

HRESULT TileManager::Add_Tile(GameObject* pObject, _vec3 vPos, TILE_SIDE eTile)
{
	
	if (pObject == nullptr)
	{
		return E_FAIL;
	}
	//Tile에서 전달받은 위치에 큐브를 생성
	Component* pComponent = pObject->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM);
	Transform* pTransform = dynamic_cast<Transform*>(pComponent);
	if (m_eMode == TILEMODE_CHANGE::MODE_TILE)
	{
		//switch (eTile)
		//{
		//case TILE_SIDE::TILE_FRONT:
		//	pTransform->Set_Pos(vPos.x, 1.f, vPos.z);
		//	break;
		//case TILE_SIDE::TILE_RIGHT:
		//	pTransform->Set_Pos(vPos.x, 1.f, vPos.z);
		//	break;
		//case TILE_SIDE::TILE_LEFT:
		//	pTransform->Set_Pos(vPos.x, 1.f, vPos.z);
		//	break;
		//case TILE_SIDE::TILE_BACK:
		//	pTransform->Set_Pos(vPos.x, 1.f, vPos.z);
		//	break;
		//case TILE_SIDE::TILE_OTHER:
		//	pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);
		//	break;
		//}
		pTransform->Set_Pos(vPos.x, 0.f, vPos.z);
		m_vecTileBuffer.push_back(pObject);
	}
	else
	{
		pTransform->Set_Pos(vPos.x, 1.f, vPos.z);
		m_vecCubeBuffer.push_back(pObject);
	}
	return S_OK;
}

void TileManager::Delete_Tile(_vec3 vPos, _vec3 Origin, _vec3 vDir)
{
	_float fu, fv, ft;
	//윗면 기준으로 광선쏴서 삭제

	switch (m_eMode)
	{
		case TILEMODE_CHANGE::MODE_TILE:
		{
			for (auto iter = m_vecTileBuffer.begin(); iter != m_vecTileBuffer.end();)
			{
				_vec3 vTileLocalPos[4];
				_matrix InverseWorld;

				memcpy(&InverseWorld, dynamic_cast<Transform*>((*iter)->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_World(), sizeof(_matrix));

				vTileLocalPos[0] = { -1.f, 1.f, -1.f }; //좌하단
				vTileLocalPos[1] = { 1.f, 1.f, -1.f };  //우하단
				vTileLocalPos[2] = { -1.f, 1.f,  1.f }; //좌상단
				vTileLocalPos[3] = { 1.f, 1.f,  1.f };  //우상단


				for (int i = 0; i < 4; ++i)
					D3DXVec3TransformCoord(&vTileLocalPos[i], &vTileLocalPos[i], &InverseWorld);

				if (D3DXIntersectTri(&vTileLocalPos[0], &vTileLocalPos[1], &vTileLocalPos[2], &Origin, &vDir, &fu, &fv, &ft) ||
					D3DXIntersectTri(&vTileLocalPos[2], &vTileLocalPos[1], &vTileLocalPos[3], &Origin, &vDir, &fu, &fv, &ft))
				{
					Safe_Release((*iter));
					iter = m_vecTileBuffer.erase(iter);
				}

				if (iter != m_vecTileBuffer.end())
					++iter;
			}
			break;
		}case TILEMODE_CHANGE::MODE_CUBE:
		{
			for (auto iter = m_vecCubeBuffer.begin(); iter != m_vecCubeBuffer.end();)
			{
				_vec3 vTileLocalPos[4];
				_matrix InverseWorld;

				memcpy(&InverseWorld, dynamic_cast<Transform*>((*iter)->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_World(), sizeof(_matrix));

				vTileLocalPos[0] = { -1.f, 1.f, -1.f }; //좌하단
				vTileLocalPos[1] = { 1.f, 1.f, -1.f };  //우하단
				vTileLocalPos[2] = { -1.f, 1.f,  1.f }; //좌상단
				vTileLocalPos[3] = { 1.f, 1.f,  1.f };  //우상단


				for (int i = 0; i < 4; ++i)
					D3DXVec3TransformCoord(&vTileLocalPos[i], &vTileLocalPos[i], &InverseWorld);

				if (D3DXIntersectTri(&vTileLocalPos[0], &vTileLocalPos[1], &vTileLocalPos[2], &Origin, &vDir, &fu, &fv, &ft) ||
					D3DXIntersectTri(&vTileLocalPos[2], &vTileLocalPos[1], &vTileLocalPos[3], &Origin, &vDir, &fu, &fv, &ft))
				{
					Safe_Release((*iter));
					iter = m_vecCubeBuffer.erase(iter);
				}
				if (iter != m_vecCubeBuffer.end())
					++iter;
			}
			break;
		}
	}
}

HRESULT TileManager::Update_TileList(const _float& fTimeDetla)
{
	for (auto& iter : m_vecTileBuffer)
		iter->Update_GameObject(fTimeDetla);

	for (auto& iter : m_vecCubeBuffer)
		iter->Update_GameObject(fTimeDetla);

	
	return S_OK;
}

void TileManager::Render_TileList()
{
	for (auto& iter : m_vecTileBuffer)
		iter->Render_GameObject();

	for (auto& iter : m_vecCubeBuffer)
		iter->Render_GameObject();
}

void TileManager::Free()
{
	for (auto& iter : m_vecTileBuffer)
	{
		Safe_Release(iter);
	}
	for (auto& iter : m_vecCubeBuffer)
	{
		Safe_Release(iter);
	}
	m_vecCubeBuffer.clear();
	m_vecTileBuffer.clear();
}