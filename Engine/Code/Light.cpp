#include "Light.h"

Light::Light(LPDIRECT3DDEVICE9 _GRPDEV) : GRPDEV(_GRPDEV), m_iIndex(0){
	ZeroMemory(&m_tLight, sizeof(m_tLight));
	GRPDEV->AddRef();
}
Light::~Light() {}

HRESULT Light::Ready_Light(const D3DLIGHT9* pLightInfo, const _uint& iIndex) {
	memcpy(&m_tLight, pLightInfo, sizeof(D3DLIGHT9));
	m_iIndex = iIndex;

	GRPDEV->SetLight(iIndex, &m_tLight);
	GRPDEV->LightEnable(iIndex, TRUE);

	return S_OK;
}
Light* Light::Create(LPDIRECT3DDEVICE9 _GRPDEV, const D3DLIGHT9* pLightInfo, const _uint& iIndex) {
	Light* LGT = new Light(_GRPDEV);
	if (FAILED(LGT->Ready_Light(pLightInfo, iIndex))) {
		MSG_BOX("Cannot Create Light.");
		Safe_Release(LGT);
		return nullptr;
	}
	return LGT;
}
void	Light::Free() {
	GRPDEV->LightEnable(m_iIndex, FALSE);
	Safe_Release(GRPDEV);
}