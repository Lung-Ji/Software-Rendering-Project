#pragma once
#include "Scene.h"

class MapScene : public Scene
{

class MapScene : public Scene {
protected:
	explicit MapScene(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual ~MapScene();

public:
	virtual	HRESULT		Ready_Scene();
	virtual INT			Update_Scene(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Scene(CONST FLOAT& _DT);
	virtual VOID		Render_Scene();

private:
	HRESULT		Ready_Enviroment_Layer(CONST TCHAR* _LTAG);
	HRESULT		Ready_GameLogic_Layer(CONST TCHAR* _LTAG);
	HRESULT		Ready_UserInterface_Layer(CONST TCHAR* _LTAG);

public:
	static	MapScene* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual void Free();
in
};

