#include "Font.h"

FontObject::~FontObject()
{
}

HRESULT FontObject::Ready_Font(const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight)
{
  D3DXFONT_DESC   Font_Desc;
  ZeroMemory(&Font_Desc, sizeof(D3DXFONT_DESC));
  



  D3DXCreateFontIndirect(GRPDEV, &Font_Desc, &Font);
  return S_OK;
}

void FontObject::Render_Font(const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color)
{

}
