#include "GameObject.h"

GameObject::GameObject(LPDIRECT3DDEVICE9 _GRPDEV)
	: GRPDEV(_GRPDEV)	 , ObjectTAG(L""), ObjectDead(FALSE), ObjectTYPE(), AlphaZValue(0.f)
										{ GRPDEV->AddRef(); ComponentList.resize((LONG)COMPONENT_TYPE::COMPONENT_END);	}
GameObject::GameObject(const GameObject& _RHS)	 
	: GRPDEV(_RHS.GRPDEV), ObjectTAG(_RHS.ObjectTAG), ObjectTYPE(_RHS.ObjectTYPE), ComponentList(_RHS.ComponentList), AlphaZValue(_RHS.AlphaZValue)
	, ObjectDead(_RHS.ObjectDead) { GRPDEV->AddRef(); ComponentList.resize((LONG)COMPONENT_TYPE::COMPONENT_END);	}
GameObject::GameObject(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _TAG)
	: GRPDEV(_GRPDEV)	 , ObjectTAG(_TAG), ObjectDead(FALSE) { GRPDEV->AddRef(); ComponentList.resize((LONG)COMPONENT_TYPE::COMPONENT_END);	}
GameObject::~GameObject()				{																				}

HRESULT		GameObject::Ready_GameObject() {
	return S_OK;
}
INT			GameObject::Update_GameObject(const FLOAT& _DT) {
	for (auto& COM : ComponentList) {
		if (COM == nullptr)	 continue;
		COM->Update_Component(_DT);
	}
	return 0;
}
VOID		GameObject::LateUpdate_GameObject(const FLOAT& _DT) {
	for (auto& COM : ComponentList) {
		if (COM == nullptr)	 continue;
		COM->LateUpdate_Component(_DT);
	}
}
VOID GameObject::AlphaSorting(const D3DXVECTOR3* _Vec) {
	D3DXMATRIX WorldMat;
	GRPDEV->GetTransform(D3DTS_VIEW, &WorldMat);
	D3DXMatrixInverse(&WorldMat, 0, &WorldMat);

	D3DXVECTOR3 CameraPosition;
	memcpy(&CameraPosition, &WorldMat.m[3][0], sizeof(D3DXVECTOR3));
	
	D3DXVECTOR3 DirectionToCam = CameraPosition - *_Vec;
	AlphaZValue = D3DXVec3Length(&DirectionToCam);
}
Component*	GameObject::Get_Component(COMPONENT_TYPE _CID) {
	return ComponentList[(LONG)_CID] != nullptr ? ComponentList[(LONG)_CID] : nullptr;
}
Component*	GameObject::Add_Component(COMPONENT_TYPE _CID) {
	if (ComponentList[(LONG)_CID] == nullptr)
		ComponentList[(LONG)_CID] = ProtoManager::GetInstance()->Clone_Prototype(_CID);
	
	return ComponentList[(LONG)_CID];
}
VOID		GameObject::Free() {
	for (auto& COM : ComponentList)
		Safe_Release(COM);
	Safe_Release(GRPDEV);
}
