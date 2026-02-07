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

	FLOAT				Get_AlphaZValue() { return AlphaZValue; }

	VOID				Set_ObjectTag(CONST TCHAR* _OBJTAG)			{	ObjectTAG = _OBJTAG; }
	wstring				Get_ObjectTag()								{	return ObjectTAG;	 }

	VOID				Set_ObjectType(GAMEOBJECT_TYPE _OBJTYPE)	{ ObjectTYPE = _OBJTYPE; }
	GAMEOBJECT_TYPE		Get_ObjectType()							{	return ObjectTYPE;	 }

	VOID				Set_ObjectDead(BOOL _DEAD) { ObjectDead = _DEAD; }
	BOOL				Get_ObjectDead() { return ObjectDead; }

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject() = 0;

public:
	virtual BOOL		OnCollisionEnter(GameObject* _Other)	{ return TRUE; }
	virtual BOOL		OnCollisionStay	(GameObject* _Other)	{ return TRUE; }
	virtual BOOL		OnCollisionExit	(GameObject* _Other)	{ return TRUE; }

public:
	VOID	AlphaSorting(CONST D3DXVECTOR3* _Vec);

protected:
	vector<Component*>				ComponentList;
	LPDIRECT3DDEVICE9				GRPDEV;

	GAMEOBJECT_TYPE					ObjectTYPE;
	wstring							ObjectTAG;
	BOOL							ObjectDead;

	FLOAT							AlphaZValue;

protected:
	virtual VOID		Free();
};

END