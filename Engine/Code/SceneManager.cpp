#include "SceneManager.h"
IMPLEMENT_SINGLETON(SceneManager)

SceneManager::SceneManager() : CurrentScene(nullptr)	{			}
SceneManager::~SceneManager()							{	Free();	}

HRESULT SceneManager::Ready_SceneManager() {
	return S_OK;
}
INT		SceneManager::Update_SceneManager(const FLOAT& _DT) {
	EffectManager::GetInstance()->Update_EffectManager(_DT);
	return CurrentScene->Update_Scene(_DT);
}
VOID	SceneManager::LateUpdate_SceneManager(const FLOAT& _DT) {
	EffectManager::GetInstance()->LateUpdate_EffectManager(_DT);
	CurrentScene->LateUpdate_Scene(_DT);
}
VOID	SceneManager::Render_SceneManager(LPDIRECT3DDEVICE9 _GRPDEV) {
	RenderManager::GetInstance()->Render_GameObject(_GRPDEV);
	
	CollisionManager::GetInstance()->Render_CollisionManager();
	//CurrentScene->Render_Scene();
}
VOID	SceneManager::Free() {
	Safe_Release(CurrentScene);
}
HRESULT SceneManager::Scene_Transition(Scene* _SCENE) {
	if (_SCENE == nullptr)	return E_FAIL;

	if (CurrentScene != _SCENE)
	{
		Safe_Release(CurrentScene);
		CurrentScene = _SCENE;
	}

	return S_OK;
}
GameObject* SceneManager::Get_GameObject(CONST TCHAR* _TAG) {
	return CurrentScene->Get_GameObject(_TAG);
}