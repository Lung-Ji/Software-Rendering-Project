#pragma once
#include "GameObject.h"
class MainMenuLogo :   public GameObject
{
private:	
	explicit MainMenuLogo(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MainMenuLogo(CONST GameObject& _RHS);
	virtual ~MainMenuLogo();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();

	static	MainMenuLogo* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;

private:
	virtual	VOID		Free();

};

