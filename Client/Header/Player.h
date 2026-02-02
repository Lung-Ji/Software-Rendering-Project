#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:
	explicit Player(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Player(const GameObject& _RHS);
	virtual ~Player();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();
	void			Key_Input(const _float& _DT);

private:
	Buffer*			Component_Buffer;
	Transform*		Component_Transform;
	Texture*		Component_Texture;
	StateMachine*	Component_FSM;

public:
	static Player* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

private:
	float _defaultSpeed;
	float _speed;

	float _defultJumpSpeed;
	float _jumpSpeed;
};