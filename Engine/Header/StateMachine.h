#pragma once
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL State {
public:
	virtual VOID FSM_StateEnter()	= 0;
	virtual VOID FSM_StateUpdate()	= 0;
	virtual VOID FSM_StateExit()	= 0;

	virtual ~State() {};
};


class ENGINE_DLL StateMachine : public Component {
protected:
	explicit StateMachine();
	explicit StateMachine(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit StateMachine(CONST StateMachine& _RHS);
	virtual ~StateMachine();

public:
	virtual HRESULT		Ready_Component();
	virtual INT			Update_Component(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Component(CONST FLOAT& _DT) {};
	virtual VOID		Render_Component() {};

public:
	VOID		FSM_StateChange(State* _State);
	VOID		FSM_StateInit(State* _State) { CurrentState = _State; }
	State*		FSM_GetCurrentState() { return CurrentState; }

public:
	static		StateMachine*	Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component*		Clone();

private:
	State*				CurrentState;
	State*				PreviousState;
private:
	virtual		VOID	Free();
};
END
