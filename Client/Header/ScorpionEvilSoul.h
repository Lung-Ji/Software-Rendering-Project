#pragma once
#include "GameObject.h"

#define SCROPOINEVILSOULIMGX 143
#define SCROPOINEVILSOULIMGY 224

enum SCROPOINEVILSOUL_STATE {
	SCROPOINEVILSOUL_APPEAR,
	SCROPOINEVILSOUL_IDLE,
	SCROPOINEVILSOUL_TRACKING,
	SCROPOINEVILSOUL_CHARGING,
	SCROPOINEVILSOUL_ATTACKING,
	SCROPOINEVILSOUL_HIT,
	SCROPOINEVILSOUL_DISAPPEAR
};

class ScorpoinEvilSoul : public GameObject
{
private:
	explicit ScorpoinEvilSoul(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit ScorpoinEvilSoul(CONST GameObject& _RHS);
	virtual ~ScorpoinEvilSoul();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer*			Component_Buffer;
	Transform*		Component_Transform;
	Collider*		Component_Collider;

public:
	static ScorpoinEvilSoul* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

	VOID Set_Target(CONST TCHAR* _TAG);

	GameObject* m_pTarget;
	_vec3		m_vDir;

	SCROPOINEVILSOUL_STATE CurrState;
	SCROPOINEVILSOUL_STATE PrevState;

	VOID Change_State(SCROPOINEVILSOUL_STATE eState);
	VOID State_Appear();
	VOID State_Idle(const _float& _DT);
	VOID State_Tracking(const _float& _DT);
	VOID State_Charging(const _float& _DT);
	//VOID State_Attacking(const _float& _DT);

	_float m_fTimer1;
	_float m_fTimer2;

	_float m_fDefault_Speed;
	_float m_fSpeed;

	TEXINFO m_tTexInfo;
};