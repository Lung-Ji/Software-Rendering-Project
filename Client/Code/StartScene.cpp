#include "../Include/pch.h"
#include "StartScene.h"

StartScene::StartScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
StartScene::~StartScene() {}

HRESULT	StartScene::Ready_Scene() {
	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);
	ProtoManager::GetInstance()->Push_ProtoType(GRPDEV, StateMachine::Create(GRPDEV));
	if (FAILED(Ready_Enviroment_Layer(L"Enviroment_Layer")))	return E_FAIL;
	if (FAILED(Ready_GameLogic_Layer(L"GameLogic_Layer")))		return E_FAIL;
	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	return S_OK;
}
INT	 StartScene::Update_Scene(CONST FLOAT& _DT) {
	return Scene::Update_Scene(_DT);
}
VOID StartScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
}
VOID StartScene::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT StartScene::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	GOBJ = CameraObject::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Camera");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	GOBJ = Monster::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Monster");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	GOBJ = Monster1::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Monster1");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;
	
	GOBJ = Terrain::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Terrain");
	
	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	GOBJ = MainUI::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"MainUI");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	GOBJ = Tile::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Tile");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	LayerList.push_back(LYR);
	
	return S_OK;
}
HRESULT StartScene::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	GOBJ = Player::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Player");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT StartScene::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
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