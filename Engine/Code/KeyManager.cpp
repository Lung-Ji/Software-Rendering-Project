#include "KeyManager.h"
IMPLEMENT_SINGLETON(KeyManager)

KeyManager::KeyManager(void) {
	ZeroMemory(KEY_STATE, sizeof(KEY_STATE));
}
KeyManager::~KeyManager(void) { Free(); }

HRESULT KeyManager::Ready_KeyManager(HINSTANCE hInst, HWND hWnd) {
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&InputSDK, NULL)))	return E_FAIL;
	
	if (FAILED(InputSDK->CreateDevice(GUID_SysKeyboard, &KeyBoard, nullptr)))	return E_FAIL;
	if (FAILED(InputSDK->CreateDevice(GUID_SysMouse, &Mouse, nullptr)))			return E_FAIL;
	
	KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	KeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	KeyBoard->Acquire();
	
	Mouse->SetDataFormat(&c_dfDIMouse);
	Mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	Mouse->Acquire();

	MouseClickedR = FALSE;
	MouseClickedL = FALSE;

	return S_OK;
}
VOID KeyManager::Update_KeyManager(CONST FLOAT& _DT) {
	for (int i = 0; i < 256; ++i) {
		if (KEY_STATE[i] && !(KeyState[i] & 0x80))
			KEY_STATE[i] = !KEY_STATE[i];

		if (!KEY_STATE[i] && (KeyState[i] & 0x80))
			KEY_STATE[i] = !KEY_STATE[i];
	}
	if (!(KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80)) {
		MouseClickedL = FALSE;
	}
	if (!(KeyManager::GetInstance()->Get_MouseState(DIM_RB) & 0x80)) {
		MouseClickedR = FALSE;
	}
	KeyBoard->GetDeviceState(256, KeyState);
	Mouse	->GetDeviceState(sizeof(MouseState), &MouseState);
}

VOID KeyManager::LateUpdate_KeyManager(CONST FLOAT& _DT) {
	
}

BOOL KeyManager::KEY_STATE_DOWN(_ubyte _KEY) {
	if (!KEY_STATE[_KEY] && (KeyState[_KEY] & 0x80)) {
		KEY_STATE[_KEY] = !KEY_STATE[_KEY];
		return TRUE;
	}
	return false;
}
BOOL KeyManager::KEY_STATE_UP(_ubyte _KEY) {
	if (KEY_STATE[_KEY] && !(KeyState[_KEY] & 0x80)) {
		KEY_STATE[_KEY] = !KEY_STATE[_KEY];
		return true;
	}
	return FALSE;
}
BOOL KeyManager::MOUSE_LB_DOWN() {
	if (MouseClickedL == FALSE && KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80) {
		MouseClickedL = TRUE;
		return TRUE;
	}

	return FALSE;
}
BOOL KeyManager::MOUSE_RB_DOWN() {
	if (MouseClickedR == FALSE && KeyManager::GetInstance()->Get_MouseState(DIM_RB) & 0x80) {
		MouseClickedR = TRUE;
		return TRUE;
	}
	return FALSE;
}

VOID KeyManager::Free() {
	Safe_Release(KeyBoard);
	Safe_Release(Mouse);
	Safe_Release(InputSDK);
}