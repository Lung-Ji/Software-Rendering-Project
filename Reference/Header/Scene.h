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

	GameObject* Get_GameObject(CONST TCHAR* _TAG);

	template <typename T>
	HRESULT		Add_GameObjectToScene(LAYER_TYPE _LTYPE, GAMEOBJECT_TYPE _GTYPE, CONST TCHAR* _TAG = L"") {
		GameObject* GOBJ = T::Create(GRPDEV);
		GOBJ->Set_ObjectTag(_TAG);
		GOBJ->Set_ObjectType(_GTYPE);

		if (nullptr == GOBJ)										return E_FAIL;
		if (FAILED(LayerList[(LONG)_LTYPE]->Add_GameObject(GOBJ)))	return E_FAIL;
		return S_OK;
	}

protected:
	vector<Layer*>				LayerList;
	LPDIRECT3DDEVICE9			GRPDEV;

protected:
	virtual		VOID	Free();
};

END