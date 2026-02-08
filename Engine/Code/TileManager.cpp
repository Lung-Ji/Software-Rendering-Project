#include "TileManager.h"
#include "Buffer.h"
#include "Component.h"

IMPLEMENT_SINGLETON(TileManager)
TileManager::TileManager() : m_eMode(TILEMODE_CHANGE::MODE_END){}
TileManager::~TileManager()
{
	Free();
}

HRESULT TileManager::Add_Tile(GameObject* pObject, _vec3 vPos, TILE_STAGE eStage, TILEMODE_CHANGE eMode, TILE_SIDE eSid, _vec3 PivotHeight)
{
	
	if (pObject == nullptr)
	{
		return E_FAIL;
	}
	//Tile에서 전달받은 위치에 큐브를 생성
	Component* pComponent = pObject->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM);
	Transform* pTransform = dynamic_cast<Transform*>(pComponent);

	if ( eSid != TILE_SIDE::TILE_OTHER)
	{
		_float fHeight(0.f);
		fHeight = (pTransform->Get_Scale()->y) * 0.5f + PivotHeight.y;
		
		pTransform->Set_Pos(vPos.x, fHeight, vPos.z);
	}
	else pTransform->Set_Pos(vPos.x, 0.f, vPos.z);

	m_vecTileBuffer[eStage][eMode].push_back(pObject);

	return S_OK;
}

void TileManager::Delete_Tile(_vec3 vPos, _vec3 Origin, _vec3 vDir)
{
	_float fu, fv, ft;
	//윗면 기준으로 광선쏴서 삭제
	for (size_t i = 0; i < TILE_STAGE::STAGE_END; ++i)
	{
		for (size_t j = 0; j < TILEMODE_CHANGE::MODE_END; ++j)
		{
			for (auto iter = m_vecTileBuffer[i][j].begin(); iter != m_vecTileBuffer[i][j].end();)
			{
				_vec3 vTileLocalPos[4];
				_matrix InverseWorld;

				memcpy(&InverseWorld, dynamic_cast<Transform*>((*iter)->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_World(), sizeof(_matrix));

				vTileLocalPos[0] = { -1.f, 0.f, -1.f }; //좌하단
				vTileLocalPos[1] = { 1.f,  0.f, -1.f };  //우하단
				vTileLocalPos[2] = { -1.f, 0.f,  1.f }; //좌상단
				vTileLocalPos[3] = { 1.f,  0.f,  1.f };  //우상단

				for (int i = 0; i < 4; ++i)
					D3DXVec3TransformCoord(&vTileLocalPos[i], &vTileLocalPos[i], &InverseWorld);

				if (D3DXIntersectTri(&vTileLocalPos[0], &vTileLocalPos[1], &vTileLocalPos[2], &Origin, &vDir, &fu, &fv, &ft) ||
					D3DXIntersectTri(&vTileLocalPos[2], &vTileLocalPos[1], &vTileLocalPos[3], &Origin, &vDir, &fu, &fv, &ft))
				{
					Safe_Release((*iter));
					iter = m_vecTileBuffer[i][j].erase(iter);
				}

				if (iter != m_vecTileBuffer[i][j].end())
					++iter;
			}
		}

	}
	
}

HRESULT TileManager::Update_TileList(const _float& fTimeDetla)
{
	for(size_t i = 0; i < TILE_STAGE::STAGE_END; ++i)
	{
		for (size_t j = 0; j < TILEMODE_CHANGE::MODE_END; ++j)
		{
			for (auto& iter : m_vecTileBuffer[i][j])
				iter->Update_GameObject(fTimeDetla);
		}
	}
	
	
	
	return S_OK;
}

void TileManager::Render_TileList()
{
	for (size_t i = 0; i < TILE_STAGE::STAGE_END; ++i)
	{
		for (size_t j = 0; j < TILEMODE_CHANGE::MODE_END; ++j)
		{
			for (auto& iter : m_vecTileBuffer[i][j])
				iter->Render_GameObject();
		}
	}
}

void TileManager::Save_Tile(HWND g_hWnd)
{
	HANDLE	hFile = CreateFile(L"../../Data/Tile.dat", // 파일 이름이 포함된 경로
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		CREATE_ALWAYS,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MSG_BOX("저장 실패요");
		return;
	}

	DWORD		dwByte(0);
	
	_int             iTilenum		 = 0;
	TILE_SIDE        eTileSide		 = TILE_SIDE::TILE_END;
	TILE_STATE       eTileState		 = TILE_STATE::STATE_END;
	TILEMODE_CHANGE  eTileMode		 = TILEMODE_CHANGE::MODE_END;
	TILE_STAGE		 eTileStage		 = TILE_STAGE::STAGE_END;
	_tchar			 cTileName[256]  = {};
	_vec3		     Info			 = {};
	_vec3			 Scale			 = {};
	_vec3			 Rotation		 = {};
	_tchar			 cPathName[128]  = {};
	_int			 iTileTextureCnt = 0;
	_vec3		     vNextPos	     = {};
	for (size_t i = 0; i < TILE_STAGE::STAGE_END; ++i)
	{
		for (size_t j = 0; j < TILEMODE_CHANGE::MODE_END; ++j)
		{
			for (auto& pTile : m_vecTileBuffer[i][j])
			{

				iTilenum = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileNumber();
				eTileSide = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileSideName();
				eTileState = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileStateName();
				eTileMode = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileMode();
				eTileStage = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileStage();
				iTileTextureCnt = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileTextureNumber();
				vNextPos = dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_NextPos();
				ua_tcscpy_s(cTileName, 128, dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileTextureName().c_str());
				
				Scale = *dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Scale();
				Rotation = *dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation();
				dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Info(INFO_POS, &Info);

				WriteFile(hFile, &Info,			   sizeof(_vec3), &dwByte, NULL);
				WriteFile(hFile, &iTilenum,		   sizeof(_int), &dwByte, NULL);
				WriteFile(hFile, &eTileSide,	   sizeof(TILE_SIDE), &dwByte, NULL);
				WriteFile(hFile, &eTileState,	   sizeof(TILE_STATE), &dwByte, NULL);
				WriteFile(hFile, &eTileMode,	   sizeof(TILEMODE_CHANGE), &dwByte, NULL);
				WriteFile(hFile, &cTileName,	   sizeof(_tchar) * 128, &dwByte, NULL);
				WriteFile(hFile, &Scale,		   sizeof(_vec3), &dwByte, NULL);
				WriteFile(hFile, &Rotation,		   sizeof(_vec3), &dwByte, NULL);
				WriteFile(hFile, &eTileStage,	   sizeof(TILE_STAGE), &dwByte, NULL);
				WriteFile(hFile, &iTileTextureCnt, sizeof(_int), &dwByte, NULL);
				WriteFile(hFile, &vNextPos,		   sizeof(_vec3), &dwByte, NULL);

				
			}
		}
	}
		

	CloseHandle(hFile);
	MSG_BOX("저장 성공요");
}


void TileManager::Reset_TileList()
{
	for (size_t i = 0; i < TILE_STAGE::STAGE_END; ++i)
	{
		for (size_t j = 0; j < TILEMODE_CHANGE::MODE_END; ++j)
		{
			for (auto& iter : m_vecTileBuffer[i][j])
				Safe_Release(iter);
		}
	}
}

void TileManager::Free()
{
	for (size_t i = 0; i < TILE_STAGE::STAGE_END; ++i)
	{
		for (size_t j = 0; j < TILEMODE_CHANGE::MODE_END; ++j)
		{
			for (auto& iter : m_vecTileBuffer[i][j])
				Safe_Release(iter);
		}
	}

}