#pragma once
#include "Component.h"
#include "Transform.h"
#include "Buffer.h"

BEGIN(Engine)

class ENGINE_DLL Collider : public Component {
private:
	explicit Collider();
	explicit Collider(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Collider(CONST Collider& _RHS);
	virtual ~Collider();

public:
	virtual HRESULT		Ready_Component();
	virtual INT			Update_Component(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Component(CONST FLOAT& _DT);
	virtual VOID		Render_Component();
	
public:
	BOOL		OnCollisionEnter();
	BOOL		OnCollisionStay();
	BOOL		OnCollisionExit();

	VOID		Set_CenterPos(Transform* _ColliderPos) { ColliderPos = _ColliderPos; }

	VOID		Set_Scale(FLOAT _XRANGE, FLOAT _YRANGE, FLOAT _ZRANGE) { Scale = { _XRANGE,  _YRANGE,  _ZRANGE }; }

	VOID		Set_MinPoint(FLOAT _X, FLOAT _Y, FLOAT _Z) { MinPoint = { _X , _Y , _Z }; }
	VOID		Set_MaxPoint(FLOAT _X, FLOAT _Y, FLOAT _Z) { MaxPoint = { _X , _Y , _Z }; }

	_vec3		Get_MinPoint() { return MinPoint; }
	_vec3		Get_MaxPoint() { return MaxPoint; }

	VOID		Set_CollisionState(BOOL _State) { Curr_ColState = _State; }
	BOOL		Get_CollisionState()			{ return Curr_ColState;   }

public:
	static		Collider*	Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component*	Clone();

private:
	Transform*		ColliderPos;
	Buffer*			ColliderArea;
	_vec3			CenterPos;
	_vec3			Scale;
	_vec3			MinPoint;
	_vec3			MaxPoint;

	BOOL		Curr_ColState;
	BOOL		Prev_ColState;

	D3DXMATRIX matWorld, matView, matProj, Sum;

	ID3DXLine* pLine;
	
private:
	virtual		VOID		Free();
};


END