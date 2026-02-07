#pragma once
#include "Base.h"
#include "Scene.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"

BEGIN(Engine)

class ENGINE_DLL SceneManager : public Base {
	DECLARE_SINGLETON(SceneManager)
private:
	explicit SceneManager();
	virtual ~SceneManager();

public:
	HRESULT			Ready_SceneManager();
	INT				Update_SceneManager(CONST FLOAT& _DT);
	VOID			LateUpdate_SceneManager(CONST FLOAT& _DT);
	VOID			Render_SceneManager(LPDIRECT3DDEVICE9 _GRPDEV);

public:
	HRESULT			Scene_Transition(Scene* _SCENE);
	Scene*			Get_CurrentScene() { 
		return  CurrentScene;
	}
	GameObject*		Get_GameObject(CONST TCHAR* _TAG);
	void			Set_CurrentScene(Scene* scene) { CurrentScene = scene; }
private:
	Scene*			CurrentScene;

public:
	virtual			VOID	Free();
};

END