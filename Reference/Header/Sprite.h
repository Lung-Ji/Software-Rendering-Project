#pragma once
#include "Component.h"

BEGIN(Engine)
struct ENGINE_DLL SpriteINFO {
	wstring					KEY;
	UINT					WIDTH, HEIGHT;
	D3DXVECTOR3				POS;
	INT						OPACITY;
	LPDIRECT3DTEXTURE9		TEXTURE;
	BOOL					VISIBLE;

	SpriteINFO(CONST TCHAR* _KEY, UINT _WIDTH, UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY = 255)
		: KEY(_KEY), WIDTH(_WIDTH), HEIGHT(_HEIGHT),POS{ _POSX, _POSY, 0.f }, OPACITY(_OPACITY), TEXTURE(nullptr), VISIBLE(_VIS){}

	VOID	Set_Pos(FLOAT _X, FLOAT _Y)		{ POS.x = _X, POS.y = _Y; }
	D3DXVECTOR2	Get_Pos() { return { POS.x, POS.y }; }
	VOID	Move_Pos(FLOAT _TX, FLOAT _TY, FLOAT _Speed) {
		if (POS.x > _TX) {
			POS.x -= _Speed;
		}
	}

	VOID	Set_Scale(FLOAT _X, FLOAT _Y)	{ WIDTH = _X, HEIGHT = _Y; }

	VOID	Set_Opacity(FLOAT _V) { OPACITY = _V; }
	VOID	Decrease_Opacity(FLOAT _V) { 
		if (OPACITY > 0)	
			OPACITY -= _V;
	}
	VOID	Increase_Opacity(FLOAT _V) { 
		if (OPACITY <= 254)	
			OPACITY += _V; 
		if (OPACITY > 254)
			OPACITY = 255;
	}

	VOID	Set_Visible(BOOL  _B) { VISIBLE = _B; }
};

struct ENGINE_DLL ItemINFO {
	enum ITINFO { NAME, CLASS, EFFECT01, EFFECT02, EFFECT03, DESC01, DESC02, DESC03, EXDESC, INVFRAME, INFFRAME };

	LPDIRECT3DTEXTURE9		TEXTURE;

	vector<wstring>			ItemDesc;

	_int					ItemPrice;
	_int					ItemType;

	ItemINFO() : TEXTURE(nullptr), ItemDesc{}, ItemPrice(0), ItemType(0) { ItemDesc.resize((LONG)ITINFO::INFFRAME + 1); }
	//ItemINFO(LPDIRECT3DTEXTURE9 _TXT, wstring _ItemKey, wstring _ItemName, wstring _ItemClass, wstring* _ItemEffect, wstring _ItemDesc, wstring _ItemExDesc, _int _ItemPrice)
	//	: TEXTURE(_TXT), ItemKey(_ItemKey), ItemName(_ItemName), ItemClass(_ItemClass), ItemEffect{_ItemEffect}, ItemDesc(_ItemDesc), ItemExDesc(_ItemExDesc), ItemPrice(_ItemPrice) {}
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

	SpriteINFO*		Import_Sprite(CONST TCHAR* _PATH, CONST TCHAR* _KEY, FLOAT _POSX, FLOAT _POSY, UINT _WIDTH, UINT _HEIGHT, BOOL _VIS, INT _OPACITY = 255);
	SpriteINFO*		Import_SpriteEX(wstring _RootPath, CONST TCHAR* _PATH, CONST TCHAR* _KEY, FLOAT _POSX, FLOAT _POSY, UINT _WIDTH, UINT _HEIGHT, BOOL _VIS, INT _OPACITY = 255);

	vector<SpriteINFO>* Get_TextureList() { return &TextureList; }
	SpriteINFO*			Get_Texture(wstring _KEY);
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