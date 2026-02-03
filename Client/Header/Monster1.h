#pragma once
#include "GameObject.h"

#define TRACKINGDIS 1000
#define TRACKINGTIME 1000
#define RUSHSPEED 1000

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

	GameObject*		pTarget;

public:
	static Monster1* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

	bool Is_Tracking;
	bool Is_Attacking;
	
	uint16_t Lost_Counter;
	uint16_t Tracking_Counter;

	_float Default_Speed;
	_float Speed;

};