#include "../Include/PCH.h"
#include "MainUI.h"

MainUI::MainUI(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
MainUI::MainUI(CONST GameObject& _RHS)		: GameObject(_RHS)		{}
MainUI::~MainUI()													{}

HRESULT	MainUI::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Effect_Initialize()))		return E_FAIL;
	if (FAILED(Text_Initialize()))			return E_FAIL;

	PlayerObject = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_GameObject(L"Player"));

	Speech_Bubble = FALSE;
	Speech_Text = L"";
	Timer01 = 0.f; Timer02 = 0.f; Timer03 = 0.f;

	MainUIOpacity = 0.f;

	Current_KeyCount		= 0;
	Current_CoinCount		= 0;
	Current_CrystalCount	= 0;

	return S_OK;
}
INT		MainUI::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	if (KEY_DOWN(DIK_LCONTROL)) {
		Player_LostHP();
		Player_UseSkill();
	}
	if (KEY_DOWN(DIK_M)) {
		PlayerObject->Set_Key(10);
		PlayerObject->Set_Coin(20);
		PlayerObject->Set_Crystal(15);
	}
	PopUp_Speech_Bubble(Speech_Text, _DT);
	PopUp_Speech_Bubble(ItemTag, _DT);
	Timer02 += _DT; 
	if(Timer02 > 0.1f){
		Player_KeyModify();
		Player_MoneyModify();
		Player_CrystalModify();
		Timer02 = 0.f;
	}
	PopUp_ItemInfo(L"Relic_Item3", _DT);
	return 0;
}
VOID	MainUI::LateUpdate_GameObject(CONST FLOAT& _DT) {
	
}
VOID	MainUI::Render_GameObject() {
	Component_Sprite->Render_Sprite();
}
VOID MainUI::Player_LostHP() {
	INT PlayerHP = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_GameObject(L"Player"))->Get_HP();
	if (PlayerHP > 0) {
		wstring UIKey_HP = L"HP_EFFECT" + to_wstring(PlayerHP);
		dynamic_cast<Player*>(SceneManager::GetInstance()->Get_GameObject(L"Player"))->Set_HP(PlayerHP - 1);
		REPLAY_UI_EFFECT(UIKey_HP);

		UIKey_HP = L"HP_SPRITE" + to_wstring(PlayerHP);
		Component_Sprite->Get_Texture(UIKey_HP)->Set_Visible(FALSE);

		UIKey_HP = L"EHP_SPRITE" + to_wstring(PlayerHP);
		Component_Sprite->Get_Texture(UIKey_HP)->Set_Visible(TRUE);
	}
}
VOID MainUI::Player_KeyModify() {
	if (Current_KeyCount != PlayerObject->Get_Key()) {
		FontObject* Font = FontManager::GetInstance()->Find_FontObject(L"KeyCountText");
		if(Current_KeyCount < PlayerObject->Get_Key())
			Font->Set_Text(to_wstring(++Current_KeyCount));
		else
			Font->Set_Text(to_wstring(--Current_KeyCount));
	}
}
VOID MainUI::Player_MoneyModify() {
	if (Current_CoinCount != PlayerObject->Get_Coin()) {
		FontObject* Font = FontManager::GetInstance()->Find_FontObject(L"CoinCountText");
		if (Current_CoinCount < PlayerObject->Get_Coin())
			Font->Set_Text(to_wstring(++Current_CoinCount));
		else
			Font->Set_Text(to_wstring(--Current_CoinCount));
	}
}
VOID MainUI::Player_CrystalModify() {
	if (Current_CrystalCount != PlayerObject->Get_Crystal()) {
		FontObject* Font = FontManager::GetInstance()->Find_FontObject(L"CrystalCountText");
		if (Current_CrystalCount < PlayerObject->Get_Crystal())
			Font->Set_Text(to_wstring(++Current_CrystalCount));
		else
			Font->Set_Text(to_wstring(--Current_CrystalCount));
	}
}
VOID MainUI::Player_UseSkill() {
	INT PlayerToken = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_GameObject(L"Player"))->Get_Token();
	wstring UIKey_HP = L"TOKEN_EFFECT" + to_wstring(PlayerToken);
	if (PlayerToken > 0) {
		dynamic_cast<Player*>(SceneManager::GetInstance()->Get_GameObject(L"Player"))->Set_Token(PlayerToken - 1);
		REPLAY_UI_EFFECT(UIKey_HP);

		UIKey_HP = L"Token" + to_wstring(PlayerToken);
		Component_Sprite->Get_Texture(UIKey_HP)->Set_Visible(FALSE);
	}
}
VOID MainUI::PopUp_Interaction_Notice(wstring _Text, BOOL _Vis) {
	SpriteINFO* KeyBoard = Component_Sprite->Get_Texture(L"KEY_E");
	SpriteINFO* InterBG = Component_Sprite->Get_Texture(L"Interaction_BG");
	FontObject* FO = FontManager::GetInstance()->Find_FontObject(L"Interaction_Text");
	FO->Text = _Text;

	if (_Vis) {
		KeyBoard->Set_Visible(TRUE);
		InterBG->Set_Visible(TRUE);
		FO->Set_Color(200, 255, 255, 255);
	} 
	else {
		KeyBoard->Set_Visible(FALSE);
		InterBG->Set_Visible(FALSE);
		FO->Set_Color(0, 255, 255, 255);
	}
	
}
VOID MainUI::PopUp_ItemInfo(wstring ItemTag, FLOAT _DT) {
	if (KEY_DOWN(DIK_B)) { ItemInfo = TRUE; }
	if (ItemInfo) {
		SpriteINFO* BackGround = Component_Sprite->Get_Texture(L"ItemNoticeBG");
		SpriteINFO* ITEM = Component_Sprite->Get_Texture(ItemTag);

		ItemINFO* iINFO = UIManager::GetInstance()->Find_Item(ItemTag);
		
		FontObject* InfoFont = FontManager::GetInstance()->Find_FontObject(L"ItemInfo");
		FontObject* ClassFont = FontManager::GetInstance()->Find_FontObject(L"ItemClass");

		InfoFont->Set_Text(iINFO->ItemName);
		ClassFont->Set_Text(iINFO->ItemClass);

		if (Timer03 <= 1) {
			Timer03 += _DT;
			if (BackGround->Get_Pos().x >= 1000.f) {
				BackGround->Set_Pos(BackGround->Get_Pos().x - 20.f, BackGround->Get_Pos().y);
				ITEM->Set_Pos(ITEM->Get_Pos().x - 20.f, ITEM->Get_Pos().y);
			}if (InfoFont->Get_Pos().x >= 1130.f) {
				InfoFont->Set_Pos(InfoFont->Get_Pos().x - 20.f, InfoFont->Get_Pos().y);
				ClassFont->Set_Pos(ClassFont->Get_Pos().x - 20.f, ClassFont->Get_Pos().y);
			}
			
			
			if (Timer03 < 0.33f) {
				BackGround->Set_Opacity(200 * Timer03 * 3);
				ITEM->Set_Opacity(200 * Timer03 * 3);
				InfoFont->Set_Color(200 * Timer03 * 3, 255, 255, 255);
				ClassFont->Set_Color(200 * Timer03 * 3, 255, 255, 255);
			}
			else {
				BackGround->Set_Opacity(200);
				ITEM->Set_Opacity(200);
				InfoFont->Set_Color(200, 255, 255, 255);
				ClassFont->Set_Color(200, 255, 255, 255);
			}
		}
		else if (Timer03 >= 1.f && Timer03 < 3.f) {
			Timer03 += _DT;
		}
		else if (Timer03 >= 3.f && Timer03 < 4.f) {
			Timer03 += _DT;
			if (Timer03 < 4.f) {
				BackGround->Set_Opacity(200 - (200 * (Timer03 - 3)));
				ITEM->Set_Opacity((200 - (200 * (Timer03 - 3))));
				InfoFont->Set_Color((200 - (200 * (Timer03 - 3))), 255, 255, 255);
				ClassFont->Set_Color(200 - (200 * (Timer03 - 3)), 255, 255, 255);
			}
			else {
				BackGround->Set_Opacity(0);
				ITEM->Set_Opacity(0);
				InfoFont->Set_Color(0, 255, 255, 255);
				ClassFont->Set_Color(0, 255, 255, 255);
			}
		}
		else if (Timer03 >= 4.f) {
			BackGround->Set_Pos(1300.f, 320.f);
			ITEM->Set_Pos(1300.f, 290.f);
			InfoFont->Set_Pos(1430.f, InfoFont->Get_Pos().y);
			ClassFont->Set_Pos(1430.f, ClassFont->Get_Pos().y);

			BackGround->Set_Opacity(0);
			ITEM->Set_Opacity(0);
			InfoFont->Set_Color(0, 255, 255, 255);
			ClassFont->Set_Color(0, 255, 255, 255);

			Timer03 = 0.f;
			ItemInfo = FALSE;
		}
	}
}
VOID MainUI::PopUp_Speech_Bubble(wstring _Text, FLOAT _DT) {
	if (KEY_DOWN(DIK_N)) { Speech_Bubble = TRUE; }
	if (Speech_Bubble) {
		SpriteINFO* BackGround = Component_Sprite->Get_Texture(L"SpeechBubble_BG");
		SpriteINFO* Frame = Component_Sprite->Get_Texture(L"SpeechBubble_Frame");
		SpriteINFO* Character = Component_Sprite->Get_Texture(L"SpeechBubble_Tif");
		FontObject* Font = FontManager::GetInstance()->Find_FontObject(L"TifNotice_Text");

		//Font->Set_Text(_Text);
		Font->Set_Text(L"유물의 헌사"); // 디버그용
		if (Timer01 < 1.f) {
			Timer01 += _DT;

			BackGround->Set_Pos(BackGround->Get_Pos().x, BackGround->Get_Pos().y - Timer01 * 2 * cosf(Timer01));
			Frame->Set_Pos(Frame->Get_Pos().x, Frame->Get_Pos().y - Timer01 * 2 * cosf(Timer01));
			Character->Set_Pos(Character->Get_Pos().x, Character->Get_Pos().y - Timer01 * 2 * cosf(Timer01));
			Font->Set_Pos( Font->Get_Pos().x, Font->Get_Pos().y - Timer01 * 2 * cosf(Timer01) );

			if (Timer01 < 1.f) {
				BackGround->Set_Opacity(Timer01 * 255);
				Frame->Set_Opacity(Timer01 * 255);
				Character->Set_Opacity(Timer01 * 255);
				Font->Set_Color(Timer01 * 200, 255, 255, 255);
			}
			else {
				BackGround->Set_Opacity(255);
				Frame->Set_Opacity(255);
				Character->Set_Opacity(255);
				Font->Set_Color(200, 255, 255, 255);
			}
		}
		else if (Timer01 >= 1.f && Timer01 < 3.f) {
			Timer01 += _DT;
		}
		else if (Timer01 >= 3.f && Timer01 < 4.f) {
			Timer01 += _DT;

			BackGround->Set_Pos(BackGround->Get_Pos().x, BackGround->Get_Pos().y + (Timer01 - 3) * 3);
			Frame->Set_Pos(Frame->Get_Pos().x, Frame->Get_Pos().y + (Timer01 - 3) * 3);
			Character->Set_Pos(Character->Get_Pos().x, Character->Get_Pos().y + (Timer01 - 3) * 3);
			Font->Set_Pos( Font->Get_Pos().x, Font->Get_Pos().y + (Timer01 - 3) * 3 );

			if (Timer01 < 4) {
				BackGround->Set_Opacity(255 - 255 * (Timer01 - 3));
				Frame->Set_Opacity(255 - 255 * (Timer01 - 3));
				Character->Set_Opacity(255 - 255 * (Timer01 - 3));
				Font->Set_Color(200 - 200 * (Timer01 - 3), 255, 255, 255);
			}
			else {
				BackGround->Set_Opacity(0);
				Frame->Set_Opacity(0);
				Character->Set_Opacity(0);
				Font->Set_Color(0, 255, 255, 255);
			}
		}
		else if (Timer01 >= 4.f) {
			Timer01 = 0;
			Speech_Bubble = FALSE;

			BackGround->Set_Opacity(0);
			Frame->Set_Opacity(0);
			Character->Set_Opacity(0);
			Font->Set_Color(0, 255, 255, 255);

			BackGround->Set_Pos(0.f, 529.f + 30.f);
			Character->Set_Pos(0.f, 529.f + 30.f);
			Frame->Set_Pos(0.f, 503.f + 30.f);
			Font->Set_Pos( 180.f, 555.f + 30.f );
		}
	}
}

