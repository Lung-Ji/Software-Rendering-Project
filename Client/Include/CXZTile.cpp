#include "CXZTile.h"
#include "../Include/PCH.h"

CXZTile::CXZTile(LPDIRECT3DDEVICE9 _GRPDEV) : m_CubeBuffer(nullptr), m_pCollider(nullptr), GameObject(_GRPDEV), m_fTime(0), m_fFrame(0), m_bStopFrame(false), m_pBuffer(nullptr), m_pTransform(nullptr), m_pTileInfo(nullptr) {}
CXZTile::CXZTile(const GameObject& _RHS) : GameObject(_RHS) {}
CXZTile::~CXZTile() {  }

HRESULT CXZTile::Ready_GameObject(TILE_SIDE eid, TILE_STATE eState) {

	if (FAILED(Component_Initialize(eid, eState))) return E_FAIL;
	
	return S_OK;
}
INT	CXZTile::Update_GameObject(const _float& _DT) {
	
	GameObject::Update_GameObject(_DT);

	Frame_Move(_DT);
	
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_TILE, this);
		return 0;

}
VOID CXZTile::LateUpdate_GameObject(const _float& _DT) {

	_matrix		matBill, matWorld, matView;

	matWorld = *m_pTransform->Get_World();
	GRPDEV->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	// y축 회전만 제거
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 주의 할 것
	matWorld = matBill * matWorld;

	m_pTransform->Set_World(&matWorld);

	_vec3		vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	AlphaYSorting(&vPos);
	
	GameObject::LateUpdate_GameObject(_DT);

}
VOID CXZTile::Render_GameObject()
{
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	
	switch (m_pTileInfo->Get_TileStateName())
	{
	case TILE_STATE::STATE_NORMAL:
		GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		break;
	case TILE_STATE::STATE_COLLISION:
		GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		break; 
	case TILE_STATE::STATE_DESTORY:
		GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(m_pTileInfo->Get_AnimationName((_uint)(m_fFrame))));

		break;
	case TILE_STATE::STATE_ANIMATION:
		GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(m_pTileInfo->Get_AnimationName((_uint)(m_fFrame))));
		break;
	case TILE_STATE::STATE_POTAL:
		GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		break;
	case TILE_STATE::STATE_POTALEFFECT:
		if (m_pTileInfo->Get_PotalOpen())
		{
			GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(m_pTileInfo->Get_AnimationName((_uint)(m_fFrame))));
		}
		else return;
		
		break;
	case TILE_STATE::STATE_TRIGGER:
		GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		break;
	case TILE_STATE::STATE_POTALGASI:
		if (!m_pTileInfo->Get_PotalOpen())
		{
			GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());

		}
		else return;

	case TILE_STATE::STATE_POTALGASI_EFFECT:
		if (!m_pTileInfo->Get_PotalOpen())
		{
			GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		}
		else return;
		break;
	}

	if(m_pBuffer!=nullptr)
	m_pBuffer->Render_Buffer();

	
}

void CXZTile::Set_Buffer(TILE_SIDE eid)
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

void CXZTile::Frame_Move(const FLOAT& _DT)
{  

	switch (m_pTileInfo->Get_TileStateName())
	{
	case TILE_STATE::STATE_ANIMATION:  
		Tile_Animation(_DT);
		break;
	case TILE_STATE::STATE_COLLISION:
		break;
	case TILE_STATE::STATE_DESTORY: //플레이어 또는 몬스터 총알에 닿았을떄
		Tile_Destory(_DT);
		break;
	case TILE_STATE::STATE_POTAL:
		Tile_Potal(_DT);
		break;
	case TILE_STATE::STATE_POTALEFFECT:
		Tile_Potal_Effect(_DT);
		break;
	case TILE_STATE::STATE_TRIGGER:
		Tile_Trigger();
	case TILE_STATE::STATE_POTALGASI:
		break;
	case TILE_STATE::STATE_POTALGASI_EFFECT:
		Tile_Gasi_Destory();
		break;
	}
	
}

