#pragma once

class MONSTER_IDLE : public State {
	DECLARE_FSM_SINGLETON(MONSTER_IDLE);
public:
	virtual VOID FSM_StateEnter();
	virtual VOID FSM_StateUpdate();
	virtual VOID FSM_StateExit();
};

class MONSTER_ATTACK : public State {
	DECLARE_FSM_SINGLETON(MONSTER_ATTACK);
public:
	virtual VOID FSM_StateEnter();
	virtual VOID FSM_StateUpdate();
	virtual VOID FSM_StateExit();
};

class MONSTER_CHASE : public State {
	DECLARE_FSM_SINGLETON(MONSTER_CHASE);
public:
	virtual VOID FSM_StateEnter();
	virtual VOID FSM_StateUpdate();
	virtual VOID FSM_StateExit();
};

class MONSTER_DAMAGED : public State {
	DECLARE_FSM_SINGLETON(MONSTER_DAMAGED);
public:
	virtual VOID FSM_StateEnter();
	virtual VOID FSM_StateUpdate();
	virtual VOID FSM_StateExit();
};

class MONSTER_DEAD : public State {
	DECLARE_FSM_SINGLETON(MONSTER_DEAD);
public:
	virtual VOID FSM_StateEnter();
	virtual VOID FSM_StateUpdate();
	virtual VOID FSM_StateExit();
};