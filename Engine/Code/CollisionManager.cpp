#include "CollisionManager.h"
#include "SceneManager.h"

IMPLEMENT_SINGLETON(CollisionManager)

CollisionManager::CollisionManager()	{}
CollisionManager::~CollisionManager()	{}

INT CollisionManager::Update_CollisionManager() {

	return 0;
}

VOID CollisionManager::Get_AllObjectOfScene() {
	Layer* SceneLayer = SceneManager::GetInstance()->Get_CurrentScene()->Get_Layer(LAYER_TYPE::LAYER_DYNAMIC_OBJECT);
	SceneLayer->Get_GameObject(GAMEOBJECT_TYPE::OBJECT_CAMERA);
}

VOID CollisionManager::Free() {

}