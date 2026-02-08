#include "../Include/PCH.h"
#include "MainMenuButton.h"

MainMenuButton::MainMenuButton(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
MainMenuButton::MainMenuButton(CONST GameObject& _RHS) : GameObject(_RHS) {}
MainMenuButton::~MainMenuButton() {}

HRESULT	MainMenuButton::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT		MainMenuButton::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	return 0;
}
VOID	MainMenuButton::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	MainMenuButton::Render_GameObject() {

	Component_Sprite->Render_Sprite();
}
HRESULT MainMenuButton::Component_Initialize() {

	Component_Sprite = ADD_COMPONENT_SPRITE;

	//Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/KEY_E_Black.png", L"KEY_E", 700, 600, 50, 50, TRUE);
	// 이미 E키 구현해놓아서 빼놨습니다
	return S_OK;
}
MainMenuButton* MainMenuButton::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MainMenuButton* MUI = new MainMenuButton(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create MainMenuButton.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID	MainMenuButton::Free() {
	GameObject::Free();
}