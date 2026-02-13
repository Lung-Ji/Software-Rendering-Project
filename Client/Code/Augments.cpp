#include "../Include/PCH.h"
#include "Augments.h"

Augments::Augments(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Augments::Augments(CONST GameObject& _RHS) : GameObject(_RHS) {}
Augments::~Augments() {}

HRESULT	Augments::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Text_Initialize()))			return E_FAIL;
	if (FAILED(Effect_Initialize()))		return E_FAIL;
	return S_OK;
}
INT		Augments::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	return 0;
}
VOID	Augments::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	Augments::Render_GameObject() {
	Component_Sprite->Render_Sprite();

	FontObject* pTitle = FontManager::GetInstance()->Find_FontObject(L"Testing");
	if (pTitle) {
		pTitle->Text = L"가호 선택";
		pTitle->Visible = TRUE; 
	}
	FontObject* pContent = FontManager::GetInstance()->Find_FontObject(L"Testing2");
	if (pContent)
	{
		pContent->Text = L"가호의 능력과 관련한 텍스트";
		pContent->Visible = TRUE;
	}
	FontObject* pName = FontManager::GetInstance()->Find_FontObject(L"Testing3");
	if(pName)
		{
			pName->Text = L"가호 이름";
			pName->Visible = TRUE;
		}
}
HRESULT Augments::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;

		//폰트 임시 출력용
		//if (nullptr == m_pFont) {
		//	D3DXCreateFont(GRPDEV, 45, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		//	L"맑은 고딕", &m_pFont);
		//}
	return S_OK;
}
HRESULT Augments::Sprite_Initialize() {
	// Sprite 예시용
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Ui_Apostle_BackGroun.png", L"Apostle_BackGround", 0.f, 0.f, 1280, 960, TRUE, 155);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Object_LevelUpBless_Effect.png", L"Apostle_Light", 540.f, 30.f, 180, 180, TRUE, 255);
	Component_Sprite->Import_Sprite(L"../../UI/Augments/Spr_Object_LevelUpBless_Birth_03.png", L"Apostle", 540.f, 30.f, 170, 170, TRUE, 255);

	Component_Sprite->Import_Sprite(L"../../UI/Augments/Temp_Apostle.png", L"Apostle_Choose", 200.f, 70.f, 900, 70, TRUE, 255);

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
HRESULT Augments::Text_Initialize(){
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 625.f, 90.f }, 30, L"Testing", L"08서울한강체 L", D3DCOLOR_ARGB(255, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 625.f,500.f }, 30, L"Testing2", L"08서울한강체 L", D3DCOLOR_ARGB(255, 255, 255, 255));
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 600.f,415.f }, 20, L"Testing3", L"08서울한강체 L", D3DCOLOR_ARGB(255, 255, 255, 255));
	
	return S_OK;
}


HRESULT Augments::Effect_Initialize() {

		// Effect예시용//
//	PLAY_UI_EFFECT_ONCE(MAIN_UI_EFFECT::HP_EFFECT, L"HP_EFFECT1", 8.f, -30.f, 75, 75, 0.75f, 255);
	return S_OK;
}


VOID Augments::Make_ShadowOutLine(){
	SpriteINFO* Title = Component_Sprite->Get_Texture(L"Apostle_Choosse");
	FontObject* Name = FontManager::GetInstance()->Find_FontObject(L"Testing");
	Name->Set_Color(255, 255, 255, 255);
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
	Safe_Release(m_pFont);
	m_pFont = nullptr;

}