#pragma once
#include "Base.h"
#include "Engine_Define.h"
#include "GameObject.h"

BEGIN(Engine)
class ENGINE_DLL CollisionManager : public Base {
	DECLARE_SINGLETON(CollisionManager)
private:
	explicit CollisionManager();
	virtual ~CollisionManager();

public:
	INT		Update_CollisionManager();
	VOID	LateUpdate_CollisionManager();
	VOID	Render_CollisionManager();
	
public:
	BOOL	AABB_Collision();
	VOID	Get_AllObjectOfScene();
	VOID	Add_ColliderObject(GameObject* _Effect) { SceneObjectList.push_back(_Effect); }

private:
	list<GameObject*>		SceneObjectList;

	BOOL					CollisionLine_Visibility;

private:
	virtual VOID	Free();
};

END