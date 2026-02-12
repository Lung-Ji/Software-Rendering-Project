#pragma once
#include "GameObject.h"
#include "FontManager.h"

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

	BOOL	Activate_NPCTalk(NPC_CHARACTER _NPCC, FLOAT _DT);
	BOOL	Shadow_FadeIn(FLOAT _Timer);
	BOOL	Shadow_FadeOut(FLOAT _Timer);

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Effect_Initialize();
	HRESULT Text_Initialize();

	static	NPCTalk* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;

	FLOAT		Timer01;
	_int		ContextPassing;

	BOOL		ShadowCast;

	SpriteINFO* BackGround;
	SpriteINFO* GRD_Top;
	SpriteINFO* GRD_Bottom;

	SpriteINFO* Sprite_Yeon;
	SpriteINFO* Sprite_Tif;

	SpriteINFO* NameBar;
	SpriteINFO* Square;

	FontObject* Name;
	FontObject* Talk;

	Player*		PlayerObject;

private:
	virtual	VOID		Free();
};

