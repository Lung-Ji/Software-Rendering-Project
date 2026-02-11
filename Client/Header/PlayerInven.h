#pragma once
#include "GameObject.h"
#include "PlayerEquipMent.h"

class PlayerInven :  public GameObject
{
	explicit PlayerInven(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit PlayerInven(CONST GameObject& _RHS);
	virtual ~PlayerInven();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	static	PlayerInven* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	HRESULT Sprite_Initialize();

private:
	SpriteObject* Component_Sprite;
private:
	virtual	VOID		Free();
};