#include "../Include/PCH.h"
#include "ShopUI.h"

ShopUI::ShopUI(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
ShopUI::ShopUI(CONST GameObject& _RHS)		: GameObject(_RHS)		{}
ShopUI::~ShopUI()													{}

HRESULT	ShopUI::Ready_GameObject() {
	return S_OK;
}
INT		ShopUI::Update_GameObject(CONST FLOAT& _DT) {
	return 0;
}
VOID	ShopUI::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	ShopUI::Render_GameObject() {

}

HRESULT	ShopUI::Component_Initialize() {
	return S_OK;
}
HRESULT	ShopUI::Sprite_Initialize() {
	return S_OK;
}
HRESULT	ShopUI::Effect_Initialize() {
	return S_OK;
}
HRESULT	ShopUI::Text_Initialize() {
	return S_OK;
}

VOID	ShopUI::Free() {

}