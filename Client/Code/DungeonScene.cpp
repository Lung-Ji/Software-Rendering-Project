#include "../Include/PCH.h"
#include "DungeonScene.h"

DungeonScene::DungeonScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
DungeonScene::~DungeonScene() {}
HRESULT	DungeonScene::Ready_Scene() {

	return S_OK;
}
INT	 DungeonScene::Update_Scene(CONST FLOAT& _DT) {
	return Scene::Update_Scene(_DT);
}
VOID DungeonScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
}
VOID DungeonScene::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT DungeonScene::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT DungeonScene::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
HRESULT DungeonScene::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
DungeonScene* DungeonScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	DungeonScene* LS = new DungeonScene(_GRPDEV);

	SceneManager::GetInstance()->Set_CurrentScene(LS);

	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create DungeonScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void DungeonScene::Free() {
	Scene::Free();
}