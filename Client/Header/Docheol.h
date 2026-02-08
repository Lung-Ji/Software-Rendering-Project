#pragma once
#include "GameObject.h"

enum DOCHEOL_STATUS { DOCHEOL_IDLE };

class Docheol : public GameObject
{
private:
	explicit Docheol(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Docheol(CONST GameObject& _RHS);
	virtual ~Docheol();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

	static			Docheol*	Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	VOID			Free();
	HRESULT			Component_Initialize();

private:
	Buffer*		Component_Buffer;
	Transform*	Component_Transform;
	Collider*	Component_Collider;

private:
	GameObject*		m_pTarget;


	_float			m_fTimer1, m_fTimer2;
	_float			_frameTick;
	UINT			_frame;


	DOCHEOL_STATUS	m_eCurrStatus, m_ePrevStatus;

	VOID Change_Status(DOCHEOL_STATUS eState);
};

