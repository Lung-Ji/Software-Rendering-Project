#pragma once
#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL FontManager : public Component
{
  DECLARE_SINGLETON(FontManager)
private:
  explicit FontManager();
  explicit FontManager(LPDIRECT3DDEVICE9 _GRPDEV);
 // explicit FontManager(CONST FontManager& _RHS);
  virtual  ~FontManager();

public:
  HRESULT Ready_FontManager(LPD3DXFONT* ppFont, LPDIRECT3DDEVICE9 _GRPDEV, INT _height, UINT _width, UINT _weight);
  HRESULT Draw_Text(CONST TCHAR* _string, INT _count, LPRECT pRect, DWORD _format, D3DCOLOR _color);
  
private:

private:
  virtual VOID Free();
};

END

