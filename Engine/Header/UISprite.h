#pragma once
#include "Component.h"

BEGIN(Engine)

struct ENGINE_DLL SpriteINFO {
	wstring					PATH;
	UINT					WIDTH, HEIGHT;
	D3DXVECTOR3				POS;
	INT						OPACITY;
	LPDIRECT3DTEXTURE9		TEXTURE;
	BOOL								Visible;

	SpriteINFO(CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
		FLOAT _POSX, FLOAT _POSY, BOOL VIS, INT _OPACITY = 255)
		: PATH(_PATH), WIDTH(_WIDTH), HEIGHT(_HEIGHT),
		POS{ _POSX, _POSY, 0.f }, OPACITY(_OPACITY), TEXTURE(nullptr), Visible(VIS) {
	}
};
class UISprite :  public Component
{
private:
  explicit UISprite();
	explicit UISprite(LPDIRECT3DDEVICE9 _GRPDEV);
  virtual ~UISprite();

public:
	HRESULT	Ready_UI(CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
		FLOAT _POSX, FLOAT _POSY, BOOL VIS, INT _OPACITY);
	INT			Update_Sprite();
	VOID		Render_Sprite();

public:
  static  UISprite* Create(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
		FLOAT _POSX, FLOAT _POSY, BOOL VIS, INT _OPACITY);
  virtual Component* Clone();
private:
  ID3DXSprite* Sprite;

private:
	virtual VOID Free();
};

END