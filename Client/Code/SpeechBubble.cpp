#include"../Include/PCH.h"
#include "SpeechBubble.h"

SpeechBubble::SpeechBubble(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
SpeechBubble::SpeechBubble(CONST GameObject& _RHS) : GameObject(_RHS) {}
SpeechBubble::~SpeechBubble() {}

HRESULT	SpeechBubble::Ready_GameObject() {
	if (FAILED(Component_Initialize()))		return E_FAIL;
	if (FAILED(Text_Initialize()))				return E_FAIL;
	if (FAILED(Sprite_Initialize()))		return E_FAIL;
	return S_OK;
}
INT		SpeechBubble::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
	return 0;
}
VOID	SpeechBubble::LateUpdate_GameObject(CONST FLOAT& _DT) {
}
VOID	SpeechBubble::Render_GameObject() {
	Component_Sprite->Render_Sprite();

	FontObject* pContent = FontManager::GetInstance()->Find_FontObject(L"asd");
	if (pContent)
	{
		pContent->Text = L"어서오세요!";
		pContent->Visible = TRUE;
	}
}
HRESULT SpeechBubble::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;
	return S_OK;
}
HRESULT SpeechBubble::Sprite_Initialize() {
	Component_Sprite->Import_Sprite(L"../../UI/NPCDialog/Spr_Ui_SpeechBubble_FaceFrame.png", L"Shop_Dialog", 400.f, 400.f, 350, 120, TRUE);
	return S_OK;
}
HRESULT SpeechBubble::Text_Initialize() {
	FontManager::GetInstance()->Add_FontSprite(GRPDEV, L"", { 600.f,450.f }, 20, L"asd", L"08서울한강체 L", D3DCOLOR_ARGB(255, 0, 0, 0));
	return S_OK;
}
SpeechBubble* SpeechBubble::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	SpeechBubble* SB = new SpeechBubble(_GRPDEV);
	if (FAILED(SB->Ready_GameObject())) {
		MSG_BOX("Cannot Create SpeechBubble.");
		Safe_Release(SB);
		return nullptr;
	}
	return SB;
}
VOID	SpeechBubble::Free() {
	GameObject::Free();
}