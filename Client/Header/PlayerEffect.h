#pragma once
#include "GameObject.h"

class PlayerEffect : public GameObject {
private:
	explicit PlayerEffect(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit PlayerEffect(CONST GameObject& _RHS);
	virtual ~PlayerEffect();

public:
	virtual			HRESULT		Ready_GameObject() { return S_OK; }
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

	virtual BOOL		OnCollisionEnter(GameObject* _Other);
	virtual BOOL		OnCollisionStay (GameObject* _Other);
	virtual BOOL		OnCollisionExit (GameObject* _Other);
public:
	HRESULT						Ready_Effect(PLAYER_SKILL _SKILLTYPE, _vec3* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime, _vec3 _Size);
	HRESULT						Make_TextureList(wstring _FileName);
	static	PlayerEffect*		Create(LPDIRECT3DDEVICE9 _GRPDEV, PLAYER_SKILL _SKILLTYPE, _vec3* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime, _vec3 _Size = {1.f, 1.f, 1.f});
private:
	HRESULT				Component_Initialize();
	virtual	VOID		Free();
private:
	PLAYER_SKILL	SKILL_TYPE;
	INT				ENDFRAME;
	vector<IDirect3DBaseTexture9*>	TextureList;

	INT				TextureIndex;
	FLOAT			FrameTick;
	FLOAT			PlayTime;
	BOOL			Repeatable;
	
	Buffer*			Component_Buffer;
	Transform*		Component_Transform;
	Texture*		Component_Texture;
	Collider*		Component_Collider;

	_vec3* _playerPos;
	_vec3 _effectSize;
};

