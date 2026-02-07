#include "../Include/PCH.h"
#include "VillageScene.h"

VillageScene::VillageScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
VillageScene::~VillageScene(){}
HRESULT	VillageScene::Ready_Scene() {

	return S_OK;
}
INT	 VillageScene::Update_Scene(CONST FLOAT& _DT) {
	return Scene::Update_Scene(_DT);
}
VOID VillageScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
}
VOID VillageScene::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT VillageScene::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT VillageScene::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
HRESULT VillageScene::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
VillageScene* VillageScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	VillageScene* LS = new VillageScene(_GRPDEV);

	SceneManager::GetInstance()->Set_CurrentScene(LS);

	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create VillageScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void VillageScene::Free() {
	Scene::Free();
}