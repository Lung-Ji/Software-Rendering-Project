#include "../Include/PCH.h"
#include "MainUI.h"
#include "UIManager.h"

MainUI::MainUI(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
MainUI::MainUI(CONST GameObject& _RHS)		: GameObject(_RHS)		{}
MainUI::~MainUI()													{}

HRESULT	MainUI::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Effect_Initialize()))		return E_FAIL;
	return S_OK;
}
INT		MainUI::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	if (KEY_DOWN(DIK_LCONTROL)) {  
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
	////////////////////////////////////////////// BACKBAR //////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png",		L"WeaponBG_Arrow", 1166.f, 580.f, 108, 108, TRUE, 150);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_ArrowCount.png", L"WeaponBG_ArrowCount", 1167.f, 681.f, 108, 30, TRUE, 150);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png", L"HP_BG", 13.f, -60.f, 183, 180, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png", L"TEARDROP_BG", 13.f, -15.f, 130, 180, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png", L"KEY_BG", 13.f, 42.f, 100, 150, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png", L"COIN_BG", 13.f, 77.f, 100, 150, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png", L"CRYSTAL_BG", 13.f, 113.f, 100, 150, TRUE, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////// HP/MP /////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png", L"HP_SPRITE1", -45.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png", L"HP_SPRITE2", -15.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png", L"HP_SPRITE3", 15.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png", L"HP_SPRITE4", 45.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png", L"HP_SPRITE5", 75.f, -60.f, 180, 180, TRUE);

	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png", L"EHP_SPRITE1", -45.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png", L"EHP_SPRITE2", -15.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png", L"EHP_SPRITE3", 15.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png", L"EHP_SPRITE4", 45.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png", L"EHP_SPRITE5", 75.f, -60.f, 180, 180, FALSE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// UTILITY //////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Crystal.png", L"CRYSTAL", 18.f, 175.f, 20, 20, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Key.png", L"KEY", 18.f, 103.f, 18, 18, TRUE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// SKILL ////////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_BG.png",			L"SkillState_BG", 0.f, 600.f, 290.f, 120.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_Frame.png",		L"SkillState_Frame", 0.f, 600.f, 290.f, 120.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_Symbol_OFF.png",	L"SkillState_Symbol_OFF", 15.f, 615.f, 80.f, 80.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_SkillOn.png",		L"SkillState_SkillOn", 15.f, 615.f, 80.f, 80.f, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_Symbol_ON.png",	L"SkillState_Symbol_ON", 15.f, 615.f, 80.f, 80.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/KEY_Q.png",					L"KEY_Q", 45.f, 595.f, 20.f, 20.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/DashStock.png",				L"DashStock1", 104.f, 669.f, 33.f, 29.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/DashStock.png",				L"DashStock2", 137.f, 669.f, 33.f, 29.f, TRUE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// INTERACT /////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/KEY_E.png", L"KEY_E", 720.f, 590.f, 35, 35, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Interaction_BG.png", L"Interaction_BG", 720.f, 590.f, 215, 35, TRUE, 155);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/ItemNoticeBG.png", L"ItemNoticeBG", 1000.f, 320.f, 300, 40, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Relic_Item1.png", L"Relic_Item1", 1000.f, 290.f, 80, 80, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Relic_Item2.png", L"Relic_Item2", 1000.f, 290.f, 80, 80, FALSE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Relic_Item3.png", L"Relic_Item3", 1000.f, 290.f, 80, 80, FALSE, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
HRESULT MainUI::Effect_Initialize() {
	/////////////////////////////////////// STATE ////////////////////////////////////////////////
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT1",   8.f, -30.f, 75, 75, 0.75f, 255);
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT2",  38.f, -30.f, 75, 75, 0.75f, 255);
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT3",  68.f, -30.f, 75, 75, 0.75f, 255);
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT4",  98.f, -30.f, 75, 75, 0.75f, 255);
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT5", 128.f, -30.f, 75, 75, 0.75f, 255);

	PLAY_UI_EFFECT(MAIN_UI_EFFECT::TEARDROP_EFFECT, L"TEARDROP_EFFECT1", -43.f, -13.f, 175, 175, 2.f, 255);
	PLAY_UI_EFFECT(MAIN_UI_EFFECT::TEARDROP_EFFECT, L"TEARDROP_EFFECT2", -10.f, -13.f, 175, 175, 2.f, 255);
	PLAY_UI_EFFECT(MAIN_UI_EFFECT::TEARDROP_EFFECT, L"TEARDROP_EFFECT3",  23.f, -13.f, 175, 175, 2.f, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////// UTILITY /////////////////////////////////////////////////
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::COIN_EFFECT, L"COIN_EFFECT", 20.f, 142.f, 15, 15, 1.f, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// SKILL //////////////////////////////////////////////////
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::DASHSTOCK_EFFECT, L"DS_EFFECT1", 70.f,  630.f, 100, 100, 1.3f, 255);
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::DASHSTOCK_EFFECT, L"DS_EFFECT2", 104.f, 630.f, 100, 100, 1.3f, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////

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