#include "../Include/PCH.h"
#include "UITest.h"

UITest::UITest(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
UITest::~UITest() {}

HRESULT	UITest::Ready_Scene() {
	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);
	ProtoManager::GetInstance()->Push_ProtoType(GRPDEV, StateMachine::Create(GRPDEV));
	if (FAILED(Ready_Enviroment_Layer(L"Enviroment_Layer")))	return E_FAIL;
	if (FAILED(Ready_GameLogic_Layer(L"GameLogic_Layer")))		return E_FAIL;
	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	return S_OK;
}
INT	 UITest::Update_Scene(CONST FLOAT& _DT) {
	return Scene::Update_Scene(_DT);
}
VOID UITest::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
}
VOID UITest::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT UITest::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	GOBJ = MainMenu::Create(GRPDEV);
	GOBJ->Set_ObjectTag(L"MainMenu");

	if (nullptr == GOBJ)					return E_FAIL;
	if (FAILED(LYR->Add_GameObject(GOBJ)))	return E_FAIL;



	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT UITest::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {
	
	return S_OK;
}
HRESULT UITest::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
UITest* UITest::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	UITest* LS = new UITest(_GRPDEV);

	SceneManager::GetInstance()->Set_CurrentScene(LS);

	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create UITest.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void UITest::Free() {
	Scene::Free();
}