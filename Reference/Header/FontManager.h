#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
ENGINE_DLL class FontManager : public Base{
  DECLARE_SINGLETON(FontManager)
private:
  explicit FontManager();
  virtual  ~FontManager();

public:
  HRESULT Ready_FontManager(LPDIRECT3DDEVICE9 _GRPDEV, INT _height, UINT Width, TCHAR _facename);
  VOID    Draw_Text(LPCSTR _string, INT _count, LPRECT pRect, DWORD _format, D3DCOLOR _color);
  VOID    Update_FontManager();
  
private:
  LOGFONT Font;
};

END

