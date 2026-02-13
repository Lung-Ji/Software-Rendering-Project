#pragma once
#include "GameObject.h"

class ScorpionBullet : public GameObject
{
public:
	explicit ScorpionBullet(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit ScorpionBullet(CONST GameObject& _RHS);
	virtual ~ScorpionBullet();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

	static			ScorpionBullet* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	VOID			Free();
	HRESULT			Component_Initialize();

private:
	Buffer* Component_Buffer;
	Transform* Component_Transform;
	Collider* Component_Collider;

public:

	VOID		Set_Master(GameObject* pOwner) { pOwner = m_pMaster; }
	GameObject* Get_Master() { return m_pMaster; }

	VOID	Set_Dir(_vec3 vDir) { m_vDir = vDir; }
	VOID	Set_Dir(_float x, _float y, _float z) { m_vDir = { x,y,z }; }
	_vec3*	Get_Dir() { return &m_vDir; }

private:

	GameObject* m_pMaster;
	_vec3		m_vDir;
	_float		m_fKillTimer;

	_float		m_fSpeed;

	TEXINFO		m_tTexInfo;
};
