#include "StateMachine.h"

StateMachine::StateMachine() 
	:						CurrentState(nullptr), PreviousState(nullptr) {}

StateMachine::StateMachine(LPDIRECT3DDEVICE9 _GRPDEV) 
	: Component(_GRPDEV),	CurrentState(nullptr), PreviousState(nullptr) {}

StateMachine::StateMachine(const StateMachine& _RHS) 
	: Component(_RHS),		CurrentState(_RHS.CurrentState), PreviousState(_RHS.PreviousState) {}

StateMachine::~StateMachine() {}

HRESULT	  StateMachine::Ready_Component() {

	return S_OK;
}
INT			StateMachine::Update_Component(CONST FLOAT& _DT) {
	//CurrentState->FSM_StateUpdate();
	return 0;
}
StateMachine* StateMachine::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	StateMachine* FSM = new StateMachine(_GRPDEV);
	if (FAILED(FSM->Ready_Component())) {
		MSG_BOX("Cannot Create StateMachine.");
		Safe_Release(FSM);
		return nullptr;
	}
	return FSM;
}
Component* StateMachine::Clone() {
	return new StateMachine(*this);
}
VOID	StateMachine::Free() {
	Component::Free();
}
VOID StateMachine::FSM_StateChange(State* _State) {
	if (CurrentState != nullptr) {
		CurrentState->FSM_StateExit();
		PreviousState = CurrentState;
	}
	
	CurrentState = _State;

	CurrentState->FSM_StateEnter();
}