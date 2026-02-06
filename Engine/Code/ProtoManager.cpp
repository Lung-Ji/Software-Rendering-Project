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
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TILEFRONT));		//COMPONENT_TYPE::COMPONENT_TILEFRONT	= 6
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TILELEFT));		//COMPONENT_TYPE::COMPONENT_TILEFRONT	= 7
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TILERIGHT));		//COMPONENT_TYPE::COMPONENT_TILEFRONT	= 8
	ComponentList.push_back(Buffer		::Create(_GRPDEV, BUFFER_TYPE::TILEBACK));		//COMPONENT_TYPE::COMPONENT_TILEFRONT	= 9
	ComponentList.push_back(Transform	::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_TRANSFORM	= 10
	ComponentList.push_back(Texture		::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_TEXTURE		= 11
	ComponentList.push_back(SpriteObject::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_SPRITE		= 12
	ComponentList.push_back(Collider	::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_COLLIDER	= 13
	ComponentList.push_back(StateMachine::Create(_GRPDEV));								//COMPONENT_TYPE::COMPONENT_FSM			= 14
	ComponentList.push_back(TileInfo::Create(_GRPDEV));								    //COMPONENT_TYPE::COMPONENT_TILEINFO	= 15
	return S_OK;
}
Component*	ProtoManager::Clone_Prototype(COMPONENT_TYPE _TYPE) {
	return ComponentList[(LONG)_TYPE]->Clone();
}
VOID		ProtoManager::Free() {
	for_each(ComponentList.begin(), ComponentList.end(), Safe_Release<Component*>);
	ComponentList.clear();
}