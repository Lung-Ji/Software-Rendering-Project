#include "FontManager.h"

IMPLEMENT_SINGLETON(FontManager);

FontManager::FontManager()	: DXSprite(nullptr)	{			}
FontManager::~FontManager()						{	Free();	}

HRESULT FontManager::Ready_FontManager(LPDIRECT3DDEVICE9 _GRPDEV) {

	if (FAILED(D3DXCreateSprite(_GRPDEV, &DXSprite))) {
		MSG_BOX("Cannot Create FontSprite.");
		return E_FAIL;
	}
	return S_OK;
}
INT FontManager::Update_FontManager(const FLOAT& _DT) {

	return 0;
}
VOID FontManager::LateUpdate_FontManager(const FLOAT& _DT) {

}
VOID FontManager::Render_FontManager() {
	DXSprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (auto& TXT : FontList) {
		if (TXT.second->Visible == TRUE) {
			FLOAT XPos = TXT.second->Position.x;
			FLOAT YPos = TXT.second->Position.y;
			RECT RT = { XPos, YPos, XPos + 1, YPos + 1 };
			TXT.second->DXFont->DrawTextW(DXSprite, TXT.second->Text.c_str(), -1, &RT, DT_CENTER | DT_NOCLIP, TXT.second->TextColor);
		}
	}

	DXSprite->End();
}
HRESULT FontManager::Add_FontSprite(LPDIRECT3DDEVICE9 _GRPDEV, wstring _Text, _vec2 _Position, _int _TextScale, wstring _FontTag, wstring _FontType, D3DCOLOR _Color, _int TextWeight, BOOL _Visible) {

	FontObject* FO = new FontObject(_Position, _Text, _TextScale, TextWeight, _FontTag, _FontType, _Color, _Visible);

	D3DXFONT_DESCW FontInfo;
	ZeroMemory(&FontInfo, sizeof(FontInfo));

	FontInfo.Height = FO->TextScale;
	FontInfo.Weight = FO->TextWeight;
	FontInfo.CharSet = HANGUL_CHARSET;
	FontInfo.OutputPrecision = OUT_DEFAULT_PRECIS;
	FontInfo.Quality = DEFAULT_QUALITY;
	FontInfo.PitchAndFamily = DEFAULT_PITCH | FW_DONTCARE;

	lstrcpyW(FontInfo.FaceName, FO->FontType.c_str());

	if (FAILED(D3DXCreateFontIndirectW(_GRPDEV, &FontInfo, &FO->DXFont))) {
		MSG_BOX("Cannot Create FontObject.");
		return E_FAIL;
	}

	FontList.insert({ FO->FontTag.c_str(), FO });

	return S_OK;
}
FontObject* FontManager::Find_FontObject(wstring _Text) {
	auto iter = find_if(FontList.begin(), FontList.end(), CTag_Finder(_Text.c_str()));
	if (iter == FontList.end())	return nullptr;
	return iter->second;
}
VOID FontManager::Free() {
	for (auto& FO : FontList) 
		Safe_Delete(FO.second);
}