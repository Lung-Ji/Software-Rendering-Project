#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Transform : public Component {
private:
	explicit Transform();
	explicit Transform(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Transform(CONST Transform& _RHS);
	virtual ~Transform();

public:
	virtual HRESULT		Ready_Component();
	virtual INT			Update_Component(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Component(CONST FLOAT& _DT);

public:
	VOID		Move_Pos(CONST _vec3* _Direction, CONST _float& _Speed, CONST _float& _DT){
		m_vInfo[INFO_POS] += *_Direction * _Speed * _DT;
	}
	
	VOID		Rotation(ROTATION eType, const _float& fAngle) {
		*(((_float*)&m_vAngle) + eType) += fAngle;
	}
	VOID				Get_Info(INFO eType, _vec3* pInfo)
	{
		memcpy(pInfo, &WorldMatrix.m[eType][0], sizeof(_vec3));
	}
public:
	VOID		Set_Pos(_vec3 _Pos)										{ m_vInfo[INFO_POS] = _Pos;						}
	VOID		Set_Pos(FLOAT _PosX, FLOAT _PosY, FLOAT _PosZ)			{ m_vInfo[INFO_POS] = { _PosX, _PosY, _PosZ };	}

	VOID		Set_Rotation(_vec3 _Rot)								{ m_vAngle = _Rot;						}
	VOID		Set_Rotation(FLOAT _RotX, FLOAT _RotY, FLOAT _RotZ)		{ m_vAngle = { _RotX, _RotY, _RotZ };	}

	VOID		Set_Scale(_vec3 _Sca)									{ m_vScale = _Sca;						}
	VOID		Set_Scale(FLOAT _ScaX, FLOAT _ScaY, FLOAT _ScaZ)		{ m_vScale = { _ScaX, _ScaY, _ScaZ };	}

public:
	_matrix*	Get_World()			{ return &WorldMatrix;			}

	_vec3*		Get_Position()		{ return &m_vInfo[INFO_POS];	}
	_vec3*		Get_Rotation()		{ return &m_vAngle;				}
	_vec3*		Get_Scale()			{ return &m_vScale;				}

private:
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vScale;
	_vec3		m_vAngle;

	_matrix		WorldMatrix;

public:
	static		Transform* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component* Clone();

private:
	virtual		VOID	Free();
};

END