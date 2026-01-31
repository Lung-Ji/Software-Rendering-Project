#pragma once
#include "Base.h"
#include "Layer.h"

BEGIN(Engine)
class ENGINE_DLL Scene : public Base {
protected:
	explicit Scene();
	explicit Scene(LPDIRECT3DDEVICE9 _GRPD);
	virtual ~Scene();

public:
	virtual	HRESULT		Ready_Scene();
	virtual INT			Update_Scene(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Scene(CONST FLOAT& _DT);
	virtual VOID		Render_Scene() = 0;

public:
	Layer*		Get_Layer(LAYER_TYPE _LID);
	GameObject* Get_GameObject(LAYER_TYPE _LID, GAMEOBJECT_TYPE _OTYPE);
	Component*	Get_Component(LAYER_TYPE _LID, GAMEOBJECT_TYPE _OTYPE, COMPONENT_TYPE _CID);

	GameObject* Get_GameObject(CONST TCHAR* _TAG);
protected:
	vector<Layer*>				LayerList;
	LPDIRECT3DDEVICE9			GRPDEV;

protected:
	virtual		VOID	Free();
};

END