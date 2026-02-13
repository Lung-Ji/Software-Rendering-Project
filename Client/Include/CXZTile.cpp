#include "CXZTile.h"
#include "../Include/PCH.h"

CXZTile::CXZTile(LPDIRECT3DDEVICE9 _GRPDEV) : m_fAlpha(0), m_CubeBuffer(nullptr), GameObject(_GRPDEV), m_fTime(0), m_fFrame(0), m_bStopFrame(false), m_pBuffer(nullptr), m_pTransform(nullptr), m_pTileInfo(nullptr) { ZeroMemory(&m_Material, sizeof(D3DMATERIAL9)); }
CXZTile::CXZTile(const GameObject& _RHS) : GameObject(_RHS) {}
CXZTile::~CXZTile() {  }

HRESULT CXZTile::Ready_GameObject(TILE_SIDE eid, TILE_STATE eState, FLOAT& X1, FLOAT& X2, FLOAT& Y1, FLOAT& Y2) {

	if (FAILED(Component_Initialize(eid, eState,X1, X2, Y1,Y2))) return E_FAIL;
	
	return S_OK;
}
INT	CXZTile::Update_GameObject(const _float& _DT) {
	
	GameObject::Update_GameObject(_DT);

	Frame_Move(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_TILE, this);
	
	if (m_fAlpha< 1.f)
		m_fAlpha+= _DT * m_fAlpha;
	if (m_fAlpha> 1.f)
		m_fAlpha= 1.f;
	else
	{
		if (m_fAlpha > 0.f)
			m_fAlpha -= _DT * m_fAlpha;
		if (m_fAlpha < 0.f)
			m_fAlpha = 0.f;
	}
	return 0;

}
VOID CXZTile::LateUpdate_GameObject(const _float& _DT) {

	_vec3		vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	AlphaYSorting(&vPos);
	
	GameObject::LateUpdate_GameObject(_DT);

}
VOID CXZTile::Render_GameObject()
{
	DWORD Argb = D3DCOLOR_ARGB( 255, 255, 255, 255);

	//GRPDEV->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//GRPDEV->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//GRPDEV->SetRenderState(D3DRS_ALPHAREF, 0xc0);

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
		if (!m_pTileInfo->Get_PotalOpen())
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
			break;
	case TILE_STATE::STATE_POTALGASI_EFFECT:
		
		if (!m_pTileInfo->Get_PotalOpen())
		{
		

		GRPDEV->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		GRPDEV->SetRenderState(D3DRS_TEXTUREFACTOR, Argb);
		
		GRPDEV->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		GRPDEV->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		GRPDEV->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		
		GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); //위에 두개 옵션 혼합해라
		GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		}
		else return;
		break;
	case TILE_STATE::STATE_UNDERTILE:
	{
		//GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		//GRPDEV->SetTexture(1, ResourceManager::GetInstance()->Find_Texture(m_pTileInfo->Get_BackGroundName(0)));
		//
		//GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		//GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		//
		//GRPDEV->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		//GRPDEV->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		//GRPDEV->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		//GRPDEV->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	}
		break;
	case TILE_STATE::STATE_POTALGASI_BREAK:
		if (!m_pTileInfo->Get_PotalOpen())
		{
			GRPDEV->SetTexture(0, m_pTileInfo->Get_Texture());
		}
		else
			return;
		break;
	}

	
	if (m_pBuffer != nullptr)
		m_pBuffer->Render_Buffer();
	
	if (m_pTileInfo->Get_TileStateName() == TILE_STATE::STATE_POTALGASI_EFFECT || m_pTileInfo->Get_TileStateName() == TILE_STATE::STATE_UNDERTILE)
	{

		GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTSS_ALPHAARG1);
		GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GRPDEV->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
		GRPDEV->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		GRPDEV->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		GRPDEV->SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
	}


	//GRPDEV->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	GRPDEV->SetTexture(0, NULL);
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

D3DMATERIAL9 CXZTile::Set_Material()
{
	m_Material.Diffuse.r = 0.1f;
	m_Material.Diffuse.g = 0.1f;
	m_Material.Diffuse.b = 0.1f;
	m_Material.Diffuse.a = 0.1f;

	return m_Material;
}

void CXZTile::Frame_Move(const FLOAT& _DT)
{  

	switch (m_pTileInfo->Get_TileStateName())
	{
	case TILE_STATE::STATE_ANIMATION:  
		Tile_Animation(_DT);
		break;
	case TILE_STATE::STATE_COLLISION:
		Crash_Player();
		break;
	case TILE_STATE::STATE_DESTORY: //플레이어 또는 몬스터 총알에 닿았을떄
		//Tile_Destory(_DT);
		//Crash_Arrow();
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

		//Tile_Gasi_Destory();
		break;
	case TILE_STATE::STATE_POTALGASI_BREAK:
		Tile_Gasi_Destory();
		break;
	}
	
}

