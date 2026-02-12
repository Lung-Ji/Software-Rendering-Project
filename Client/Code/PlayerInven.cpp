#include "../Include/PCH.h"
#include "PlayerInven.h"

PlayerInven::PlayerInven(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), Equip_ItemList{ nullptr }, Saved_ItemList{ nullptr } {}
PlayerInven::PlayerInven(CONST GameObject& _RHS)	: GameObject(_RHS)	 , Equip_ItemList{ nullptr }, Saved_ItemList{ nullptr } {}
PlayerInven::~PlayerInven() {}

HRESULT	PlayerInven::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Text_Initialize()))			return E_FAIL;

	PlayerObject = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_GameObject(L"Player"));

	SavedItemIndex = 1;
	EquipedItemIndex = 1;

	FocusOn_SavedItem = TRUE;
	FocusOn_EquipedItem = FALSE;

	EquipMode = FALSE;

	return S_OK;
}
INT		PlayerInven::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	if(KEY_DOWN(DIK_B)) 
		UIManager::GetInstance()->Get_Active() ? UIManager::GetInstance()->Set_Active(false) : UIManager::GetInstance()->Set_Active(true);
	
	Selecting_SavedItem();
	Selecting_EquipItem();
	//Display_ItemInfo();

	return 0;
}
VOID	PlayerInven::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	PlayerInven::Render_GameObject() {	
	if (UIManager::GetInstance()->Get_Active() == FALSE) {
		PlayerObject->Set_PlayerStop(TRUE);
		Component_Sprite->Render_Sprite();
		UIManager::GetInstance()->Render_UI(GRPDEV, Inven);
		UIManager::GetInstance()->Render_UI(GRPDEV, Object);
	}
	else if(UIManager::GetInstance()->Get_Active()){
		PlayerObject->Set_PlayerStop(FALSE);
	}
}	
HRESULT PlayerInven::Component_Initialize() {
	UIManager::GetInstance()->Set_Active(true);
	Component_Sprite = ADD_COMPONENT_SPRITE;
	return S_OK;
}
HRESULT PlayerInven::Sprite_Initialize() {
	wstring BaseFolder = L"../../UI/Inventory_UI/";
		///////////////////////////////////////////////////// BACKGROUND //////////////////////////////////////////////////////
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_BG.png", L"Inven_BG", 0.f, 0.f, 1280, 720, TRUE, 155);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SavedSpace_BG.png", L"Inven_SavedSpace_BG", 810.f, 250.f, 393, 215, TRUE, 155);
		//////////////////////////////////////////////////////////// BASIC_FRAME ///////////////////////////////////////////////////////////////
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG01", 410.f + 80.F, 285.f, 70, 70, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG02", 485.f + 80.F, 230.f, 70, 70, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG03", 560.f + 80.F, 230.f, 70, 70, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG04", 635.f + 80.F, 285.f, 70, 70, TRUE, 200);

		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG05", 410.f + 80.F, 367.5f, 70, 70, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG06", 485.f + 80.F, 422.5f, 70, 70, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG07", 560.f + 80.F, 422.5f, 70, 70, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SpaceBG.png", L"InvenFrameBG08", 635.f + 80.F, 367.5f, 70, 70, TRUE, 200);

		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E1", 410.f + 80.F, 285.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E2", 485.f + 80.F, 230.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E3", 560.f + 80.F, 230.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E4", 635.f + 80.F, 285.f, 70, 70, TRUE, 255);
																																	   
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E5", 410.f + 80.F, 367.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E6", 485.f + 80.F, 422.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E7", 560.f + 80.F, 422.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame_E8", 635.f + 80.F, 367.5f, 70, 70, TRUE, 255);
		//////////////////////////////////////////////////////////// MARK ///////////////////////////////////////////////////////////////
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Weapon.png", L"InvenMark01", 410.f + 85.F, 290.f, 60, 60, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Weapon.png", L"InvenMark02", 485.f + 85.F, 235.f, 60, 60, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Weapon.png", L"InvenMark03", 560.f + 85.F, 235.f, 60, 60, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Weapon.png", L"InvenMark04", 635.f + 85.F, 290.f, 60, 60, TRUE, 200);

		Component_Sprite->Import_SpriteEX(BaseFolder, L"EquipMent.png", L"InvenMark05", 410.f + 85.F, 365.f, 65, 65, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"EquipMent.png", L"InvenMark06", 485.f + 85.F, 420.f, 65, 65, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"EquipMent.png", L"InvenMark07", 560.f + 85.F, 420.f, 65, 65, TRUE, 200);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"EquipMent.png", L"InvenMark08", 635.f + 85.F, 365.f, 65, 65, TRUE, 200);

		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E1", 410.f + 80.F, 285.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E2", 485.f + 80.F, 230.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E3", 560.f + 80.F, 230.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E4", 635.f + 80.F, 285.f, 70, 70, FALSE, 255);

		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E5", 410.f + 80.F, 367.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E6", 485.f + 80.F, 422.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E7", 560.f + 80.F, 422.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame_E8", 635.f + 80.F, 367.5f, 70, 70, FALSE, 255);
		/////////////////////////////////////////////////////// EMPTY SPACE ///////////////////////////////////////////////////////////////
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame1", 835.f, 292.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame2", 835.f + 67.5f, 292.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame3", 835.f + 67.5f * 2, 292.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame4", 835.f + 67.5f * 3, 292.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame5", 835.f + 67.5f * 4, 292.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame6", 835.f, 360.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame7", 835.f + 67.5f, 360.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame8", 835.f + 67.5f * 2, 360.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame9", 835.f + 67.5f * 3, 360.f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame10", 835.f + 67.5f * 4, 360.f, 70, 70, TRUE, 255);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////// SELECT SPACE ///////////////////////////////////////////////////////////////
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame1", 835.f, 292.5f, 70, 70, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame2", 835.f + 67.5f, 292.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame3", 835.f + 67.5f * 2, 292.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame4", 835.f + 67.5f * 3, 292.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame5", 835.f + 67.5f * 4, 292.5f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame6", 835.f, 360.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame7", 835.f + 67.5f, 360.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame8", 835.f + 67.5f * 2, 360.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame9", 835.f + 67.5f * 3, 360.f, 70, 70, FALSE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame10", 835.f + 67.5f * 4, 360.f, 70, 70, FALSE, 255);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////// KEY GUIDE ///////////////////////////////////////////////////////////////
		Component_Sprite->Import_SpriteEX(BaseFolder, L"KEY_Q.png", L"Inven_KEY_Q", 1000.f, 435.f, 20, 20, TRUE, 255);
		Component_Sprite->Import_SpriteEX(BaseFolder, L"KEY_E.png", L"Inven_KEY_E", 1110.f, 435.f, 20, 20, TRUE, 255);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////// ITEM INFO ///////////////////////////////////////////////////////////////
		ItemInfo_Screen.push_back(Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_ItemInfo_Top.png", L"Inven_InfoT", 140.f, 180.f, 335, 120, TRUE, 200));
		ItemInfo_Screen.push_back(Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_ItemInfo_Mid.png", L"Inven_InfoM", 140.f, 300.f, 335, 110, TRUE, 200));
		ItemInfo_Screen.push_back(Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_ItemInfo_Bot.png", L"Inven_InfoB", 140.f, 410.f, 335,  63, TRUE, 200));

		ItemInfo_Screen.push_back(Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_ItemInfo_Frame.png", L"Inven_InfoFrame", 160.f, 210.f, 105, 105, TRUE, 255));
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
HRESULT  PlayerInven::Text_Initialize() {
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"버리기", { 1050.f, 437.f }, 16, L"Inven_QText", L"Yoon\u00AE 대한", D3DCOLOR_ARGB(0, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"선택", { 1150.f, 437.f }, 16, L"Inven_EText", L"Yoon\u00AE 대한", D3DCOLOR_ARGB(0, 255, 255, 255));

	//////////////////////////////////////////////////////// ITEM INFO ///////////////////////////////////////////////////////////////
	//FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"버리기", { 1050.f, 437.f }, 16, L"Inven_QText", L"Yoon\u00AE 대한", D3DCOLOR_ARGB(0, 255, 255, 255));
	//FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"선택", { 1150.f, 437.f }, 16, L"Inven_EText", L"Yoon\u00AE 대한", D3DCOLOR_ARGB(0, 255, 255, 255));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return S_OK;
}
HRESULT PlayerInven::Selecting_SavedItem() {
	if (FocusOn_SavedItem) {
		if (KEY_DOWN(DIK_W)) {
			if (SavedItemIndex <= 5)	return E_FAIL;
			else {
				SavedItemIndex -= 5;
				wstring PastFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex + 5);
				wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
		else if (KEY_DOWN(DIK_A)) {
			if (SavedItemIndex == 1 || SavedItemIndex == 6) {
				wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(FALSE);
				FocusOn_EquipedItem = TRUE;
				Selecting_EquipItem();
			}
			else {
				SavedItemIndex -= 1;
				wstring PastFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex + 1);
				wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
		else if (KEY_DOWN(DIK_S)) {
			if (SavedItemIndex >= 6)	return E_FAIL;
			else {
				SavedItemIndex += 5;
				wstring PastFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex - 5);
				wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
		else if (KEY_DOWN(DIK_D)) {
			if (SavedItemIndex == 10)	return E_FAIL;
			else {
				SavedItemIndex += 1;
				wstring PastFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex - 1);
				wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
	}
	return S_OK;
}
HRESULT PlayerInven::Selecting_EquipItem() {
	if (SavedItemIndex == 1 && FocusOn_SavedItem && FocusOn_EquipedItem) {
		EquipedItemIndex = 4;
		FocusOn_SavedItem = FALSE;
		wstring SelectedFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
		Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
		
	}	
	else if (SavedItemIndex == 6 && FocusOn_SavedItem && FocusOn_EquipedItem) {
		EquipedItemIndex = 8;
		FocusOn_SavedItem = FALSE;
		wstring SelectedFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
		Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
	}
		
	if (FocusOn_EquipedItem) {
		if (KEY_DOWN(DIK_W)) {
			if (EquipedItemIndex <= 4)	return E_FAIL;
			else {
				EquipedItemIndex -= 4;
				wstring PastFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex + 4);
				wstring SelectedFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
		else if (KEY_DOWN(DIK_A)){
			if (EquipedItemIndex == 1 || EquipedItemIndex == 5)	return E_FAIL;
			else {
				EquipedItemIndex -= 1;
				wstring PastFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex + 1);
				wstring SelectedFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
		else if (KEY_DOWN(DIK_S)){
			if (EquipedItemIndex >= 5)	return E_FAIL;
			else {
				EquipedItemIndex += 4;
				wstring PastFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex - 4);
				wstring SelectedFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
		else if (KEY_DOWN(DIK_D)){
			if (EquipedItemIndex == 4 || EquipedItemIndex == 8) {
				FocusOn_SavedItem = TRUE;
				FocusOn_EquipedItem = FALSE;

				if (EquipedItemIndex == 4) {
					wstring PastFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
					Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
					SavedItemIndex = 1;
					wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
					Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				}
				if (EquipedItemIndex == 8) {
					wstring PastFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
					Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
					SavedItemIndex = 6;
					wstring SelectedFrame = L"Inven_SelectFrame" + to_wstring(SavedItemIndex);
					Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				}

				return S_OK;
			}
			else {
				EquipedItemIndex += 1;
				wstring PastFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex - 1);
				wstring SelectedFrame = L"Inven_SelectFrame_E" + to_wstring(EquipedItemIndex);
				Component_Sprite->Get_Texture(SelectedFrame)->Set_Visible(TRUE);
				Component_Sprite->Get_Texture(PastFrame)->Set_Visible(FALSE);
			}
		}
	}
	
	return S_OK;
}
HRESULT PlayerInven::Equip_Item() {
	if (EquipMode) {
		if (KEY_DOWN(DIK_E)){
			if (FocusOn_SavedItem) {
				Saved_ItemList[SavedItemIndex - 1] = EquipObject;
			}
			if (FocusOn_EquipedItem) {
				Equip_ItemList[EquipedItemIndex - 1] = EquipObject;
			}
		}
	}

	if (FocusOn_SavedItem) {
		if (Saved_ItemList[SavedItemIndex - 1] != nullptr && KEY_DOWN(DIK_E)) {
			EquipMode = TRUE;
			EquipObject = Saved_ItemList[SavedItemIndex - 1];
		}
	}
	if (FocusOn_EquipedItem) {
		if (Equip_ItemList[EquipedItemIndex - 1] != nullptr && KEY_DOWN(DIK_E)) {
			EquipMode = TRUE;
			EquipObject = Equip_ItemList[EquipedItemIndex - 1];
		}
	}

	
	return S_OK;
}
HRESULT PlayerInven::Display_ItemInfo() {
	if (FocusOn_SavedItem) {
		if (Saved_ItemList[SavedItemIndex - 1] != nullptr) {
			for (auto& Comp : ItemInfo_Screen)
				Comp->Set_Visible(TRUE);


		}
		else {
			for (auto& Comp : ItemInfo_Screen)
				Comp->Set_Visible(FALSE);
		}
	}
	if (FocusOn_EquipedItem) {
		if (Equip_ItemList[EquipedItemIndex - 1] != nullptr) {
			for (auto& Comp : ItemInfo_Screen) 
				Comp->Set_Visible(TRUE);
		}
		else {
			for (auto& Comp : ItemInfo_Screen) 
				Comp->Set_Visible(FALSE);
		}
	}
	return S_OK;
}
HRESULT PlayerInven::Append_Item() {
	//if (_ITTY == ITEM_TYPE::WEAPON) {
	//	for (INT IDX = 1; IDX <= 4; ++IDX) {
	//		if (Equip_ItemList[IDX] == nullptr) {
	//			Equip_ItemList[IDX] = ;
	//			return S_OK;
	//		}
	//	}
	//	// 모든 Equip 칸이 채워져 있는 경우
	//	for (INT IDX = 1; IDX <= 10; ++IDX) {
	//		if (Saved_ItemList[IDX] == nullptr) {
	//			Saved_ItemList[IDX] = ;
	//			return S_OK;
	//		}
	//	}
	//	return E_FAIL;
	//}
	//else if (_ITTY == ITEM_TYPE::UTILITY) {
	//	for (INT IDX = 5; IDX <= 8; ++IDX) {
	//		if (Equip_ItemList[IDX] == nullptr) {
	//			Equip_ItemList[IDX] = ;
	//			return S_OK;
	//		}
	//	}
	//	// 모든 Equip 칸이 채워져 있는 경우
	//	for (INT IDX = 1; IDX <= 10; ++IDX) {
	//		if (Saved_ItemList[IDX] == nullptr) {
	//			Saved_ItemList[IDX] = ;
	//			return S_OK;
	//		}
	//	}
	//	return E_FAIL;
	//}
	return S_OK;
}
PlayerInven* PlayerInven::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	PlayerInven* MUI = new PlayerInven(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create PlayerInven.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID	PlayerInven::Free() {
	GameObject::Free();
}