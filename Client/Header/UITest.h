#pragma once

#include "Scene.h"
class UITest :
    public Scene
{
protected:
	explicit UITest(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual ~UITest();

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
	static	UITest* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual void Free();

};