#include "Spawner.h"
#include "../Include/PCH.h"

Spawner::Spawner(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_bSpawn(false),m_fTime(0), m_fFrame(0), m_bStopFrame(false), m_pBuffer(nullptr), m_pTransform(nullptr), m_pTileInfo(nullptr) {}
Spawner::Spawner(const GameObject& _RHS) : GameObject(_RHS) {}
Spawner::~Spawner() {}

HRESULT Spawner::Ready_GameObject(TILE_SIDE eid, TILE_SPAWNER eSpawn) {

	if (FAILED(Component_Initialize(eid, eSpawn))) return E_FAIL;

	return S_OK;
}
INT	Spawner::Update_GameObject(const _float& _DT) {

	GameObject::Update_GameObject(_DT);

	Frame_Move(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_TILE, this);

	return 0;

}
VOID Spawner::LateUpdate_GameObject(const _float& _DT) {

	_vec3		vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	AlphaYSorting(&vPos);

	GameObject::LateUpdate_GameObject(_DT);

}
VOID Spawner::Render_GameObject()
{
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());

	m_pBuffer->Render_Buffer();

	GRPDEV->SetTexture(0, NULL);
}

void Spawner::Set_Buffer(TILE_SIDE eid)
{
	switch (eid)
	{
	case TILE_SIDE::TILE_FRONT:
		m_pBuffer = ADD_COMPONENT_TILEFRONT;
		break;
	case TILE_SIDE::TILE_RIGHT:
		m_pBuffer = ADD_COMPONENT_TILERIGHT;
		break;
	case TILE_SIDE::TILE_LEFT:
		m_pBuffer = ADD_COMPONENT_TILELEFT;
		break;
	case TILE_SIDE::TILE_BACK:
		m_pBuffer = ADD_COMPONENT_TILEBACK;
		break;
	case TILE_SIDE::TILE_OTHER:
		m_pBuffer = ADD_COMPONENT_TILE;
		break;
	}
}

void Spawner::Frame_Move(const FLOAT& _DT)
{


	switch (m_pTileInfo->Get_Spawner())
	{
	case TILE_SPAWNER::NPC1:
		break;

	case TILE_SPAWNER::NPC2:
		break;
	
	case TILE_SPAWNER::MONSTER_SPAWN1:
		Monster_Spawn();
		break;
	case TILE_SPAWNER::MONSTER_SPAWN2:
		break;

	case TILE_SPAWNER::MONSTER_SPAWN3:
		break;

	case TILE_SPAWNER::MONSTER_SPAWN4:
		break;

	case TILE_SPAWNER::ITEM_SPAWN1:
		break;

	case TILE_SPAWNER::ITEM_SPAWN2:
		break;

	case TILE_SPAWNER::ITEM_SPAWN3:
		break;

	case TILE_SPAWNER::ITEM_SPAWN4:
		break;

	case TILE_SPAWNER::ITEM_SPAWN5:
		break;

	case TILE_SPAWNER::ITEM_SPAWN6:
		break;
	}

}

void Spawner::Monster_Spawn()
{

	if (!m_bSpawn)
	{
		_vec3 vPos;
		m_pTransform->Get_Info(INFO_POS, &vPos);
		SceneManager::GetInstance()->Get_CurrentScene()->Add_GameObjectToScene
			<Bat>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Bat");
		Bat* pBat = nullptr;

		pBat = dynamic_cast<Bat*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Bat"));

		dynamic_cast<Transform*>(pBat->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Pos(vPos);
		m_bSpawn = true;
	}
	
}

Transform* Spawner::Crash_Player()
{
	_vec3 vPos{}, vTilePos{};
	//플레이어와 부딪히면 다음 좌표로 이동
	Transform* pPlayer = dynamic_cast<Transform*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player")->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Player* OriginPlayer = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player"));

	pPlayer->Get_Info(INFO_POS, &vPos);

	m_pTransform->Get_Info(INFO_POS, &vTilePos);

	if (vPos.x > vTilePos.x - 1 && vPos.x < vTilePos.x + 1 && vPos.z > vTilePos.z - 1 && vPos.z < vTilePos.z + 1 && vTilePos.y < 2)
	{
		return pPlayer;
	}


	return nullptr;
}

HRESULT Spawner::Component_Initialize(TILE_SIDE eid, TILE_SPAWNER eSpawn) {

	m_pTransform = ADD_COMPONENT_TRANSFORM;
	m_pTileInfo = ADD_COMPONENT_TILEINFO;

	switch (eid)
	{
	case TILE_SIDE::TILE_FRONT:
		m_pBuffer = ADD_COMPONENT_TILEFRONT;
		break;
	case TILE_SIDE::TILE_RIGHT:
		m_pBuffer = ADD_COMPONENT_TILERIGHT;
		break;
	case TILE_SIDE::TILE_LEFT:
		m_pBuffer = ADD_COMPONENT_TILELEFT;
		break;
	case TILE_SIDE::TILE_OTHER:
		m_pBuffer = ADD_COMPONENT_TILE;
		break;
	}

	return S_OK;
}

Spawner* Spawner::Create(LPDIRECT3DDEVICE9 _GRPDEV, TILE_SIDE eid, TILE_SPAWNER eSpawn) {

	Spawner* pSpawner = new Spawner(_GRPDEV);

	if (FAILED(pSpawner->Ready_GameObject(eid, eSpawn))) {
		MSG_BOX("Cannot Create Spawner.");
		Safe_Release(pSpawner);
		return nullptr;
	}

	return pSpawner;
}
VOID Spawner::Free() {


	GameObject::Free();
}