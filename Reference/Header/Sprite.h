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
		POS{ _POSX, _POSY, 0.f }, OPACITY(_OPACITY), TEXTURE(nullptr), Visible(VIS){
	}
};
class ENGINE_DLL SpriteObject: public Component {
private:
	explicit SpriteObject();
	explicit SpriteObject(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit SpriteObject(CONST SpriteObject& _RHS);
	virtual ~SpriteObject();

public:
	HRESULT		Ready_Sprite();
	INT			Update_Sprite();
	VOID		Render_Sprite();

	HRESULT		Import_Sprite(CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY = 255);
public:
	static		SpriteObject*		Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component*			Clone();

private:
	ID3DXSprite*			Sprite;
	vector<SpriteINFO>		TextureList;
private:
	virtual		VOID		Free();
};


END