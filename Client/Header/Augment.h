#pragma once
#include "GameObject.h"

class Augment : public GameObject {
	explicit Augment(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Augment(CONST GameObject& _RHS);
	virtual ~Augment();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Text_Initialize();
	HRESULT Item_Initialize();

public:
	static	Augment* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	SpriteObject* Component_Sprite;

private:
	virtual	VOID		Free();
};