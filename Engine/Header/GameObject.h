#pragma once
#include "Base.h"
#include "Component.h"
#include "ProtoManager.h"

BEGIN(Engine)
class ENGINE_DLL GameObject : public Base {
protected:
	explicit GameObject(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit GameObject(CONST GameObject& _RHS);
	explicit GameObject(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _TAG);
	virtual ~GameObject();

public:
	Component*			Get_Component(COMPONENT_TYPE _CID);
	Component*			Add_Component(COMPONENT_TYPE _CID);

	VOID				Set_ObjectTag(CONST TCHAR* _OBJTAG)	{ TAG = _OBJTAG; }
	wstring				Get_ObjectTag()						{	return TAG;	 }
	// Ãß°¡
public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

protected:
	vector<Component*>				ComponentList;
	LPDIRECT3DDEVICE9				GRPDEV;
	wstring							TAG;

protected:
	virtual VOID		Free();
};

END