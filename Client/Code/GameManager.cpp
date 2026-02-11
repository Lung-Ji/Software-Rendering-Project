#include "../Include/pch.h"
#include "GameManager.h"

GameManager::GameManager() : DEVCLASS(nullptr), GRPDEV(nullptr) {}
GameManager::~GameManager() { Free(); }

HRESULT GameManager::Ready_GameManager() {
	if (FAILED(Ready_DefaultSetting()))					return E_FAIL;
	ResourceManager::GetInstance()->GlobalImport_Texture(GRPDEV, L"../../UI");
	if (FAILED(Ready_SceneSetting()))					return E_FAIL;
	ResourceManager::GetInstance()->GlobalImport_Texture(GRPDEV, L"../../Resource");

	FontManager::GetInstance()->Ready_FontManager(GRPDEV);
	return S_OK;
}
VOID	GameManager::Update_GameManager(CONST FLOAT& _DT) {
	//TileManager::GetInstance()->Update_TileList(_DT);
	KeyManager::GetInstance()->Update_KeyManager(_DT);
	SceneManager::GetInstance()->Update_SceneManager(_DT);
}
VOID	GameManager::LateUpdate_GameManager(CONST FLOAT& _DT) {
	KeyManager::GetInstance()->LateUpdate_KeyManager(_DT);
	SceneManager::GetInstance()->LateUpdate_SceneManager(_DT);
}
VOID	GameManager::Render_GameManager() {
	DEVCLASS->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
	SceneManager::GetInstance()->Render_SceneManager(GRPDEV);
	
	//TileManager::GetInstance()->Render_TileList();
	//DEVCLASS->Render_End();
}
HRESULT GameManager::Ready_DefaultSetting() {
	if (FAILED(GraphicDevice::GetInstance()->Ready_GraphicDevice(hWnd, MODE_WIN, WINCX, WINCY, &DEVCLASS))) {
		MSG_BOX("Cannot Create Device.");
		return E_FAIL;
	}

	DEVCLASS->AddRef();

	GRPDEV = DEVCLASS->Get_Device();
	GRPDEV->AddRef();
	GRPDEV->SetRenderState(D3DRS_LIGHTING, FALSE);

	GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
	GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	GRPDEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GRPDEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	SoundManager::GetInstance()->Ready_SoundManager();
	
	return S_OK;
}
HRESULT GameManager::Ready_SceneSetting() {

	Scene* StartScene = StartScene::Create(GRPDEV);
	//Scene* StartScene = DebugScene::Create(GRPDEV);
	//Scene* MapScene = MapScene::Create(GRPDEV);
	if (StartScene == nullptr)	return E_FAIL;
	if (FAILED(SceneManager::GetInstance()->Scene_Transition(StartScene))) {
		MSG_BOX("Cannot Setting LogoScene.");
		Safe_Release(StartScene);
		return E_FAIL;
	}
	return S_OK;
}
GameManager* GameManager::Create() {
	GameManager* Instance = new GameManager;
	if (FAILED(Instance->Ready_GameManager())) {
		MSG_BOX("Cannot Create GameManager.");
		Safe_Release(Instance);
		return nullptr;
	}
	return Instance;
}
VOID		 GameManager::Free() {

	Safe_Release(DEVCLASS);
	Safe_Release(GRPDEV);

	GraphicDevice	::DestroyInstance();
	KeyManager		::DestroyInstance();
	CollisionManager::DestroyInstance();
	TimeManager		::DestroyInstance();
	SceneManager	::DestroyInstance();
	ProtoManager	::DestroyInstance();
	SoundManager	::DestroyInstance();
	RenderManager	::DestroyInstance();
	GUIManager		::DestroyInstance();
	TileManager		::DestroyInstance();
	ResourceManager	::DestroyInstance();
	UIManager		::DestroyInstance();
	EffectManager	::DestroyInstance();
	FontManager		::DestroyInstance();
	DEVCLASS		->DestroyInstance();
}