void CXZTile::Tile_Animation(const FLOAT& _DT)
{
	//플레이어와 충돌 했고, 플레이어가 충돌한 상태에서 이동 했을때 true
	Transform* pTransform = Crash_Player();
	Player* pPlayer = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player"));
	if (pTransform != nullptr && pPlayer->Get_Speed() != 0)
		m_bStopFrame = true;

	if (m_bStopFrame)
	{
		m_fTime += _DT;					//지난 시간
		if (m_fTime > 0.3f) //0.1초가 지나면
		{
			++m_fFrame;     //프레임 증가
			m_fTime = 0.f;	//시간 초기화

			if (m_fFrame >= (_float)m_pTileInfo->Get_TileTextureNumber() - 1.f)
			{
				m_fFrame = 0;
				m_bStopFrame = false;
			}
		}
	}


}
void CXZTile::Tile_Destory(const FLOAT& _DT)
{
	_vec3 Pos, Scale, Rot;
	if (m_fFrame == m_pTileInfo->Get_TileTextureNumber() - 1)
		return;
	m_pTransform->Get_Info(INFO_POS, &Pos);	
	Scale = *m_pTransform->Get_Scale();
	Rot   = *m_pTransform->Get_Rotation();
	Transform* pTransform = Crash_Player();
	TileDestoryEffect* pEffect = nullptr;
		m_bStopFrame = true;

	if (m_bStopFrame && pTransform != nullptr)
	{
		// 애니메이션 터트린후 프레임 ++
		// 현재 이미지 개수보다 크지 않을때 까지 이펙트 터트리고 카운트
			EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::ENVIROMENT, TileDestoryEffect::Create(GRPDEV, OBJECT_DESTORY::STONE, 8, Pos,Scale,Rot));
			
		if (!(m_fFrame >= m_pTileInfo->Get_TileTextureNumber() - 1))
		{
			++m_fFrame;
			//이펙트;
		}
		else
		{
			m_bStopFrame = false;
		}
			
	}
}
void CXZTile::Tile_Potal(const FLOAT& _DT)
{
	Transform*  pTransform = Crash_Player();
		if(Crash_Player() != nullptr)
			pTransform->Set_Pos(m_pTileInfo->Get_NextPos());
}
void CXZTile::Tile_Potal_Effect(const FLOAT& _DT)
{
	//몬스터가 다 잡히면 포탈을 랜더해라
	if (m_pTileInfo->Get_PotalOpen())
	{
		m_fTime += _DT;					//지난 시간
		if (m_fTime > 0.1f) //0.1초가 지나면
		{
			++m_fFrame;     //프레임 증가
			m_fTime = 0.f;	//시간 초기화
	
			if (m_fFrame >= (_float)m_pTileInfo->Get_TileTextureNumber() - 1.f)
			{
				m_fFrame = 0;
			}
		}
	}
}

void CXZTile::Tile_Trigger()
{
	if (Crash_Player() != nullptr)
		TileManager::GetInstance()->Set_Trigger(m_pTileInfo->Get_TileStage(),
			m_pTileInfo->Get_TileMode(), TILE_STATE::STATE_POTALEFFECT);
}

void CXZTile::Tile_Gasi_Destory()
{
	_vec3 Pos, Scale, Rot;
	m_pTransform->Get_Info(INFO_POS, &Pos);
	Scale = *m_pTransform->Get_Scale();
	Rot = *m_pTransform->Get_Rotation();
	Transform* pTransform = Crash_Player();
	TileDestoryEffect* pEffect = nullptr;
	
	
	if (m_pTileInfo->Get_PotalOpen() && !m_bStopFrame)
	{
		// 애니메이션 터트린후 프레임 ++
		// 현재 이미지 개수보다 크지 않을때 까지 이펙트 터트리고 카운트
		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::ENVIROMENT, TileDestoryEffect::Create(GRPDEV, OBJECT_DESTORY::POTALEFFECT, 7, Pos, Scale, Rot));
		m_bStopFrame = true;
	}
}

Transform* CXZTile::Crash_Player()
{
	_vec3 vPos{}, vTilePos{};
	//플레이어와 부딪히면 다음 좌표로 이동
	Transform* pPlayer = dynamic_cast<Transform*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player")->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM));

	pPlayer->Get_Info(INFO_POS, &vPos);
	m_pTransform->Get_Info(INFO_POS, &vTilePos);
	if (vPos.x > vTilePos.x - 1 && vPos.x < vTilePos.x + 1 && vPos.z > vTilePos.z - 1 && vPos.z < vTilePos.z + 1)
		return pPlayer;

	return nullptr;
}
HRESULT CXZTile::Component_Initialize(TILE_SIDE eid, TILE_STATE eState) {

	m_pTransform = ADD_COMPONENT_TRANSFORM;
	m_pTileInfo  = ADD_COMPONENT_TILEINFO;
	
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
	switch (eState)
	{
	case TILE_STATE::STATE_ANIMATION:
		m_CubeBuffer = ADD_COMPONENT_CUBE;
		break;
	case TILE_STATE::STATE_DESTORY:
		m_CubeBuffer = ADD_COMPONENT_CUBE;
		break;
	}
	
	return S_OK;
}

CXZTile* CXZTile::Create(LPDIRECT3DDEVICE9 _GRPDEV, TILE_SIDE eid, TILE_STATE eState) {
	
	CXZTile* pCXZTile = new CXZTile(_GRPDEV);
	
	if (FAILED(pCXZTile->Ready_GameObject(eid, eState))) {
		MSG_BOX("Cannot Create CXZTile.");
		Safe_Release(pCXZTile);
		return nullptr;
	}
	
	return pCXZTile;
}
VOID CXZTile::Free() {
	GameObject::Free();
}