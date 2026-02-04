#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL CollisionManager : public Base {
	DECLARE_SINGLETON(CollisionManager)
private:
	explicit CollisionManager();
	virtual ~CollisionManager();

public:
	INT		Update_CollisionManager();
	
public:
	VOID	Get_AllObjectOfScene();

private:
	
private:
	virtual VOID	Free();
};

END