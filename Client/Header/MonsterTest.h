#pragma once
#include "GameObject.h"

#pragma region Macros
#define POS(GAMEOBJECT)			static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define ROTATION(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation()
#define MYPOS					Component_Transform->Get_Position()

#pragma endregion

#define TESTMONIMGX 287.f
#define TESTMONIMGY 173.f

#define TRACKINGDIS 10.f
#define TRACKINGMAX 3.f
#define TRACKINGMIN 2.f
#define ATTACKREADY 1.f
#define ATTACKEND	2.f
#define RUSHSPEED	2.f

enum MONSTERTEST_STATE { MONTEST_IDLE, MONTEST_TRACKING, MONTEST_ATTACKING, MONTEST_Hit, MONTEST_DEAD };

class MonsterTest : public GameObject
{
private:
	explicit MonsterTest(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MonsterTest(CONST GameObject& _RHS);
	virtual ~MonsterTest();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer* Component_Buffer;
	Transform* Component_Transform;
	Collider* Component_Collider;

public:
	static MonsterTest* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

	VOID Set_Target(CONST TCHAR* _TAG);

	GameObject* pTarget;
	_vec3* pTargetPos;
	_vec3		vDir;

	MONSTERTEST_STATE CurrState;
	MONSTERTEST_STATE PrevState;

	VOID Change_State(MONSTERTEST_STATE eState);
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