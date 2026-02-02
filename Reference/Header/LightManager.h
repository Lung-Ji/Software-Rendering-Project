#pragma once
#include "Base.h"
#include "Engine_Define.h"
#include "Light.h"

BEGIN(Engine)
class ENGINE_DLL LightManager : public Base {
	DECLARE_SINGLETON(LightManager)
private:
	explicit LightManager();
	virtual ~LightManager();

public:
	HRESULT Ready_Light(LPDIRECT3DDEVICE9 GRPDEV, CONST D3DLIGHT9* _Light, CONST UINT& _Index);

private:
	list<Light*>		LightList;
private:
	virtual VOID	Free();

};

END