#include "../Include/PCH.h"
#include "Augments.h"
#include "UIManager.h"

Augments::Augments(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Augments::Augments(CONST GameObject& _RHS) : GameObject(_RHS) {}
Augments::~Augments() {}

HRESULT	Augments::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Effect_Initialize()))		return E_FAIL;
	return S_OK;
}
INT		Augments::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	if (KEY_DOWN(DIK_P)) {
		REPLAY_UI_EFFECT(L"HP_EFFECT1");
		REPLAY_UI_EFFECT(L"HP_EFFECT2");
		REPLAY_UI_EFFECT(L"HP_EFFECT3");
		REPLAY_UI_EFFECT(L"HP_EFFECT4");
		REPLAY_UI_EFFECT(L"HP_EFFECT5");
		REPLAY_UI_EFFECT(L"TEARDROP_EFFECT1");
		REPLAY_UI_EFFECT(L"TEARDROP_EFFECT2");
		REPLAY_UI_EFFECT(L"TEARDROP_EFFECT3");
		REPLAY_UI_EFFECT(L"COIN_EFFECT");
		REPLAY_UI_EFFECT(L"DS_EFFECT1");
		REPLAY_UI_EFFECT(L"DS_EFFECT2");
	}
	return 0;
}
VOID	Augments::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	Augments::Render_GameObject() {

	Component_Sprite->Render_Sprite();
}
HRESULT Augments::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;
	TextureList = Component_Sprite->Get_TextureList();

	return S_OK;
}
HRESULT Augments::Sprite_Initialize() {
	// Sprite 예시용
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Background.png", L"Perk_BackGround", 300.f, 230.f, 160.f, 160.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Background.png", L"Perk_BackGround", 560.f, 230.f, 160.f, 160.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Background.png", L"Perk_BackGround", 800.f, 230.f, 160.f, 160.f, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-04.png", L"Perk_01", 340.f, 270.f, 80.f, 80.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-05.png", L"Perk_02", 590.f, 260.f, 108.f, 108.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-07.png", L"Perk_03", 820.f, 260.f, 108.f, 108.f, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Frame.png", L"Perk_Frame", 300.f, 230.f, 160.f, 160.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Frame.png", L"Perk_Frame", 560.f, 230.f, 160.f, 160.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Frame.png", L"Perk_Frame", 800.f, 230.f, 160.f, 160.f, TRUE, 255);



	return S_OK;
}
HRESULT Augments::Effect_Initialize() {

		// Effect예시용//
//	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT1", 8.f, -30.f, 75, 75, 0.75f, 255);

	return S_OK;
}
Augments* Augments::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Augments* MUI = new Augments(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create Augments.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID	Augments::Free() {
	GameObject::Free();
}