#pragma once
#include "GameObject.h"

class Inventory : public GameObject {
private:
	explicit Inventory(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Inventory(CONST GameObject& _RHS);
	virtual ~Inventory();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Effect_Initialize();

	static	Inventory* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject*		Component_Sprite;
	vector<SpriteINFO>* TextureList;
	GameObject*			Armed_Space[8];
	GameObject*			Saved_Space[10];
	BOOL				Activate_Inventory;

	FLOAT				BackGround_Opacity;
private:
	virtual	VOID		Free();
};

