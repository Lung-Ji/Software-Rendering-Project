#pragma once
#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)
class ENGINE_DLL Layer : public Base {
private:
	explicit Layer();
	virtual ~Layer();

public:
	HRESULT				Add_GameObject(GameObject* _GOBJ);
	GameObject*			Get_GameObject(CONST TCHAR* _TAG);

public:
	virtual	HRESULT		Ready_Layer();
	virtual INT			Update_Layer(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Layer(CONST FLOAT& _DT);
	//virtual VOID		Render_Layer();

	list<GameObject*>*	Get_GameObjectList() { return &GameObjectList; }
	HRESULT				Delete_Object(GameObject* _OBJ);

private:
	list<GameObject*>	GameObjectList;

public:
	static	Layer*		Create();
private:
	virtual VOID		Free() ;
};
END