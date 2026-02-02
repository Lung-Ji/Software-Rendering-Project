#include "KeyManager.h"
IMPLEMENT_SINGLETON(KeyManager)

KeyManager::KeyManager(void) {
	ZeroMemory(KEY_STATE, sizeof(KEY_STATE));;
}
KeyManager::~KeyManager(void) { Free(); }
int KeyMapping[(int)KEY::LAST] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, // 0 - 9
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
			'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
	VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_MENU,
	VK_ESCAPE, VK_SPACE, VK_RETURN,
	VK_LBUTTON, VK_RBUTTON,
};
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

	return S_OK;
}
VOID KeyManager::Update_KeyManager(CONST FLOAT& _DT) {
	KeyBoard->GetDeviceState(256, KeyState);
	Mouse	->GetDeviceState(sizeof(MouseState), &MouseState);
}

VOID KeyManager::LateUpdate_KeyManager(CONST FLOAT& _DT) {
	for (int i = 0; i < 256; ++i) {
		if (KEY_STATE[i] && !(KeyState[i] & 0x80))
			KEY_STATE[i] = !KEY_STATE[i];

		if (!KEY_STATE[i] && (KeyState[i] & 0x80))
			KEY_STATE[i] = !KEY_STATE[i];
	}
}

BOOL KeyManager::KEY_STATE_DOWN(_ubyte _KEY) {
	if (!KEY_STATE[_KEY] && KeyState[_KEY] & 0x80) {
		KEY_STATE[_KEY] = !KEY_STATE[_KEY];
		return true;
	}
	return false;
}
BOOL KeyManager::KEY_STATE_UP(_ubyte _KEY) {
	if (KEY_STATE[_KEY] && !(KeyState[_KEY] & 0x80)) {
		KEY_STATE[_KEY] = !KEY_STATE[_KEY];
		return true;
	}
	return false;
}
VOID KeyManager::Free() {
	Safe_Release(KeyBoard);
	Safe_Release(Mouse);
	Safe_Release(InputSDK);
}