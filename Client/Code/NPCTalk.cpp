#include "../Include/PCH.h"
#include "NPCTalk.h"

NPCTalk::NPCTalk(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)	{}
NPCTalk::NPCTalk(CONST GameObject& _RHS) : GameObject(_RHS)			{}
NPCTalk::~NPCTalk()													{}

HRESULT		NPCTalk::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	if (FAILED(Effect_Initialize()))		return E_FAIL;
	if (FAILED(Text_Initialize()))			return E_FAIL;

	Timer01 = 0.f;
	ContextPassing = 0;

	return S_OK;
}
INT			NPCTalk::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}
VOID		NPCTalk::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID		NPCTalk::Render_GameObject() {
	Component_Sprite->Render_Sprite();
}

VOID NPCTalk::Activate_NPCTalk(NPC_CHARACTER _NPCC, FLOAT _DT) {
	FontObject* Name = FontManager::GetInstance()->Find_FontObject(L"Personal Name");
	FontObject* Talk = FontManager::GetInstance()->Find_FontObject(L"TALK");
	if (_NPCC == NPC_CHARACTER::NPC_TIF) {
		Timer01 += _DT;
		if (KEY_DOWN(DIK_E)) { ContextPassing++; }

		Make_ShadowOutline(Timer01);
		if (ContextPassing == 0){
			Name->Text = L"시간의 사도";
			Talk->Text = L"포근한 기운이 느껴진다..";
		}
		if (ContextPassing == 1) {
			Name->Text = L"시간의 사도";
			Talk->Text = L"모두 함께 기도합시다...";
		}
		//if (ContextPassing == 2) {
		//	Name->Text = L"이라";
		//	Talk->Text = L"";
		//}
	}
	else {

	}
}

VOID NPCTalk::Make_ShadowOutline(FLOAT _Timer) {
	SpriteINFO* BackGround = Component_Sprite->Get_Texture(L"NPCTalk_BackGround");
	SpriteINFO* GRD_Top = Component_Sprite->Get_Texture(L"FrameGradation_Top");
	SpriteINFO* GRD_Bottom = Component_Sprite->Get_Texture(L"FrameGradation_Bottom");

	SpriteINFO* Sprite_Yeon = Component_Sprite->Get_Texture(L"NPCTalk_Yeon");
	SpriteINFO* Sprite_Tif = Component_Sprite->Get_Texture(L"NPCTalk_Tif");

	SpriteINFO* NameBar = Component_Sprite->Get_Texture(L"NameBar");
	SpriteINFO* Square = Component_Sprite->Get_Texture(L"TalkPass_Square");

	FontObject* Name = FontManager::GetInstance()->Find_FontObject(L"Personal Name");
	FontObject* Talk = FontManager::GetInstance()->Find_FontObject(L"TALK");

	if (_Timer < 1.f) {
		BackGround->Set_Opacity(_Timer * 150);
		GRD_Top->Set_Opacity(_Timer * 255);
		GRD_Bottom->Set_Opacity(_Timer * 255);
		Sprite_Yeon->Set_Opacity(_Timer * 255);
		Sprite_Tif->Set_Opacity(_Timer * 255);
	}
	else if (_Timer > 1.f && _Timer < 2.f) {
		NameBar->Set_Visible(TRUE);
		Square->Set_Visible(TRUE);
		Name->Set_Color(255 * (_Timer - 1), 255, 255, 255);
		Talk->Set_Color(150 * (_Timer - 1), 255, 255, 255);
	}
}

HRESULT NPCTalk::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;
	return S_OK;
}
HRESULT NPCTalk::Sprite_Initialize() {
	wstring BaseFolder = L"../../UI/NPCDialog/";

	Component_Sprite->Import_SpriteEX(BaseFolder, L"NPCTalk_BackGround.png", L"NPCTalk_BackGround", 0.f, 0.f, 1280, 720, TRUE, 0);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"NPCTalk_Yeon.png", L"NPCTalk_Yeon", -60.f, 100.f, 617, 1221, TRUE, 0);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"FrameGradation.png", L"FrameGradation_Top", -150.f, -1150.f, 1620, 1280, TRUE, 0);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"NPCTalk_Tif.png", L"NPCTalk_Tif", 797.f, 105.f, 520, 1221, TRUE, 0);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"FrameGradation.png", L"FrameGradation_Bottom", -150.f, 450.f, 1620, 1620, TRUE, 0);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"NameBar.png", L"NameBar", 565.f, 535.f, 150, 10, FALSE, 200);
	Component_Sprite->Import_SpriteEX(BaseFolder, L"TalkPass_Square.png", L"TalkPass_Square", 628.f, 660.f, 25, 25, FALSE, 200);

	return S_OK;
}
HRESULT NPCTalk::Effect_Initialize() {
	return S_OK;
}
HRESULT NPCTalk::Text_Initialize() {
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 643, 502.f }, 28, L"Personal Name", L"08서울한강체 L", D3DCOLOR_ARGB(0, 255, 255, 255), 600);
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 640, 560.f }, 20, L"TALK", L"08서울한강체 L", D3DCOLOR_ARGB(0, 255, 255, 255));
	return S_OK;
}

NPCTalk* NPCTalk::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	NPCTalk* NPT = new NPCTalk(_GRPDEV);
	if (FAILED(NPT->Ready_GameObject())) {
		MSG_BOX("Cannot Create NPCTalk.");
		Safe_Release(NPT);
		return nullptr;
	}
	return NPT;
}

VOID	NPCTalk::Free() {
	GameObject::Free();
}