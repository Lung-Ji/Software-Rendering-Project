#include "Layer.h"
#include "CollisionManager.h"

Layer::Layer() {}
Layer::~Layer() {}

HRESULT		Layer::Ready_Layer() {
	return S_OK;
}
INT			Layer::Update_Layer(const FLOAT& _DT) {
	for (auto iter = GameObjectList.begin(); iter != GameObjectList.end();) {
		int ObjectResult = (*iter)->Update_GameObject(_DT);
		if ((*iter)->Get_ObjectDead() == TRUE || ObjectResult == -1) {
			CollisionManager::GetInstance()->Delete_ColliderObject((*iter));
			Safe_Release((*iter));
			iter = GameObjectList.erase(iter);
			continue;
		}
		else { ++iter; }
	}
	return 0;
}
VOID		Layer::LateUpdate_Layer(const FLOAT& _DT) {
	for (auto& GOBJ : GameObjectList) {
		if (!GOBJ->Get_ObjectDead())
			GOBJ->LateUpdate_GameObject(_DT);
	}
}
HRESULT Layer::Delete_Object(GameObject* _OBJ) {
	for (auto iter = GameObjectList.begin(); iter != GameObjectList.end();) {
		if (*iter == _OBJ) {
			Safe_Release(*iter);
			iter = GameObjectList.erase(iter);
			return S_OK;
		}
		else { ++iter; }
	}
	return E_FAIL;
}
GameObject* Layer::Get_GameObject(CONST TCHAR* _TAG) {
	for (auto& OBJ : GameObjectList) {
		if (OBJ->Get_ObjectTag() == _TAG) 
			return OBJ;
	}
	return nullptr;
}
HRESULT		Layer::Add_GameObject(GameObject* _GOBJ) {
	if (_GOBJ == nullptr) return E_FAIL;
	GameObjectList.push_back(_GOBJ);
	//CollisionManager::GetInstance()->Add_ColliderObject(_GOBJ);
	return S_OK;
}
Layer*		Layer::Create() {
	Layer* Instance = new Layer;
	if (FAILED(Instance->Ready_Layer())) {
		MSG_BOX("Cannot Create Layer.");
		Safe_Release(Instance);
		return nullptr;
	}
	return Instance;
}
void		Layer::Free() {
	for (auto& GOBJ : GameObjectList)
		Safe_Release(GOBJ);
}
