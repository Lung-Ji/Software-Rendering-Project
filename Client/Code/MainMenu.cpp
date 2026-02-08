#include "../Include/PCH.h"
#include "MainMenu.h"

MainMenu::MainMenu(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
MainMenu::MainMenu(CONST GameObject& _RHS) : GameObject(_RHS) {}
MainMenu::~MainMenu() {}

HRESULT	MainMenu::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;

}
INT		MainMenu::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);


	return 0;
}
VOID	MainMenu::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	MainMenu::Render_GameObject() {

	UIManager::GetInstance()->Render_UI(GRPDEV, Inventory);

}
HRESULT MainMenu::Component_Initialize(){
	UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../Resource/MainMenu/Spr_Tilte_Illustration.png", 1280, 720,0,0,TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Spr_Tilte_logo.png", L"Title", 100, 100, 400, 250, 100, TRUE);

	return S_OK;
}
MainMenu* MainMenu::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MainMenu* MUI = new MainMenu(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create MainMenu.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID	MainMenu::Free() {
	GameObject::Free();
}