#pragma once
#include "GameObject.h"

class ShopUI : public GameObject {
private:
	explicit ShopUI(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit ShopUI(CONST GameObject& _RHS);
	virtual ~ShopUI();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT				Component_Initialize();
	HRESULT				Sprite_Initialize();
	HRESULT				Effect_Initialize();
	HRESULT				Text_Initialize();
public:
	static	ShopUI*		Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject*	Component_Sprite;

private:
	virtual	VOID		Free();
};
