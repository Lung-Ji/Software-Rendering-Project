#pragma once
#include "Scene.h"

class DebugScene : public Scene {
protected:
	explicit DebugScene(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual ~DebugScene();

public:
	virtual	HRESULT		Ready_Scene();
	virtual INT			Update_Scene(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Scene(CONST FLOAT& _DT);
	virtual VOID		Render_Scene();

private:
	HRESULT		Ready_Enviroment_Layer();
	HRESULT		Ready_GameLogic_Layer();
	HRESULT		Ready_UserInterface_Layer();

public:
	static	DebugScene* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual void Free();
};

