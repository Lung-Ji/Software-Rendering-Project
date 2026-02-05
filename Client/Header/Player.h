#pragma once
#include "GameObject.h"

enum class pState
{
	STATE_STANDING,
	STATE_RUN_UP,
	STATE_RUN_DOWN,
	STATE_RUN_LEFT,
	STATE_RUN_RIGHT,
	STATE_RUN_LU,
	STATE_RUN_RU,
	STATE_RUN_LD,
	STATE_RUN_RD,
	STATE_DASH,
	STATE_HANDUP,
	STATE_LANDING_DOWN,
	STATE_LANDING_UP,

	STATE_SHOTING,
	STATE_TARGETING,
	STATE_CHARGE_ATTACK,

	STATE_VICTORY,
	STATE_DEAD,

	End
};

enum class pSee
{
	SEE_UP,
	SEE_DOWN,
	SEE_RIGHT,
	SEE_LEFT,
	SEE_LU,
	SEE_RU,
	SEE_LD,
	SEE_RD,

	End
};

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
private:
	Buffer*			Component_Buffer;
	Transform*		Component_Transform;
	Texture*		Component_Texture;
	StateMachine*	Component_FSM;
	Collider*		Component_Collider;
public:
	static Player* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

private:
	void			Key_Input(const _float& _DT);
	void			Gravity(const _float& _DT);
	void			SetGrahpic();
private:
	bool			Debug;

	pState			_state;
	pSee			_see;

	_uint			_frame;
	float			_frameTick;

	float			_defaultSpeed;
	float			_speed;

	bool			_isJump;
	float			_defultJumpSpeed;
	float			_jumpSpeed;
	float			_g;
};
