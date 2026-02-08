#pragma once
#include "GameObject.h"
#include "FontManager.h"

class MainUI : public GameObject {
private:
	explicit MainUI(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MainUI(CONST GameObject& _RHS);
	virtual ~MainUI();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();

	static	MainUI*		Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject*		Component_Sprite;

private:
	virtual	VOID		Free();
};

