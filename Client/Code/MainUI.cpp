#include "../Include/PCH.h"
#include "MainUI.h"
#include "UIManager.h"

MainUI::MainUI(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
MainUI::MainUI(CONST GameObject& _RHS)		: GameObject(_RHS)		{}
MainUI::~MainUI()													{}

HRESULT	MainUI::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	if (FAILED(Sprite_Initialize())) return E_FAIL;
	return S_OK;
}
INT		MainUI::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	if (KEY_DOWN(DIK_TAB)) INDEX++;
	if (KEY_DOWN(DIK_Q)) INDEX = 0;
	if (KEY_DOWN(DIK_9)) {
		PLAY_UI_EFFECT(UI_EFFECT::COIN_EFFECT, L"Coin_Effect", 100.f, 100.f, 0.3f, 0.3f, 1.f, 255);
	}
	if (KEY_DOWN(DIK_8)) {
		PLAY_UI_EFFECT(UI_EFFECT::HP_EFFECT, L"HP_EFFECT", 100.f, 100.f, 0.3f, 0.3f, 1.f, 255);
	}
	if (KEY_HOLD(DIK_LEFT)) {
		(*TextureList)[INDEX].Set_Pos((*TextureList)[INDEX].Get_Pos().x - 1.f, (*TextureList)[INDEX].Get_Pos().y);
	}
	if (KEY_HOLD(DIK_RIGHT)) {
		(*TextureList)[INDEX].Set_Pos((*TextureList)[INDEX].Get_Pos().x + 1.f, (*TextureList)[INDEX].Get_Pos().y);
	}
	if (KEY_HOLD(DIK_UP)) {
		(*TextureList)[INDEX].Set_Pos((*TextureList)[INDEX].Get_Pos().x , (*TextureList)[INDEX].Get_Pos().y - 1.f);
	}
	if (KEY_HOLD(DIK_DOWN)) {
		(*TextureList)[INDEX].Set_Pos((*TextureList)[INDEX].Get_Pos().x , (*TextureList)[INDEX].Get_Pos().y + 1.f);
	}
	return 0;
}
VOID	MainUI::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	MainUI::Render_GameObject() {
	
	Component_Sprite->Render_Sprite();
}
HRESULT MainUI::Component_Initialize() {
	
	Component_Sprite = ADD_COMPONENT_SPRITE;
	TextureList = Component_Sprite->Get_TextureList();
	
	return S_OK;
}
HRESULT MainUI::Sprite_Initialize() {

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