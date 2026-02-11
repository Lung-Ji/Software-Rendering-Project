#pragma once
#include "GameObject.h"

class NPC : public GameObject {
private:
	explicit NPC(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit NPC(const GameObject& _RHS);
	virtual ~NPC();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

	virtual			BOOL		OnCollisionEnter(GameObject* _Other);
	virtual			BOOL		OnCollisionStay(GameObject* _Other) ;
	virtual			BOOL		OnCollisionExit(GameObject* _Other) ;

	VOID			TalkWithNPC(FLOAT _DT);

private:
	HRESULT			Component_Initialize();

private:
	Buffer*		Component_Buffer;
	Transform*	Component_Transform;
	Texture*	Component_Texture;
	Collider*	Component_Collider;

	GameObject* Player;
	MainUI*		PlayerUI;
	NPCTalk*	NPCTalkUI;

	vector<IDirect3DTexture9*>	Tif_TextureList;

	_float  Timer_Tif;
	_int	Tif_AnimIDX;


	BOOL	Interaction_Possible;

public:
	static NPC* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();
};