#pragma once
#include "Base.h"
#include "Component.h"
#include "ProtoManager.h"

BEGIN(Engine)
class ENGINE_DLL TileObject : public Base {
protected:
	explicit TileObject(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit TileObject(CONST TileObject& _RHS);
	explicit TileObject(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _TAG);
	virtual ~TileObject();

public:
	Component* Get_Component(COMPONENT_TYPE _CID);
	Component* Add_Component(COMPONENT_TYPE _CID);

	VOID				Set_ObjectTag(CONST TCHAR* _OBJTAG) { TAG = _OBJTAG; }
	wstring				Get_ObjectTag() { return TAG; }
	// Ãß°¡
public:
	virtual	HRESULT		Ready_TileObject();
	virtual INT			Update_TileObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_TileObject(CONST FLOAT& _DT);
	virtual VOID		Render_TileObject() = 0;

protected:
	vector<Component*>				ComponentList;
	LPDIRECT3DDEVICE9				GRPDEV;
	wstring							TAG;

protected:
	virtual VOID		Free();
};

END