VOID MainUI::All_UI_FadeOUT() {

}

VOID MainUI::All_UI_FadeIN() {

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
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png",				L"HP_BG", 13.f, -60.f, 183, 180, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png",				L"TEARDROP_BG", 13.f, -15.f, 130, 180, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png",				L"KEY_BG", 13.f, 42.f, 100, 150, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png",				L"COIN_BG", 13.f, 77.f, 100, 150, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/HP_BG.png",				L"CRYSTAL_BG", 13.f, 113.f, 100, 150, TRUE, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////// HP/MP /////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png",		L"HP_SPRITE1", -45.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png",		L"HP_SPRITE2", -15.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png",		L"HP_SPRITE3", 15.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png",		L"HP_SPRITE4", 45.f, -60.f, 180, 180, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_HpStock.png",		L"HP_SPRITE5", 75.f, -60.f, 180, 180, TRUE);

	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png",	L"EHP_SPRITE1", -45.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png",	L"EHP_SPRITE2", -15.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png",	L"EHP_SPRITE3", 15.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png",	L"EHP_SPRITE4", 45.f, -60.f, 180, 180, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Spr_Ui_EmptyHpStock.png",	L"EHP_SPRITE5", 75.f, -60.f, 180, 180, FALSE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// UTILITY //////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Crystal.png", L"CRYSTAL", 18.f, 175.f, 20, 20, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Key.png", L"KEY", 18.f, 103.f, 18, 18, TRUE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// SPEECH ///////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SpeechBubble_BG.png", L"SpeechBubble_BG", 0.f, 529.f + 30.f, 360, 62, TRUE, 0);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SpeechBubble_Tif.png", L"SpeechBubble_Tif", 0.f, 529.f + 30.f, 153, 62, TRUE, 0);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SpeechBubble_Frame.png", L"SpeechBubble_Frame", 0.f, 503.f + 30.f, 566 * 0.7f, 126 * 0.7f, TRUE, 0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// SKILL ////////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_BG.png",			L"SkillState_BG", 0.f, 600.f, 290.f, 120.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_Frame.png",		L"SkillState_Frame", 0.f, 600.f, 290.f, 120.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_Symbol_OFF.png",	L"SkillState_Symbol_OFF", 15.f, 615.f, 80.f, 80.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_SkillOn.png",		L"SkillState_SkillOn", 15.f, 615.f, 80.f, 80.f, FALSE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/SkillState_Symbol_ON.png",	L"SkillState_Symbol_ON", 15.f, 615.f, 80.f, 80.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/KEY_Q.png",					L"KEY_Q", 45.f, 595.f, 20.f, 20.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Token.png",					L"Token1", 104.f, 669.f, 33.f, 29.f, TRUE);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Token.png",					L"Token2", 137.f, 669.f, 33.f, 29.f, TRUE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// INTERACT /////////////////////////////////////////////////////
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/KEY_E.png",				L"KEY_E", 720.f, 590.f, 35, 35, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Interaction_BG.png",		L"Interaction_BG", 720.f, 590.f, 215, 35, TRUE, 155);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/ItemNoticeBG.png",		L"ItemNoticeBG", 1300.f, 320.f, 300, 40, TRUE, 0);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Relic_Item1.png",			L"Relic_Item1", 1300.f, 290.f, 80, 80, TRUE, 0);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Relic_Item2.png",			L"Relic_Item2", 1300.f, 290.f, 80, 80, TRUE, 0);
	Component_Sprite->Import_Sprite(L"../../UI/MainUI/Relic_Item3.png",			L"Relic_Item3", 1300.f, 290.f, 80, 80, TRUE, 0);
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

	PLAY_UI_EFFECT(MAIN_UI_EFFECT::DASHSTOCK_EFFECT, L"DASHSTOCK_EFFECT1", -43.f, -13.f, 175, 175, 2.f, 255);
	PLAY_UI_EFFECT(MAIN_UI_EFFECT::DASHSTOCK_EFFECT, L"DASHSTOCK_EFFECT2", -10.f, -13.f, 175, 175, 2.f, 255);
	PLAY_UI_EFFECT(MAIN_UI_EFFECT::DASHSTOCK_EFFECT, L"DASHSTOCK_EFFECT3",  23.f, -13.f, 175, 175, 2.f, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////// UTILITY /////////////////////////////////////////////////
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::COIN_EFFECT, L"COIN_EFFECT", 20.f, 142.f, 15, 15, 1.f, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// SKILL //////////////////////////////////////////////////
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::TOKEN_EFFECT, L"TOKEN_EFFECT1", 70.f,  630.f, 100, 100, 0.6f, 255);
	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::TOKEN_EFFECT, L"TOKEN_EFFECT2", 104.f, 630.f, 100, 100, 0.6f, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
