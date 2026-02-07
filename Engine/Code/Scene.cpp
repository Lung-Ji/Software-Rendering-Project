#include "Scene.h"

Scene::Scene() : GRPDEV(nullptr)                            {                   }
Scene::Scene(LPDIRECT3DDEVICE9 _GRPD)   : GRPDEV(_GRPD)     { GRPDEV->AddRef(); }
Scene::~Scene()                                             {                   }

HRESULT Scene::Ready_Scene() {
    for (INT INDEX = 0; INDEX < (LONG)LAYER_TYPE::LAYER_END; ++INDEX) {
        Layer* NewLayer = Layer::Create();
        LayerList.push_back(NewLayer);
    }
    return S_OK;
}
INT Scene::Update_Scene(const FLOAT& _DT) {
    for (auto& LYR : LayerList)
        LYR->Update_Layer(_DT);
    return 0;
}
VOID Scene::LateUpdate_Scene(const FLOAT& _DT) {
    for (auto& LYR : LayerList)
        LYR->LateUpdate_Layer(_DT);
}
Layer* Scene::Get_Layer(LAYER_TYPE _LID)    {
    return LayerList[(LONG)_LID];
}
GameObject* Scene::Get_GameObject(CONST TCHAR* _TAG) {
    for (auto& LYR : LayerList) {
        GameObject* Target = LYR->Get_GameObject(_TAG);
        if (Target != nullptr) return Target;
    }
    return nullptr;
}
VOID	Scene::Free() {
    for (auto& LYR : LayerList)
        Safe_Release(LYR);
    Safe_Release(GRPDEV);
}