#include "Font.h"

FontObject::FontObject() : Sprite(nullptr){};
FontObject::FontObject(LPDIRECT3DDEVICE9 _GRPDEV)	:Component(_GRPDEV), Sprite(nullptr) {}
FontObject::FontObject(CONST Component& _RHS){}
FontObject::~FontObject() {}

HRESULT FontObject::Ready_Font(const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight)
{

	D3DXFONT_DESC			tFont_Desc;
	ZeroMemory(&tFont_Desc, sizeof(D3DXFONT_DESC));

	tFont_Desc.CharSet = HANGUL_CHARSET;
	tFont_Desc.Width = iWidth;
	tFont_Desc.Height = iHeight;
	tFont_Desc.Weight = iWeight;
	lstrcpy(tFont_Desc.FaceName, pFontType);

	if (FAILED(D3DXCreateFontIndirect(GRPDEV, &tFont_Desc, &Font)))
	{
		MSG_BOX("Font Create Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(GRPDEV, &Sprite)))
	{
		MSG_BOX("Sprite Create Failed");
		return E_FAIL;
	}

  return S_OK;
}

void FontObject::Render_Font(const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color)
{
	RECT rc{ (_long)pPos->x, (_long)pPos->y };

	Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	Font->DrawTextW(Sprite, pString, lstrlen(pString), &rc, DT_NOCLIP, Color);

	Sprite->End();

}

FontObject* FontObject::Create(LPDIRECT3DDEVICE9 GRPDEV, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight)
{
	FontObject* pFont = new FontObject(GRPDEV);
	if (FAILED(pFont->Ready_Font(pFontType,iWidth,iHeight,iWeight))) {
		MSG_BOX("ÆùÆ® ¸ø¸Í±Ý");
		Safe_Release(pFont);
		return nullptr;
	}
  return pFont;
}

FontObject* FontObject::Clone()
{
	return new FontObject(*this);
}
void FontObject::Free()
{
	Component::Free();
}