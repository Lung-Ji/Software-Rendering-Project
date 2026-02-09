#pragma once
#include "GameObject.h"

#define MONSTERSUMMON01EFFECTMAX 20
#define MONSTERSUMMON02EFFECTMAX 21
#define MONSTERSUMMON03EFFECTMAX 22

class MonsterSummon03 : public GameObject
{
private:
	explicit MonsterSummon03(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MonsterSummon03(CONST GameObject& _RHS);
	virtual ~MonsterSummon03();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer* Component_Buffer;
	Transform* Component_Transform;

public:
	static MonsterSummon03* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

	GameObject*			m_pMaster;
	TEXTUREINFO			_Textures;

	_float	_frameTick;
	UINT	_frame;

	_float Speed;
};