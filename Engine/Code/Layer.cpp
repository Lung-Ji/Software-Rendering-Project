#include "Layer.h"

Layer::Layer() {}
Layer::~Layer() {}

HRESULT		Layer::Ready_Layer() {
	return S_OK;
}
INT			Layer::Update_Layer(const FLOAT& _DT) {
	int ObjectResult = 0;
	for (auto& GOBJ : GameObjectList) {
		if (GOBJ->Get_ObjectDead() == FALSE) {
			ObjectResult = GOBJ->Update_GameObject(_DT);
		}
		if(ObjectResult == -1)
			Safe_Release(GOBJ);
	}
	return 0;
}
VOID		Layer::LateUpdate_Layer(const FLOAT& _DT) {
	for (auto& GOBJ : GameObjectList) {
		if (!GOBJ->Get_ObjectDead())
			GOBJ->LateUpdate_GameObject(_DT);
	}
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
