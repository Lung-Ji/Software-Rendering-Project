#pragma once
#include "GameObject.h"
class Augments : public GameObject
{
	private:
		explicit Augments(LPDIRECT3DDEVICE9 _GRPDEV);
		explicit Augments(CONST GameObject& _RHS);
		virtual ~Augments();

	public:
		virtual	HRESULT		Ready_GameObject();
		virtual INT			Update_GameObject(CONST FLOAT& _DT);
		virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
		virtual VOID		Render_GameObject();

	public:
		HRESULT Component_Initialize();
		HRESULT Sprite_Initialize();
		HRESULT Effect_Initialize();

		static	Augments* Create(LPDIRECT3DDEVICE9 _GRPDEV);

	private:
		SpriteObject* Component_Sprite;
		vector<SpriteINFO>* TextureList;
	private:
		virtual	VOID		Free();
};



