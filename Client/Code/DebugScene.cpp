#include "../Include/PCH.h"
#include "DebugScene.h"

DebugScene::DebugScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
DebugScene::~DebugScene() {}

HRESULT	DebugScene::Ready_Scene() {
	Scene::Ready_Scene();
	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);

	if (FAILED(Ready_Enviroment_Layer()))		return E_FAIL;
	if (FAILED(Ready_GameLogic_Layer()))		return E_FAIL;
	if (FAILED(Ready_UserInterface_Layer()))	return E_FAIL;

	PlayerInven* PI = dynamic_cast<PlayerInven*>(SceneManager::GetInstance()->Get_GameObject(L"PlayerInven"));

	ItemINFO* it01 = new ItemINFO;
	it01->ItemDesc = { L"초고리 활", L"무기/희귀", L"일반 공격", L"일반 공격력 24 ~ 26", L"공격 속도 2.5"
		, L"치명타 확률이 +3% 증가합니다.", L"매의 화살 : 치명타 피해를 입힌 적에게 5 초간 시선을 부여합니다."
		, L"매의 시선 : 치명타 확률이 +10% 증가하고, \n치명타 피해가 +20% 증가합니다.", L""
		, L"DIC_InvenFrame_MichaelBow", L"DIC_InfoFrame_MichaelBow"};
	it01->ItemPrice = 68;
	it01->ItemType = (int)ITEM_TYPE::WEAPON;
	
	PI->Append_Item(it01);
	
	ItemINFO* it02 = new ItemINFO;
	it02->ItemDesc = { L"풍수의 활", L"무기/희귀", L"일반 공격", L"이동 속도 + 20%", L"공격 속도 2.5"
		, L"그냥 빨라집니다.", L"풍수의 신 : 공격할 때마다 이동 속도가 증가합니다."
		, L"매의 시선 : 치명타 확률이 +10% 증가하고, \n치명타 피해가 +20% 증가합니다.", L""
		, L"DIC_InvenFrame_DarkBow", L"DIC_InfoFrame_DarkBow"};
	it02->ItemPrice = 68;
	it02->ItemType = (int)ITEM_TYPE::WEAPON;
	
	PI->Append_Item(it02);
	
	ItemINFO* it03 = new ItemINFO;
	it03->ItemDesc = { L"풍수의 활", L"무기/희귀", L"일반 공격", L"이동 속도 + 20%", L"공격 속도 2.5"
		, L"그냥 빨라집니다.", L"풍수의 신 : 공격할 때마다 이동 속도가 증가합니다."
		, L"매의 시선 : 치명타 확률이 +10% 증가하고, \n치명타 피해가 +20% 증가합니다.", L""
		, L"DIC_InvenFrame_GreenBow", L"DIC_InfoFrame_GreenBow" };
	it03->ItemPrice = 68;
	it03->ItemType = (int)ITEM_TYPE::WEAPON;
	
	PI->Append_Item(it03);
	
	ItemINFO* it04 = new ItemINFO;
	it04->ItemDesc = { L"얼음의 활", L"무기/희귀", L"일반 공격", L"빙결 효과", L"빙결 면역"
		, L"그냥 빨라집니다.", L"풍수의 신 : 공격할 때마다 이동 속도가 증가합니다."
		, L"매의 시선 : 치명타 확률이 +10% 증가하고, \n치명타 피해가 +20% 증가합니다.", L""
		, L"DIC_InvenFrame_IceBow", L"DIC_InfoFrame_IceBow" };
	it04->ItemPrice = 68;
	it04->ItemType = (int)ITEM_TYPE::WEAPON;
	
	PI->Append_Item(it04);
	
	ItemINFO* it05 = new ItemINFO;
	it05->ItemDesc = { L"얼음의 활", L"무기/희귀", L"일반 공격", L"빙결 효과", L"빙결 면역"
		, L"그냥 빨라집니다.", L"빙결 면역 : 공격할 때마다 이동 속도가 증가합니다."
		, L"빙결 효과 : 치명타 확률이 +10% 증가하고, \n치명타 피해가 +20% 증가합니다.", L""
		, L"DIC_InvenFrame_IceBow", L"DIC_InfoFrame_IceBow" };
	it05->ItemPrice = 68;
	it05->ItemType = (int)ITEM_TYPE::WEAPON;
	
	PI->Append_Item(it05);

	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	UIManager::GetInstance()->Ready_UIManager(GRPDEV);
	CollisionManager::GetInstance()->Get_AllObjectOfScene();

	return S_OK;
}
INT	 DebugScene::Update_Scene(CONST FLOAT& _DT) {
	CollisionManager::GetInstance()->Update_CollisionManager();
	UIManager::GetInstance()->Update_UIManager(_DT);
	return Scene::Update_Scene(_DT);
}
VOID DebugScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	UIManager::GetInstance()->LateUpdate_UIManager(_DT);
	CollisionManager::GetInstance()->LateUpdate_CollisionManager();
	CollisionManager::GetInstance()->Render_CollisionManager();
	Scene::LateUpdate_Scene(_DT);
}
VOID DebugScene::Render_Scene() {
	UIManager::GetInstance()->Render_UIManager(GRPDEV);
}
HRESULT DebugScene::Ready_Enviroment_Layer() {
	//Add_GameObjectToScene<Terrain>(LAYER_TYPE::LAYER_STATIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Terrain");
	return S_OK;
}
HRESULT DebugScene::Ready_GameLogic_Layer() {
	Add_GameObjectToScene<CameraObject>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA, L"Camera");
	Add_GameObjectToScene<Player>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_PLAYER, L"Player");
	//Add_GameObjectToScene<NPC>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_NPC, L"NPC_Tif");
	//Add_GameObjectToScene<Monster1>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Monster1");
	return S_OK;
}
HRESULT DebugScene::Ready_UserInterface_Layer() {
	//Add_GameObjectToScene<MainMenuButton>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"MainButton");
	//Add_GameObjectToScene<MainMenu>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"MainMenu");
	//Add_GameObjectToScene<MainUI>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"MainUI");
	Add_GameObjectToScene<PlayerInven>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"PlayerInven");
	//Add_GameObjectToScene<Augments>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"Augments");
	//Add_GameObjectToScene<NPCTalk>(LAYER_TYPE::LAYER_USER_INTERFACE, GAMEOBJECT_TYPE::OBJECT_UI, L"NPCTalk");

	return S_OK;
}
DebugScene* DebugScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	DebugScene* LS = new DebugScene(_GRPDEV);

	SceneManager::GetInstance()->Set_CurrentScene(LS);

	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create StartScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void DebugScene::Free() {
	Scene::Free();
}