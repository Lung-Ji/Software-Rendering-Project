#pragma once
#include "GameObject.h"

struct EffectINFO {
	LPDIRECT3DTEXTURE9 BaseTexture;
	D3DXVECTOR3	Pos;
	D3DXVECTOR3 Scale;
	INT			Opacity;

	EffectINFO(LPDIRECT3DTEXTURE9 _BaseTexture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _Scale, INT _Opacity)
		: BaseTexture(_BaseTexture), Pos(_Pos), Scale(_Scale), Opacity(_Opacity) {}
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
	HRESULT						Ready_Effect(UI_EFFECT _EFTTYPE, wstring _TAG, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _UISCALE, INT _OPAC, BOOL _Repeatable, FLOAT _PlayTime);
	HRESULT						Make_TextureList(wstring _FileName, D3DXVECTOR3 _POS, D3DXVECTOR3 _SCALE, INT _OPACITY);
	static	UIEffect*			Create(LPDIRECT3DDEVICE9 _GRPDEV, wstring _TAG, UI_EFFECT _SKILLTYPE, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _SCALE, INT _OPACITY, BOOL _Repeatable, FLOAT _PlayTime);
public:
	// Utility
	static	VOID				Replay_Effect(wstring _TAG);
private:
	HRESULT						Component_Initialize();
	virtual			VOID		Free();
private:
	UI_EFFECT		SKILL_TYPE;
	INT				ENDFRAME;
	vector<EffectINFO*>	TextureList;

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

