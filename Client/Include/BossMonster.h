#pragma once
#include "GameObject.h"

class BossMonster :   public GameObject
{
private:
	explicit BossMonster(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit BossMonster(CONST GameObject& _RHS);
	virtual ~BossMonster();

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
	static BossMonster* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();
};