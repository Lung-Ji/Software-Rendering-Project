#include "../Include/PCH.h"
#include "FieldApostle.h"

FieldApostle::FieldApostle(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
FieldApostle::FieldApostle(CONST GameObject& _RHS) : GameObject(_RHS) {}
FieldApostle::~FieldApostle() {}

HRESULT	FieldApostle::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;

}
INT		FieldApostle::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	return 0;
}
VOID	FieldApostle::LateUpdate_GameObject(CONST FLOAT& _DT) {
}
VOID	FieldApostle::Render_GameObject() {
	Component_Sprite->Render_Sprite();
	FontManager::GetInstance()->Render_FontManager();
}
HRESULT FieldApostle::Text_Initialize(){
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 350.f,200.f }, 30, L"Choose_Apostle", L"08서울한강체 L", D3DCOLOR_ARGB(0, 255, 255, 255));
	
	return S_OK;
}
HRESULT FieldApostle::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;
	return S_OK;
}
HRESULT FieldApostle::Sprite_Initialize() {
	wstring BaseFolder = L"../../UI/Augments";

	Component_Sprite->Import_SpriteEX(BaseFolder, L"Spr_Object_LevelUpBless_Birth_01.png", L"Apostle_Field", 400.f, 550.f, 100, 100, TRUE, 255);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"Temp_Apostle.png", L"Apostle_Field_BackGround", 200.f, 100.f, 200, 100, TRUE, 255);

	return S_OK;
}

VOID FieldApostle::Make_ShadowOutLine() {
	SpriteINFO* BackGround = Component_Sprite->Get_Texture(L"Apostle_Field_BackGround");
	

}

FieldApostle* FieldApostle::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	FieldApostle* FA = new FieldApostle(_GRPDEV);
	if (FAILED(FA->Ready_GameObject())) {
		MSG_BOX("Cannot Create Object_Explain.");
		Safe_Release(FA);
		return nullptr;
	}
	return FA;
}
VOID	FieldApostle::Free() {
	GameObject::Free();
}