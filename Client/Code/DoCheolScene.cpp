#include "../Include/PCH.h"
#include "DoCheolScene.h"

DoCheolScene::DoCheolScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
DoCheolScene::~DoCheolScene() {}
HRESULT	DoCheolScene::Ready_Scene() {
	Scene::Ready_Scene();

	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);

	ResourceManager::GetInstance()->GlobalImport_Texture(GRPDEV, L"../../Tile");
	Ready_GameLogic_Layer(L"GameLogic_Layer");

	{
		HANDLE	hFile = CreateFile(L"../../Data/Tile.dat", // 파일 이름이 포함된 경로
			GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
			NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
			NULL,				// 보안 속성(기본값인 경우 NULL)
			OPEN_EXISTING,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
			FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
			NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MSG_BOX("로드 실패");
			return E_FAIL;
		}

		DWORD	dwByte(0);		// eof 역할
		_int             iTilenum = 0;
		TILE_SIDE        eTileSide = TILE_SIDE::TILE_END;
		TILE_STATE       eTileState = TILE_STATE::STATE_END;
		TILEMODE_CHANGE  eTileMode = TILEMODE_CHANGE::MODE_END;
		TILE_STAGE	     eTileStage = TILE_STAGE::STAGE_END;
		_tchar			 cTileName[128] = {};
		_vec3		     Info = {};
		_vec3			 Scale = {};
		_vec3			 Rotation = {};
		_tchar			 cPathName[128] = {};
		_int		     iTileTextureCnt = 0;
		_vec3			 vNextPos = {};
		_bool		     bAni = false;
		UvXY				 uv = {};
		TILE_SPAWNER		eSpawn = TILE_SPAWNER::SPAWN_END;
		TileManager::GetInstance()->Render_TileList();
		while (true)
		{
			ReadFile(hFile, &Info, sizeof(_vec3), &dwByte, NULL);
			ReadFile(hFile, &iTilenum, sizeof(_int), &dwByte, NULL);
			ReadFile(hFile, &eTileSide, sizeof(TILE_SIDE), &dwByte, NULL);
			ReadFile(hFile, &eTileState, sizeof(TILE_STATE), &dwByte, NULL);
			ReadFile(hFile, &eTileMode, sizeof(TILEMODE_CHANGE), &dwByte, NULL);
			ReadFile(hFile, &cTileName, sizeof(_tchar) * 128, &dwByte, NULL);
			ReadFile(hFile, &Scale, sizeof(_vec3), &dwByte, NULL);
			ReadFile(hFile, &Rotation, sizeof(_vec3), &dwByte, NULL);
			ReadFile(hFile, &eTileStage, sizeof(TILE_STAGE), &dwByte, NULL);
			ReadFile(hFile, &iTileTextureCnt, sizeof(_int), &dwByte, NULL);
			ReadFile(hFile, &vNextPos, sizeof(_vec3), &dwByte, NULL);
			ReadFile(hFile, &bAni, sizeof(_bool), &dwByte, NULL);
			ReadFile(hFile, &uv, sizeof(UvXY), &dwByte, NULL);
			ReadFile(hFile, &eSpawn, sizeof(TILE_SPAWNER), &dwByte, NULL);



			GameObject* GOBJ = nullptr;
			//GRPDEV->AddRef();
			GOBJ = CXZTile::Create(GRPDEV, eTileSide, eTileState, uv.x1, uv.x2, uv.y, uv.y2);
			GOBJ->Set_ObjectTag(L"CXZTile");
			dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileStage(eTileStage);
			dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileSpawner(eSpawn);
			if (eTileState == TILE_STATE::STATE_DESTORY || eTileState == TILE_STATE::STATE_ANIMATION || eTileState == TILE_STATE::STATE_POTALEFFECT)
				dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileAnimaiton(cTileName, iTileTextureCnt, eTileSide, eTileState, eTileMode, iTilenum, vNextPos, bAni);
			else
			{
				dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileAll(nullptr, cTileName, eTileSide, eTileState, eTileMode, iTilenum, vNextPos);
				dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))
					->Set_TextureID(ResourceManager::GetInstance()->Find_Texture(dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileTextureName().c_str()));
			}

			dynamic_cast<Transform*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(Scale);
			dynamic_cast<Transform*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(Rotation);
			dynamic_cast<Transform*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Pos(Info);
			TileManager::GetInstance()->Load_TilePush(GOBJ, eTileStage, eTileMode);

			if (0 == dwByte)
				break;
		}

		MSG_BOX("로드 성공");
		CloseHandle(hFile);
	}
	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	CollisionManager::GetInstance()->Get_AllObjectOfScene();
	return S_OK;
}
INT	 DoCheolScene::Update_Scene(CONST FLOAT& _DT) {
	TileManager::GetInstance()->Update_TileList(_DT);
	CollisionManager::GetInstance()->Update_CollisionManager();
	return Scene::Update_Scene(_DT);
}
VOID DoCheolScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
	TileManager::GetInstance()->LateUpdate_Tile(_DT);
	CollisionManager::GetInstance()->LateUpdate_CollisionManager();
	CollisionManager::GetInstance()->Render_CollisionManager();
}
VOID DoCheolScene::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT DoCheolScene::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT DoCheolScene::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {


	Add_GameObjectToScene<CameraObject>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA, L"Camera");
	Add_GameObjectToScene<Player>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Player");

	Add_GameObjectToScene<Terrain>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Terrain");
	Add_GameObjectToScene<Tile>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Tile");


	return S_OK;
}
HRESULT DoCheolScene::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
DoCheolScene* DoCheolScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	DoCheolScene* LS = new DoCheolScene(_GRPDEV);
	SceneManager::GetInstance()->Set_CurrentScene(LS);
	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create DoCheolScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void DoCheolScene::Free() {
	Scene::Free();
}