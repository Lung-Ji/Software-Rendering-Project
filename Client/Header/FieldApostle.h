#pragma once
#include "GameObject.h"
class FieldApostle :  public GameObject
{
private:
	explicit FieldApostle(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit FieldApostle(CONST GameObject& _RHS);
	virtual ~FieldApostle();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Effect_Initialize();
	HRESULT	Text_Initialize();

	VOID Make_ShadowOutLine();

	static	FieldApostle* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;
	vector<SpriteINFO>* TextureList;

private:
	VOID Free();
};