void CXZTile::Tile_Animation(const FLOAT& _DT)
{
	//플레이어와 충돌 했고, 플레이어가 충돌한 상태에서 이동 했을때 true
	if (m_pTileInfo->Get_OnlyAnimation())
	{
		m_fTime += _DT;					//지난 시간
		if (m_fTime > 0.15f) //0.1초가 지나면
		{
			++m_fFrame;     //프레임 증가
			m_fTime = 0.f;	//시간 초기화

			if (m_fFrame >= (_float)m_pTileInfo->Get_TileTextureNumber() - 1.f)
			{
				m_fFrame = 0;
			}
		}
		return;
	}
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

	m_pTransform->Get_Info(INFO_POS, &Pos);
	Scale = *m_pTransform->Get_Scale();
	Rot = *m_pTransform->Get_Rotation();
	Transform* pTransform = Crash_Arrow();

	if (pTransform != nullptr)
	{
		m_bStopFrame = true;
	}

	if(pTransform != nullptr && m_pTileInfo->Get_OnlyAnimation() && m_fFrame < 1)
	{
		Scale.x *= 2.5;
		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::ENVIROMENT, TileDestoryEffect::Create(GRPDEV, OBJECT_DESTORY::POTALEFFECT, 7, Pos, Scale , Rot));
		Set_ObjectDead(TRUE);
		++m_fFrame;
	}
	
	if (m_bStopFrame && pTransform != nullptr && m_fFrame < m_pTileInfo->Get_TileTextureNumber() - 1.f)
	{
		// 애니메이션 터트린후 프레임 ++
		// 현재 이미지 개수보다 크지 않을때 까지 이펙트 터트리고 카운트
		if(!m_pTileInfo->Get_OnlyAnimation())
			EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::ENVIROMENT, TileDestoryEffect::Create(GRPDEV, OBJECT_DESTORY::STONE, 8, Pos,Scale * 2,Rot));
		++m_fFrame;
		//Set_ObjectDead(TRUE);
		m_bStopFrame = false;
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
	{
		TileManager::GetInstance()->Change_Stage(m_pTileInfo->Get_TileStage());
		TileManager::GetInstance()->Set_Trigger(m_pTileInfo->Get_TileStage(),
			m_pTileInfo->Get_TileMode(), TILE_STATE::STATE_POTALEFFECT);
	}

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
	Player* OriginPlayer = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player"));
	
	pPlayer->Get_Info(INFO_POS, &vPos);
	
	m_pTransform->Get_Info(INFO_POS, &vTilePos);

	if (vPos.x  > vTilePos.x - 1 && vPos.x < vTilePos.x + 1 && vPos.z > vTilePos.z - 1 && vPos.z  < vTilePos.z + 1 && vTilePos.y < 2)
	{
		return pPlayer;
	}


	return nullptr;
}
Transform* CXZTile::Crash_Arrow()
{
	_vec3 vPos{}, vTilePos{};
	//플레이어와 부딪히면 다음 좌표로 이동
	Arrow* pPArrow = nullptr;
	pPArrow = dynamic_cast<Arrow*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"PlayerArrow"));
	if (pPArrow == nullptr)
		return nullptr;
	Transform* ObjArrow = dynamic_cast<Transform*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"PlayerArrow")->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM));

	ObjArrow->Get_Info(INFO_POS, &vPos);

	m_pTransform->Get_Info(INFO_POS, &vTilePos);

	if (vPos.x > vTilePos.x - 1 && vPos.x < vTilePos.x + 1 && vPos.z > vTilePos.z - 1 && vPos.z < vTilePos.z + 1 && vTilePos.y < 2)
	{
		pPArrow->Set_ObjectDead(TRUE);
		return ObjArrow;
	}
	return nullptr;
}
HRESULT CXZTile::Component_Initialize(TILE_SIDE eid, TILE_STATE eState, FLOAT& X1, FLOAT& X2, FLOAT& Y1, FLOAT& Y2) {

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
	
	//switch (eState)
	//{
	//case TILE_STATE::STATE_ANIMATION:
	//	m_CubeBuffer = ADD_COMPONENT_CUBE;
	//	break;
	//case TILE_STATE::STATE_DESTORY:
	//	m_CubeBuffer = ADD_COMPONENT_CUBE;
	//	break;
	//}
	
	return S_OK;
}

CXZTile* CXZTile::Create(LPDIRECT3DDEVICE9 _GRPDEV, TILE_SIDE eid, TILE_STATE eState, FLOAT& X1 , FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2) {
	
	CXZTile* pCXZTile = new CXZTile(_GRPDEV);
	
	if (FAILED(pCXZTile->Ready_GameObject(eid, eState,X1 ,X2,Y1,Y2))) {
		MSG_BOX("Cannot Create CXZTile.");
		Safe_Release(pCXZTile);
		return nullptr;
	}
	
	return pCXZTile;
}
VOID CXZTile::Free() {


	GameObject::Free();
}