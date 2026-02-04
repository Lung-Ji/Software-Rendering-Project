#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Collider : public Component {
private:
	explicit Collider();
	explicit Collider(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Collider(CONST Collider& _RHS);
	virtual ~Collider();

public:
	virtual HRESULT		Ready_Component() { return 0; }
	virtual INT			Update_Component(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Component(CONST FLOAT& _DT);
	virtual VOID		Render_Component();

public:
	BOOL	OnCollisionEnter();
	BOOL	OnCollisionStay();
	BOOL	OnCollisionExit();

public:
	static		Collider* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component* Clone();

private:

private:
	virtual		VOID		Free();
};


END