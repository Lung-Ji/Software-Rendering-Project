#include "../Include/PCH.h"
#include "PlayerInven.h"

PlayerInven::PlayerInven(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
PlayerInven::PlayerInven(CONST GameObject& _RHS) : GameObject(_RHS) {}
PlayerInven::~PlayerInven() {}

HRESULT	PlayerInven::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	return S_OK;
}
INT		PlayerInven::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	if(KEY_DOWN(DIK_B))
	{
		if((UIManager::GetInstance()->Get_Active()))
			UIManager::GetInstance()->Set_Active(false);
		else
			UIManager::GetInstance()->Set_Active(true);
	}
	return 0;
}
VOID	PlayerInven::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	PlayerInven::Render_GameObject() {	
		UIManager::GetInstance()->Render_UI(GRPDEV, Inventory);
		UIManager::GetInstance()->Render_UI(GRPDEV, Object);
		//Component_Font->Render_Component();
}	
HRESULT PlayerInven::Component_Initialize() {
	UIManager::GetInstance()->Set_Active(true);

	return S_OK;
}
HRESULT PlayerInven::Sprite_Initialize() {
	
		///////////////////////////////////////////////// BACKGROUND //////////////////////////////////////////////////////
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_ArrowCount.png", L"INVEN_BACKGROUND", -45.f, -125.f, 1380.f, 1000.f, TRUE);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/MainUI/WeaponBG_ArrowCount.png",
			1380.f, 1000.f, -45.f, -125.f, TRUE,155);
		////////////////////////////////////////////// CUR_EQUIP_ARROW //////////////////////////////////////////////////////
		UIManager::GetInstance()->Import_UISprite(GRPDEV,Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png",100.f, 100.f,410.f, 250.f,TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV,Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png",100.f, 100.f,510.f, 200.f,TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV,Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png",100.f, 100.f,610.f, 200.f,TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV,Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png",100.f, 100.f,710.f, 250.f,TRUE, 255);

		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/Weapon.png", 80.f, 90.f, 523.f, 200.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/Weapon.png", 80.f, 90.f, 623.f, 200.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/Weapon.png", 80.f, 90.f, 723.f, 250.f, TRUE, 255);

		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_SPRITE2", 510.f, 200.f, 100.f, 100.f, TRUE);
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_SPRITE3", 610.f, 200.f, 100.f, 100.f, TRUE);
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_SPRITE4", 710.f, 250.f, 100.f, 100.f, TRUE);
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_SPRITE1", 410.f, 250.f, 100.f, 100.f, TRUE);
		///////////////////////////////////////////// CUR_EQUIP_EQUIPMENT/////////////////////////////////////////////////////
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png", 100.f, 100.f, 410.f, 350.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png", 100.f, 100.f, 510.f, 400.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png", 100.f, 100.f, 610.f, 400.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png", 100.f, 100.f, 710.f, 350.f, TRUE, 255);

		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/EquipMent.png", 80.f, 90.f, 423.f, 350.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/EquipMent.png", 80.f, 90.f, 523.f, 400.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/EquipMent.png", 80.f, 90.f, 623.f, 400.f, TRUE, 255);
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/EquipMent.png", 80.f, 90.f, 723.f, 350.f, TRUE, 255);

				
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_EQUIPMENT_SPRITE1", 410.f, 350.f, 100.f, 100.f, TRUE);
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_EQUIPMENT_SPRITE2", 510.f, 400.f, 100.f, 100.f, TRUE);
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_EQUIPMENT_SPRITE3", 610.f, 400.f, 100.f, 100.f, TRUE);
		//Component_Sprite->Import_Sprite(L"../../UI/MainUI/WeaponBG_Arrow.png", L"EQUIP_EQUIPMENT_SPRITE4", 710.f, 350.f, 100.f, 100.f, TRUE);
		///////////////////////////////////////////////EXAMPLE_WEARPON/////////////////////////////////////////////////////////////
		//Component_Sprite->Import_Sprite(L"../../UI/Weapon_UI/Spr_Weapon_No006_LongBowThumbnail.png", L"ARROW_INVEN1", 420.f, 265.f, 85.f, 85.f, TRUE);
		////////////////////////////////////////////INVENTORY_ITEM_BACKGROUND//////////////////////////////////////////////////////////////
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/Spr_Ui_Inventory_Background.png", 450.f, 300.f, 820.f, 200.f, TRUE, 200);

		//Component_Sprite->Import_Sprite(L"../../UI/Inventory_UI/Spr_Ui_Inventory_Background.png", L"INVENTORY_BACKGROUND", 900.f, 300.f, 450.f, 300.f, TRUE);
		/////////////////////////////////////////////INVENTORY_ITEM////////////////////////////////////////////////////////////////////////
		UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Weapon_UI/Spr_Weapon_No006_LongBowThumbnail.png",
		85.f, 85.f, 420.f, 265.f, TRUE, 255);

		UIManager::GetInstance()->Import_UISprite(GRPDEV, Object, L"../../UI/Inventory_UI/EquipMent_Status_Window.png",
			350.f, 300.f, 50.f, 200.f, TRUE, 255.f);
		//Component_Sprite->Import_Sprite(L"../../UI/Inventory_UI/Spr_Ui_Center_ItemAcquisition_Frame_Backgroud.png", L"INVENTORY_ITEM", 700.f, 250.f, 55.f, 55.f, TRUE);
		//UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/Inventory_UI/Spr_Ui_Center_ItemAcquisition_Frame_Backgroud.png", 
		//	55.f, 55.f, 700.f, 150.f, TRUE, 255);
		
	//	_vec2 rc = { 500.f,300.f };
	//	Component_Font->Import_Font(L"Test", 400, 1, rc);

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