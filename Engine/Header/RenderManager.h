#pragma once

#include "Base.h"
#include "GameObject.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL RenderManager : public Base {
	DECLARE_SINGLETON(RenderManager)
private:
	explicit RenderManager();
	virtual ~RenderManager();

public:
	VOID		Add_RenderGroup(RENDERID _RID, GameObject* _GOBJ);
	VOID		Render_GameObject(LPDIRECT3DDEVICE9& _GRPDEV);
	VOID		Clear_RenderGroup();

	GameObject* Get_Camera() { return RenderGroup[RENDERID::RENDER_UI].front(); }

public:
	VOID		Render_Priority(LPDIRECT3DDEVICE9& _GRPDEV);
	VOID		Render_NonAlpha(LPDIRECT3DDEVICE9& _GRPDEV);
	VOID		Render_Alpha(LPDIRECT3DDEVICE9& _GRPDEV);
	VOID		Render_UI(LPDIRECT3DDEVICE9& _GRPDEV);
	VOID		Render_TILE(LPDIRECT3DDEVICE9& _GRPDEV);
private:
	list<GameObject*>			RenderGroup[RENDERID::RENDER_END];

private:
	virtual VOID	Free();

public:
	static VOID Make_BillBoard(Transform* Component_Transform, LPDIRECT3DDEVICE9 _GRPDEV);
};

END