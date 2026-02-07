#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

struct ENGINE_DLL KeyINFO {
	KEY_STATE	Current_KeyState;
	BOOL		Prev_KeyState;
};
class ENGINE_DLL KeyManager : public Base {
	DECLARE_SINGLETON(KeyManager)
private:
	explicit KeyManager(void);
	virtual ~KeyManager(void);

public:
	HRESULT			Ready_KeyManager(HINSTANCE hInst, HWND hWnd);
	VOID			Update_KeyManager(CONST FLOAT& _DT);
	VOID			LateUpdate_KeyManager(CONST FLOAT& _DT);

	_byte			Get_KeyState(_ubyte _KID)				{ return KeyState[_KID];					}
	_byte			Get_MouseState(MOUSEKEYSTATE _MID)		{ return MouseState.rgbButtons[_MID];		}
	LONG			Get_MouseMove(MOUSEMOVESTATE _MID)		{ return *(((_long*)&MouseState) + _MID);	}

	KEY_STATE GetKeyState(KEY key)							{ return KeySet[(int)key].Current_KeyState; };

public:
	BOOL	KEY_STATE_HOLD(_ubyte _KEY) { return KeyState[_KEY] & 0x80 ? TRUE : FALSE; }
	BOOL	KEY_STATE_DOWN(_ubyte _KEY);
	BOOL	KEY_STATE_UP(_ubyte _KEY);

	BOOL	MOUSE_LB_DOWN();
	BOOL	MOUSE_RB_DOWN();

private:
	BOOL						 KEY_STATE[256];
	vector<KeyINFO>				 KeySet;

	LPDIRECTINPUT8				 InputSDK = nullptr;
	LPDIRECTINPUTDEVICE8		 KeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8		 Mouse	  = nullptr;
	_byte						 KeyState[256];

	DIMOUSESTATE				 MouseState;
	BOOL						 MouseClickedR;
	BOOL						 MouseClickedL;

public:
	virtual			VOID	Free();
};

END