#include "GameObject.h"

GameObject::GameObject(LPDIRECT3DDEVICE9 _GRPDEV)
	: GRPDEV(_GRPDEV)	 ,TAG(L"")		{ GRPDEV->AddRef(); ComponentList.resize((LONG)COMPONENT_TYPE::COMPONENT_END);	}
GameObject::GameObject(const GameObject& _RHS)	 
	: GRPDEV(_RHS.GRPDEV),TAG(_RHS.TAG), ComponentList(_RHS.ComponentList)	
										{ GRPDEV->AddRef(); ComponentList.resize((LONG)COMPONENT_TYPE::COMPONENT_END);	}
GameObject::GameObject(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _TAG)
	: GRPDEV(_GRPDEV)	 ,TAG(_TAG)		{ GRPDEV->AddRef(); ComponentList.resize((LONG)COMPONENT_TYPE::COMPONENT_END);	}
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
//VOID		GameObject::Render_GameObject() {
//	for (auto& COM : ComponentList) {
//		if (COM == nullptr)	  continue;
//		COM->Render_Component();
//	}
//}
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
