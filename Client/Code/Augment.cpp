#include "../Include/PCH.h"
#include "Augment.h"

Augment::Augment(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
Augment::Augment(CONST GameObject& _RHS)		: GameObject(_RHS)		{}
Augment::~Augment()													{}

HRESULT	Augment::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Text_Initialize()))			return E_FAIL;
	if (FAILED(Item_Initialize()))			return E_FAIL;

	return S_OK;
}
INT		Augment::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	return 0;
}
VOID	Augment::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	Augment::Render_GameObject() {
	Component_Sprite->Render_Sprite();
}

HRESULT Augment::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;

	return S_OK;
}
HRESULT Augment::Sprite_Initialize() {
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_Apostle_BackGroun.png", L"Apostle_BackGround", 0.f, 0.f, 1280, 960, TRUE, 155);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Object_LevelUpBless_Effect.png", L"Apostle_Light", 540.f, 30.f, 180, 180, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Object_LevelUpBless_Birth_03.png", L"Apostle", 540.f, 30.f, 170, 170, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-04.png", L"Perk_01", 340.f, 270.f, 80.f, 80.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-05.png", L"Perk_02", 590.f, 260.f, 108.f, 108.f, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-07.png", L"Perk_03", 820.f, 260.f, 108.f, 108.f, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_ApostleLiberation_Background_Top.png", L"Y", 270.f, 400.f, 700, 80, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_ApostleLiberation_Background_Bottom.png", L"D", 270.f, 480.f, 700, 140, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Background.png", L"Perk_BackGround", 300.f, 230.f, 140, 140, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Background.png", L"Perk_BackGround", 560.f, 230.f, 140, 140, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Background.png", L"Perk_BackGround", 800.f, 230.f, 140, 140, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-04.png", L"Perk_01", 340.f, 270.f, 60, 60, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-05.png", L"Perk_02", 590.f, 260.f, 88, 88, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_PerkIcon_1-07.png", L"Perk_03", 820.f, 260.f, 88, 88, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Frame.png", L"Perk_Frame", 300.f, 230.f, 140, 140, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Frame.png", L"Perk_Frame", 560.f, 230.f, 140, 140, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_LevelV2_Frame.png", L"Perk_Frame", 800.f, 230.f, 140, 140, TRUE, 255);
	
	return S_OK;
}
HRESULT Augment::Text_Initialize() {
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"가호 선택", { 625.f, 90.f }, 30, L"Testing", L"08서울한강체 L", D3DCOLOR_ARGB(255, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 625.f,500.f }, 30, L"Testing2", L"08서울한강체 L", D3DCOLOR_ARGB(255, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"가호 이름", { 600.f,415.f }, 20, L"Testing3", L"08서울한강체 L", D3DCOLOR_ARGB(255, 255, 255, 255));

	return S_OK;
}
HRESULT Augment::Item_Initialize() {
	return S_OK;
}
Augment* Augment::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Augment* MUI = new Augment(_GRPDEV);
	if (FAILED(MUI->Ready_GameObject())) {
		MSG_BOX("Cannot Create Augments.");
		Safe_Release(MUI);
		return nullptr;
	}
	return MUI;
}
VOID  Augment::Free() {
	GameObject::Free();
}