#pragma once
#include "GameObject.h"

#pragma region Macros
#define POS(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define MYPOS Component_Transform->Get_Position()

#pragma endregion

#define TRACKINGDIS 10.f
#define TRACKINGMAX 3.f
#define TRACKINGMIN 2.f
#define ATTACKREADY 1.f
#define ATTACKEND	3.f
#define RUSHSPEED 2.f

enum MONSTER1_STATE { MON1_IDLE, MON1_TRACKING, MON1_ATTACKING, MON1_Hit, MON1_DEAD };

class Monster1 : public GameObject
{
private:
	explicit Monster1(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Monster1(CONST GameObject& _RHS);
	virtual ~Monster1();

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
	Texture*		Component_Texture;
	StateMachine*	Component_FSM;
	Collider*		Component_Collider;

	GameObject*		pTarget;

public:
	static Monster1* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

	VOID Set_Target(CONST TCHAR* _TAG);

	_vec3*		pTargetPos;
	_vec3		vDir;

	MONSTER1_STATE CurrState;
	MONSTER1_STATE PrevState;

	VOID Change_State(MONSTER1_STATE eState);
	VOID State_Idle();
	VOID State_Tracking(const _float& _DT);
	VOID State_Attacking(const _float& _DT);


	_float Timer1;
	_float Timer2;

	_float Default_Speed;
	_float Speed;


	_uint _frame;
	_float _frameTick;

};