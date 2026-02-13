#pragma once
#include "Scene.h"

class DoCheolScene : public Scene {
protected:
	explicit DoCheolScene(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual ~DoCheolScene();

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
	static	DoCheolScene* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual void Free();
};

