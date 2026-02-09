#pragma once
#include "GameObject.h"

enum class ArrowType {
	IceArrow,

	End
};

class Arrow : public GameObject
{
private:
	explicit Arrow(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Arrow(const GameObject& _RHS);
	virtual ~Arrow();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();
	void			SetGrahpic();
private:
	Buffer* Component_Buffer;
	Transform* Component_Transform;
	Texture* Component_Texture;

	IDirect3DTexture9* g_pTexture = NULL; // 로드된 이미지
	ID3DXSprite* g_pSprite = NULL;   // 스프라이트 객체

public:
	static Arrow* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();
};

