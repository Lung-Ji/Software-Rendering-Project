#pragma once
#include "GameObject.h"

class SpeechBubble : public GameObject
{
	explicit SpeechBubble(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit SpeechBubble(CONST GameObject& _RHS);
	virtual ~SpeechBubble();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	static	SpeechBubble* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	HRESULT Sprite_Initialize();
	HRESULT Text_Initialize();
private:
	SpriteObject* Component_Sprite;
private:
	virtual	VOID		Free();

};