HRESULT MainUI::Text_Initialize() {
	////////////////////////////////////////////// UTILITY //////////////////////////////////////////////////////
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"0", { 52.f, 106.f }, 16, L"KeyCountText",		L"08서울한강체 L", D3DCOLOR_ARGB(200, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"0", { 52.f, 142.f }, 16, L"CoinCountText",		L"08서울한강체 L", D3DCOLOR_ARGB(200, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"0", { 52.f, 178.f }, 16, L"CrystalCountText",	L"08서울한강체 L", D3DCOLOR_ARGB(200, 255, 255, 255));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// WEAPON ///////////////////////////////////////////////////////
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"∞", { 1220.f, 687.f }, 16, L"ArrowCountText",		L"08서울한강체 L", D3DCOLOR_ARGB(200, 255, 255, 255));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////// INTERACTION ////////////////////////////////////////////////////
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 810.f, 600.f }, 16, L"Interaction_Text", L"08서울한강체 M", D3DCOLOR_ARGB(200, 255, 255, 255), 400);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////// GETITEM ///////////////////////////////////////////////////////
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 1430.f, 330.f }, 20, L"ItemInfo", L"08서울한강체 L", D3DCOLOR_ARGB(200, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 1430.f, 400.f }, 12, L"ItemClass", L"08서울한강체 L", D3DCOLOR_ARGB(200, 255, 255, 255));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////// SPEECH ///////////////////////////////////////////////////////
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 180.f, 550.f + 30.f }, 13, L"TifNotice_Text", L"08서울한강체 M", D3DCOLOR_ARGB(0, 255, 255, 255), 400);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
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