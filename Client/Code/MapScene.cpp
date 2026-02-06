#include "../Include/PCH.h"
#include "MapScene.h"

MapScene::MapScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
MapScene::~MapScene() {}
HRESULT	MapScene::Ready_Scene() {

	return S_OK;
}
INT	 MapScene::Update_Scene(CONST FLOAT& _DT) {

	return Scene::Update_Scene(_DT);
}
VOID MapScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
}
VOID MapScene::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT MapScene::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT MapScene::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	GOBJ = CameraObject::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Camera");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	GOBJ = Terrain::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Terrain");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	GOBJ = Tile::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"Tile");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT MapScene::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
MapScene* MapScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MapScene* LS = new MapScene(_GRPDEV);
	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create MapScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void MapScene::Free() {
	Scene::Free();
}