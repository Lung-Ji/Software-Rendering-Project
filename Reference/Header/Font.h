#pragma once

#include "Component.h"

BEGIN(Engine)
struct ENGINE_DLL FontINFO {
  wstring MSG;
  UINT  WEIGHT, WIDTH, MIPLEVELS;
  BOOL  ITALIC;
  DWORD CHARSET;
  DWORD OUTPUTPRECISION;
  DWORD QUALITY;
  DWORD PITCHANDFAMILY;
  LPCWSTR FACENAME;
  _vec2   POS;
  D3DXCOLOR COLOR;
  LPD3DXFONT FONT;

  FontINFO(CONST TCHAR* _msg, UINT _weight, UINT _width,_vec2 _pos ) 
    :MSG(_msg),
    WEIGHT(_weight), 
    WIDTH(_width), 
    POS(_pos),
    MIPLEVELS(1),
    COLOR(1.f,1.f,1.f,1.f),
    ITALIC(false), 
    CHARSET(HANGUL_CHARSET),
    OUTPUTPRECISION(1), 
    QUALITY(DEFAULT_QUALITY),
    PITCHANDFAMILY(DEFAULT_PITCH),
    FACENAME(L"Times New Roman"),
    FONT(nullptr) {}
};

class ENGINE_DLL FontObject : public Component {
private:
  explicit FontObject();
  explicit FontObject(LPDIRECT3DDEVICE9 _GRPDEV);
  explicit FontObject(CONST Component& _RHS);
  virtual ~FontObject();

public:
  HRESULT Ready_Font(const _tchar* pFontType,
    const _uint& iWidth,
    const _uint& iHeight,
    const _uint& iWeight);

  void Render_Font();

  HRESULT Import_Font(CONST TCHAR* _msg, UINT _weight, UINT _width, const _vec2 _pos);


public:
  static FontObject* Create(LPDIRECT3DDEVICE9 GRPDEV,
    const _tchar* pFontType,
    const _uint& iWidth,
    const _uint& iHeight,
    const _uint& iWeight);

private:
  virtual void Free();
  virtual	FontObject* Clone();

private:
  LPD3DXFONT		Font;		
  ID3DXSprite* Sprite;
  vector<FontINFO> FontList;
};

END