#include "LightManager.h"

LightManager::LightManager()	{	}
LightManager::~LightManager()	{	}

HRESULT LightManager::Ready_Light(LPDIRECT3DDEVICE9 GRPDEV, const D3DLIGHT9* _Light, const UINT& _Index)	{
	Light* pLight = Light::Create(GRPDEV, _Light, _Index);
	if (nullptr == pLight)	return E_FAIL;

	LightList.push_back(pLight);
	return S_OK;
}
VOID	LightManager::Free() {
	for_each(LightList.begin(), LightList.end(), CDeleteObj());
	LightList.clear();
}