#include "../Include/pch.h"
#include "DebugScene.h"

DebugScene::DebugScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
DebugScene::~DebugScene() {}

HRESULT	DebugScene::Ready_Scene() {
	Scene::Ready_Scene();
	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);

	if (FAILED(Ready_Enviroment_Layer()))		return E_FAIL;
	if (FAILED(Ready_GameLogic_Layer()))		return E_FAIL;
	if (FAILED(Ready_UserInterface_Layer()))		return E_FAIL;

	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	UIManager::GetInstance()->Ready_UIManager(GRPDEV);
	//CollisionManager::GetInstance()->Get_AllObjectOfScene();

	return S_OK;
}
INT	 DebugScene::Update_Scene(CONST FLOAT& _DT) {
	//CollisionManager::GetInstance()->Update_CollisionManager();
	UIManager::GetInstance()->Update_UIManager(_DT);
	return Scene::Update_Scene(_DT);
}
VOID DebugScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	UIManager::GetInstance()->LateUpdate_UIManager(_DT);
	//CollisionManager::GetInstance()->LateUpdate_CollisionManager();
	//CollisionManager::GetInstance()->Render_CollisionManager();
	Scene::LateUpdate_Scene(_DT);
}
VOID DebugScene::Render_Scene() {
	UIManager::GetInstance()->Render_UIManager(GRPDEV);
}
HRESULT DebugScene::Ready_Enviroment_Layer() {
	//Add_GameObjectToScene<Terrain>(LAYER_TYPE::LAYER_STATIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Terrain");
	return S_OK;
}
HRESULT DebugScene::Ready_GameLogic_Layer() {
	Add_GameObjectToScene<CameraObject>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA, L"Camera");
	Add_GameObjectToScene<Player>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Player");
	//Add_GameObjectToScene<Monster1>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Monster1");
	return S_OK;
}
HRESULT DebugScene::Ready_UserInterface_Layer() {
	//Add_GameObjectToScene<MainMenuButton>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"MainButton");
	//Add_GameObjectToScene<MainMenu>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"MainMenu");
	Add_GameObjectToScene<MainUI>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"MainUI");
	return S_OK;
}
DebugScene* DebugScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	DebugScene* LS = new DebugScene(_GRPDEV);

	SceneManager::GetInstance()->Set_CurrentScene(LS);

	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create StartScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void DebugScene::Free() {
	Scene::Free();
}