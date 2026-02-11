#pragma once
#include "GameObject.h"

class NPCTalk : public GameObject {
private:
	explicit NPCTalk(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit NPCTalk(CONST GameObject& _RHS);
	virtual ~NPCTalk();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

	VOID	Activate_NPCTalk(NPC_CHARACTER _NPCC, FLOAT _DT);
	VOID	Make_ShadowOutline(FLOAT _DT);

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Effect_Initialize();
	HRESULT Text_Initialize();

	static	NPCTalk* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;

	FLOAT Timer01;
	_int	ContextPassing;
private:
	virtual	VOID		Free();
};

