#pragma once
#include "GameObject.h"

class MainMenu : public GameObject {
private:
	explicit MainMenu(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MainMenu(CONST GameObject& _RHS);
	virtual ~MainMenu();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();

	static	MainMenu* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;

private:
	virtual	VOID		Free();
};

