#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL UIManager : public Base {
	DECLARE_SINGLETON(UIManager)
private:
	explicit UIManager();
	virtual ~UIManager();

public:
	VOID	Ready_UIManager(LPDIRECT3DDEVICE9 _GRPDEV);
	VOID	Update_UIManager();
	VOID	Render_UIManager();
private:
	LPDIRECT3DDEVICE9 GRPDEV;
private:
	virtual VOID	Free();
};

END