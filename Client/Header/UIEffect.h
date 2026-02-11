#pragma once
#include "GameObject.h"

struct EffectINFO {
	wstring					KEY;
	UINT					WIDTH, HEIGHT;
	D3DXVECTOR3				POS;
	INT						OPACITY;
	LPDIRECT3DTEXTURE9		TEXTURE;
	BOOL					VISIBLE;
	
	EffectINFO(wstring _KEY, UINT _WIDTH, UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY = 255)
		: KEY(_KEY), WIDTH(_WIDTH), HEIGHT(_HEIGHT), POS{ _POSX, _POSY, 0.f }, OPACITY(_OPACITY), TEXTURE(nullptr), VISIBLE(_VIS) {}

	VOID	Set_Pos(FLOAT _X, FLOAT _Y) { POS.x = _X, POS.y = _Y; }
	D3DXVECTOR3	Get_Pos() { return { POS.x, POS.y, 0.f }; }
	VOID	Move_Pos(FLOAT _TX, FLOAT _TY, FLOAT _Speed) {
		if(POS.x > _TX){
			POS.x -= _Speed;
		}
	}

	VOID	Set_Scale(FLOAT _X, FLOAT _Y)	{ WIDTH = _X, HEIGHT = _Y;					}

	VOID	Set_Opacity(FLOAT _V)			{ OPACITY = _V;								}
	VOID	Decrease_Opacity(FLOAT _V)		{ if (OPACITY > 0)	OPACITY -= _V;			}
	VOID	QuickDecrease_Opacity(FLOAT _V) { while (OPACITY > 0.f) { OPACITY -= _V; }	}

	VOID	Set_Visible(BOOL  _B)			{ VISIBLE = _B;								}
};

class UIEffect : public GameObject {
private:
	explicit UIEffect(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit UIEffect(CONST GameObject& _RHS);
	virtual ~UIEffect();

public:
	virtual			HRESULT		Ready_GameObject() { return S_OK; }
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();
public:
	// Initialize
	HRESULT						Ready_Effect(MAIN_UI_EFFECT _EFTTYPE, wstring _TAG, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _UISCALE, INT _OPAC, BOOL _Repeatable, FLOAT _PlayTime);
	HRESULT						Make_TextureList(wstring _PATH, wstring _KEY, FLOAT _POSX, FLOAT _POSY, UINT _WIDTH, UINT _HEIGHT, BOOL _VIS, INT _OPACITY);
	static	UIEffect*			Create(LPDIRECT3DDEVICE9 _GRPDEV, wstring _TAG, MAIN_UI_EFFECT _SKILLTYPE, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _SCALE, INT _OPACITY, BOOL _Repeatable, FLOAT _PlayTime);
public:
	// Utility
	static	VOID				Replay_Effect(wstring _TAG);
private:
	HRESULT						Component_Initialize();
	virtual			VOID		Free();
private:
	MAIN_UI_EFFECT		SKILL_TYPE;
	INT					ENDFRAME;
	vector<EffectINFO>	TextureList;

	INT				TextureIndex;
	FLOAT			FrameTick;
	FLOAT			PlayTime;
	BOOL			Repeatable;

	ID3DXSprite*	Sprite;

	D3DXMATRIX		MatTransform;
	D3DXMATRIX		MatPos;
	D3DXMATRIX		MatScale;

	SpriteObject*	Component_Sprite;
};

