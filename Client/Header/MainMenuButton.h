#pragma once
#include "GameObject.h"
class MainMenuButton : public GameObject
{
private:
	explicit MainMenuButton(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MainMenuButton(CONST GameObject& _RHS);
	virtual ~MainMenuButton();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();

	static	MainMenuButton* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;

private:
	virtual	VOID		Free();
};

