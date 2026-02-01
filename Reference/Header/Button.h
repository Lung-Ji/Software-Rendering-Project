#pragma once
#include "Component.h"

BEGIN(Engine)
struct ENGINE_DLL SpriteINFO {
	wstring					PATH;
	UINT					WIDTH, HEIGHT;
	D3DXVECTOR3				POS;
	INT						OPACITY;
	LPDIRECT3DTEXTURE9		TEXTURE;

	SpriteINFO(CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
		FLOAT _POSX, FLOAT _POSY, INT _OPACITY = 255)

		: PATH(_PATH), WIDTH(_WIDTH), HEIGHT(_HEIGHT),
		POS{ _POSX, _POSY, 0.f }, OPACITY(_OPACITY), TEXTURE(nullptr) {
	}
};
class ENGINE_DLL ButtonObject : public Component {
private:
	explicit ButtonObject();
	explicit ButtonObject(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit ButtonObject(CONST ButtonObject& _RHS);
	virtual ~ButtonObject();

public:
	HRESULT		Ready_Sprite();
	INT			Update_Sprite();
	VOID		Render_Sprite();

	HRESULT		Import_Sprite(CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, INT _OPACITY = 255);
public:
	static		ButtonObject* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component* Clone();

private:
	ID3DXSprite*			Sprite;
	vector<SpriteINFO>		TextureList;
private:
	virtual		VOID		Free();
};


END