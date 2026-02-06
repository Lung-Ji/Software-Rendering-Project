#pragma once
#include "Scene.h"

class StartScene : public Scene {
protected:
	explicit StartScene(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual ~StartScene();

public:
	virtual	HRESULT		Ready_Scene();
	virtual INT			Update_Scene(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Scene(CONST FLOAT& _DT);
	virtual VOID		Render_Scene();

private:
	HRESULT		Ready_Enviroment_Layer();
	HRESULT		Ready_GameLogic_Layer();
	HRESULT		Ready_UserInterface_Layer();

	HRESULT		Ready_Tile_Layer(CONST TCHAR* _LTAG);

public:
	static	StartScene* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual void Free();
};

