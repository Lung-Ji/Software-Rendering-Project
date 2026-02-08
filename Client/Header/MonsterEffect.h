#pragma once
#include "GameObject.h"

class MonsterEffect : public GameObject {
private:
	explicit MonsterEffect(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MonsterEffect(CONST GameObject& _RHS);
	virtual ~MonsterEffect();

public:
	virtual			HRESULT		Ready_GameObject() { return S_OK; }
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

	virtual BOOL		OnCollisionEnter(GameObject* _Other);
	virtual BOOL		OnCollisionStay(GameObject* _Other);
	virtual BOOL		OnCollisionExit(GameObject* _Other);

public:
	HRESULT						Ready_Effect(MONSTER_SKILL _SKILLTYPE, _vec3* _MonsterPOS, BOOL _Repeatable, FLOAT _PlayTime);
	HRESULT						Make_TextureList(wstring _FileName);
	static	MonsterEffect*		Create(LPDIRECT3DDEVICE9 _GRPDEV, MONSTER_SKILL _SKILLTYPE, _vec3* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime);
private:
	HRESULT				Component_Initialize();
	virtual	VOID		Free();
private:
	MONSTER_SKILL	SKILL_TYPE;
	INT				ENDFRAME;
	vector<IDirect3DBaseTexture9*>	TextureList;

	INT				TextureIndex;
	FLOAT			FrameTick;
	FLOAT			PlayTime;
	BOOL			Repeatable;

	Buffer*		Component_Buffer;
	Transform*	Component_Transform;
	Texture*	Component_Texture;
	Collider*	Component_Collider;
};

