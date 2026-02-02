#pragma once
#include "GameObject.h"

class Monster : public GameObject {
private:
	explicit Monster(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Monster(CONST GameObject& _RHS);
	virtual ~Monster();

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

	GameObject*		Player;

public:
	static Monster* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();
};