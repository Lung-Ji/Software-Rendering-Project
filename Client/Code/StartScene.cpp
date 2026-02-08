#include "../Include/pch.h"
#include "StartScene.h"

StartScene::StartScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
StartScene::~StartScene() {}

HRESULT	StartScene::Ready_Scene() {
	Scene::Ready_Scene();
	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);

	if (FAILED( Ready_Enviroment_Layer()	))		return E_FAIL;
	if (FAILED( Ready_GameLogic_Layer()		))		return E_FAIL;
	if (FAILED( Ready_UserInterface_Layer()	))		return E_FAIL;

	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	CollisionManager::GetInstance()->Get_AllObjectOfScene();

	return S_OK;
}
INT	 StartScene::Update_Scene(CONST FLOAT& _DT) {
	CollisionManager::GetInstance()->Update_CollisionManager();
	return Scene::Update_Scene(_DT);
}
VOID StartScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	CollisionManager::GetInstance()->LateUpdate_CollisionManager();
	CollisionManager::GetInstance()->Render_CollisionManager();
	Scene::LateUpdate_Scene(_DT);
}
VOID StartScene::Render_Scene() {

	//GOBJ = Tile::Create(GRPDEV);
	//GOBJ->Set_ObjectTag(L"Tile");
	//
	//if (nullptr == GOBJ)					return E_FAIL;
	//if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;
	
	//return S_OK;

}
HRESULT StartScene::Ready_Enviroment_Layer() {
	Add_GameObjectToScene<Terrain>			(LAYER_TYPE::LAYER_STATIC_OBJECT , GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Terrain"		);
	return S_OK;
}
HRESULT StartScene::Ready_GameLogic_Layer() {
	Add_GameObjectToScene<CameraObject>		(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA , L"Camera"		);
	Add_GameObjectToScene<Player>			(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Player"		);
	Add_GameObjectToScene<Bat>				(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Bat");
	Add_GameObjectToScene<Docheol>			(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Docheol");
	return S_OK;
}
HRESULT StartScene::Ready_UserInterface_Layer() {
	Add_GameObjectToScene<MainMenuButton>	(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI	  ,	L"MainButton"	);
	Add_GameObjectToScene<MainMenu>			(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI	  ,	L"MainMenu"		);
	Add_GameObjectToScene<MainUI>			(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI	  , L"MainUI"		);
	return S_OK;
}
StartScene* StartScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	StartScene* LS = new StartScene(_GRPDEV);

	SceneManager::GetInstance()->Set_CurrentScene(LS);

	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create StartScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void StartScene::Free() {
	Scene::Free();
}