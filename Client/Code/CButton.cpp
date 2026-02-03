#include "../Include/PCH.h"
#include "CButton.h"

CButton::CButton(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_pBuffer(nullptr), m_pTransform(nullptr) {}
CButton::CButton(const GameObject& _RHS) : GameObject(_RHS) {}
CButton::~CButton() { Free(); }

HRESULT CButton::Ready_GameObject() {

	if (FAILED(Component_Initialize())) return E_FAIL;

	return S_OK;
}

INT	CButton::Update_GameObject(const _float& _DT) {

	POINT ptMouse;

	if (KeyManager::GetInstance()->Get_MouseState(DIM_LB)
		&& (0x80 && GetCursorPos(&ptMouse)))
	{
		m_bCheckMouse = true;
	}

	GameObject::Update_GameObject(_DT);	
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	return 0;
}

VOID CButton::LateUpdate_GameObject(const _float& _DT) {

	GameObject::LateUpdate_GameObject(_DT);
}

VOID CButton::Render_GameObject()
{
	Component_Sprite->Render_Sprite();
}

HRESULT CButton::Component_Initialize() {
	Component_Sprite = ADD_COMPONENT_SPRITE;
	
	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Spiki.png", 100, 100, 640, 360);
	Component_Sprite->Import_Sprite(L"../../Resource/Extra/Example/Spiki_Push.png", 100, 100, 700, 360);
	
	return S_OK;
}

CButton* CButton::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	CButton* pButton = new CButton(_GRPDEV);
	if (FAILED(pButton->Ready_GameObject())) {
		MSG_BOX("Cannot Create CButton.");
		Safe_Release(pButton);
		return nullptr;
	}
	return pButton;
}
VOID CButton::Free() {
	GameObject::Free();
}