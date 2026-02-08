#include "../Include/PCH.h"
#include "MainMenuLogo.h"

MainMenuLogo::MainMenuLogo(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
MainMenuLogo::MainMenuLogo(CONST GameObject& _RHS) : GameObject(_RHS) {}
MainMenuLogo::~MainMenuLogo() {}

HRESULT	MainMenuLogo::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT		MainMenuLogo::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	return 0;
}
VOID	MainMenuLogo::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	MainMenuLogo::Render_GameObject() {

	Component_Sprite->Render_Sprite();
}
HRESULT MainMenuLogo::Component_Initialize() {

	Component_Sprite = ADD_COMPONENT_SPRITE;

	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Spr_Tilte_Illustration.png", L"Title", 1280, 720, 0, 0, 100, TRUE);
	
	return S_OK;
}
MainMenuLogo* MainMenuLogo::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MainMenuLogo* MUI = new MainMenuLogo(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create MainMenuLogo.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID	MainMenuLogo::Free() {
	GameObject::Free();
}