#include "../Include/PCH.h"
#include "Inventory.h"

Inventory::Inventory(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)	, Activate_Inventory(FALSE), BackGround_Opacity(0.f)	{}
Inventory::Inventory(CONST GameObject& _RHS)	: GameObject(_RHS)		, Activate_Inventory(FALSE), BackGround_Opacity(0.f)	{}
Inventory::~Inventory()																				{}

HRESULT	Inventory::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Effect_Initialize()))		return E_FAIL;
	return S_OK;
}
INT		Inventory::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	if (KEY_DOWN(DIK_B)) { Activate_Inventory ? Activate_Inventory = TRUE : Activate_Inventory = FALSE; }
	if (Activate_Inventory) {
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
		REPLAY_UI_EFFECT(L"");
	}
	return 0;
}
VOID	Inventory::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	Inventory::Render_GameObject() {
	Component_Sprite->Render_Sprite();
}
HRESULT Inventory::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;
	TextureList = Component_Sprite->Get_TextureList();

	return S_OK;
}
HRESULT Inventory::Sprite_Initialize() {
	wstring BaseFolder = L"../../UI/Inventory/";

	/////////////////////////////////////////////////// FRAME ///////////////////////////////////////////////////
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_BG.png", L"Inven_BG", 0.f, 0.f, 1280, 720, TRUE, 155);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SavedSpace_BG.png", L"Inven_SavedSpace_BG", 810.f, 250.f, 393, 215, TRUE, 155);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////  EMPTY SPACE ////////////////////////////////////////////////
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame1", 835.f,				292.5f, 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame2", 835.f + 67.5f,		292.5f, 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame3", 835.f + 67.5f * 2,	292.5f, 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame4", 835.f + 67.5f * 3,	292.5f, 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame5", 835.f + 67.5f * 4,	292.5f, 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame6", 835.f,				360.f , 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame7", 835.f + 67.5f,		360.f , 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame8", 835.f + 67.5f * 2, 360.f , 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame9", 835.f + 67.5f * 3, 360.f , 70, 70, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_NonSelectFrame.png", L"Inven_NonSelectFrame10",835.f + 67.5f * 4, 360.f , 70, 70, TRUE, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////						
	///////////////////////////////////////////////  SELECT SPACE ///////////////////////////////////////////////
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame1", 835.f,			  292.5f, 70, 70, TRUE,  255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame2", 835.f + 67.5f,	  292.5f, 70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame3", 835.f + 67.5f * 2, 292.5f, 70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame4", 835.f + 67.5f * 3, 292.5f, 70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame5", 835.f + 67.5f * 4, 292.5f, 70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame6", 835.f,			  360.f,  70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame7", 835.f + 67.5f,	  360.f,  70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame8", 835.f + 67.5f * 2, 360.f,  70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame9", 835.f + 67.5f * 3, 360.f,  70, 70, FALSE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Inven_SelectFrame.png", L"Inven_SelectFrame10",835.f + 67.5f * 4, 360.f,  70, 70, FALSE, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////// KEY GUIDE /////////////////////////////////////////////////
	Component_Sprite->Import_SpriteEX(BaseFolder, L"KEY_Q.png", L"Inven_KEY_Q", 1000.f, 435.f, 20, 20, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"KEY_E.png", L"Inven_KEY_E", 1110.f, 435.f, 20, 20, TRUE, 255);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
HRESULT Inventory::Effect_Initialize() {
	
	return S_OK;
}

Inventory* Inventory::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Inventory* INV = new Inventory(_GRPDEV);
	if (FAILED(INV->Ready_GameObject())) {
		MSG_BOX("Cannot Create Inventory.");
		Safe_Release(INV);
		return nullptr;
	}
	return INV;
}
VOID	Inventory::Free() {
	GameObject::Free();
}