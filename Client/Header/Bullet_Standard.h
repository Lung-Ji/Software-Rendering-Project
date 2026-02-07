#pragma once
#include "GameObject.h"

class Bullet_Standard : public GameObject {
private:
	explicit Bullet_Standard(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Bullet_Standard(const GameObject& _RHS);
	virtual ~Bullet_Standard();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer*		Component_Buffer;
	Transform*	Component_Transform;
	Texture*	Component_Texture;
	Collider*	Component_Collider;

public:
	static Bullet_Standard* Create(LPDIRECT3DDEVICE9 _GRPDEV);

	VOID		Set_Master(GameObject* pOwner)		{ pOwner = m_pMaster; }
	GameObject* Get_Master()						{ return m_pMaster; }

	VOID	Set_Dir(_vec3 vDir)						{ m_vDir = vDir; }
	VOID	Set_Dir(_float x, _float y, _float z)	{ m_vDir = { x,y,z }; }
	_vec3*	Get_Dir()								{ return &m_vDir; }

private:
	virtual VOID Free();

	GameObject* m_pMaster;
	_vec3		m_vDir;

	_float		m_fSpeed;
	_uint		_frame;
	_float		_frameTick;
};