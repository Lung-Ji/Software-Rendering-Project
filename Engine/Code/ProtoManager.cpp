#include "ProtoManager.h"

IMPLEMENT_SINGLETON(ProtoManager)

ProtoManager::ProtoManager()	{			}
ProtoManager::~ProtoManager()	{	Free();	}

HRESULT		ProtoManager::Ready_Prototype(LPDIRECT3DDEVICE9 _GRPDEV) {

	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TRIANGLE));		//COMPONENT_TYPE::COMPONENT_TRIANGLE	= 0
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::RECTANGLE));		//COMPONENT_TYPE::COMPONENT_RECTANGLE	= 1
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TEXTURE));		//COMPONENT_TYPE::COMPONENT_RECTTEX		= 2
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TERRAIN));		//COMPONENT_TYPE::COMPONENT_TERRAIN		= 3
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TILE));			//COMPONENT_TYPE::COMPONENT_TILE		= 4
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::CUBE));			//COMPONENT_TYPE::COMPONENT_CUBE		= 5
	ComponentList.push_back(Transform	::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_TRANSFORM	= 6
	ComponentList.push_back(Texture		::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_TEXTURE		= 7
	ComponentList.push_back(SpriteObject::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_SPRITE		= 8
	ComponentList.push_back(StateMachine::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_FSM			= 9
	
	return S_OK;
}
Component*	ProtoManager::Clone_Prototype(COMPONENT_TYPE _TYPE) {
	return ComponentList[(LONG)_TYPE]->Clone();
}
HRESULT ProtoManager::Push_ProtoType(LPDIRECT3DDEVICE9 _GRPDEV, Component* _Push) {
	ComponentList.push_back(_Push);
	return S_OK;
}
VOID		ProtoManager::Free() {
	for_each(ComponentList.begin(), ComponentList.end(), Safe_Release<Component*>);
	ComponentList.clear();
}