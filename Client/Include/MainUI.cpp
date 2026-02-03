#include "../Include/PCH.h"
#include "MainUI.h"

MainUI::MainUI(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
MainUI::MainUI(CONST GameObject& _RHS)		: GameObject(_RHS)		{}
MainUI::~MainUI()													{}

HRESULT	MainUI::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT		MainUI::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	return 0;
}
VOID	MainUI::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	MainUI::Render_GameObject() {
	
	Component_Sprite->Render_Sprite();
}
HRESULT MainUI::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;

	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Skill01.png", 50, 50, 10, 650, 100);
	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Skill02.png", 50, 50, 70, 650);
	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Skill03.png", 50, 50, 130, 650);

	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Testing.png", 50, 50, 180, 650);

	return S_OK;
}
MainUI* MainUI::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MainUI* MUI = new MainUI(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create MainUI.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID	MainUI::Free() {
	GameObject::Free();
}