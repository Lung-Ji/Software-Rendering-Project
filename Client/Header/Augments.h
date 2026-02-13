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
		HRESULT	Text_Initialize();

		VOID Make_ShadowOutLine();

		static	Augments* Create(LPDIRECT3DDEVICE9 _GRPDEV);

	private:
		SpriteObject* Component_Sprite;
		vector<SpriteINFO>* TextureList;


		// 임시 폰트용 멤버 변수
		ID3DXFont* m_pFont;
		RECT			 rc = { 550,80, 0, 0 };
		D3DXCOLOR  color = { 255.f,255.f,255.f,255.f };

	private:
		virtual	VOID		Free();
};



