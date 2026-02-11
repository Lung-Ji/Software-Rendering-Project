#include "Font.h"

FontObject::FontObject() : Sprite(nullptr){}
FontObject::FontObject(LPDIRECT3DDEVICE9 _GRPDEV)	:Component(_GRPDEV), Sprite(nullptr) {}
FontObject::FontObject(CONST Component& _RHS):Component(_RHS){}
FontObject::~FontObject() {}

HRESULT FontObject::Ready_Font(const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight)
{
	if (FAILED(D3DXCreateSprite(GRPDEV, &Sprite)))
	{
		MSG_BOX("Font Create Failed");
		return E_FAIL;
	}

	return S_OK;
}

void FontObject::Render_Font()
{
	GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (auto& FONT : FontList) {
		Font->DrawTextW(Sprite, FONT.MSG.c_str(), lstrlen(FONT.MSG.c_str()), (LPRECT)&FONT.POS, DT_NOCLIP, FONT.COLOR);
	}

	Sprite->End();
	GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT FontObject::Import_Font(CONST TCHAR* _msg, UINT _weight, UINT _width, const _vec2 _pos){
	FontList.push_back(FontINFO(_msg, _weight, _width, _pos));

	D3DXCreateFont(GRPDEV, 12, FontList.back().WIDTH, FontList.back().WEIGHT, FontList.back().MIPLEVELS, FontList.back().ITALIC, FontList.back().CHARSET,
		FontList.back().OUTPUTPRECISION, FontList.back().QUALITY, FontList.back().PITCHANDFAMILY, FontList.back().FACENAME, &FontList.back().FONT);

	return S_OK;
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
void FontObject::Free(){
	Component::Free();
}