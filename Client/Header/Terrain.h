#pragma once
#include "GameObject.h"
class Terrain : public GameObject {
private:
	explicit Terrain(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Terrain(CONST GameObject& _RHS);
	virtual ~Terrain();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer*		Component_Buffer;
	Transform*	Component_Transform;
	Texture*	Component_Texture;

	IDirect3DBaseTexture9* StaticTexture;

public:
	static	Terrain* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

};

