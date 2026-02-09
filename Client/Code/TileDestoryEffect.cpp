#include "TileDestoryEffect.h"
#include "../Include/PCH.h"

TileDestoryEffect::TileDestoryEffect(LPDIRECT3DDEVICE9 _GRPDEV) :GameObject(_GRPDEV), m_bEffect(true), m_fTime(0), m_fFrame(0), m_pTileEffectBuff(nullptr), m_pTransform(nullptr){}
TileDestoryEffect::TileDestoryEffect(const GameObject& _RHS) : GameObject(_RHS) {}
TileDestoryEffect::~TileDestoryEffect() {  }

HRESULT TileDestoryEffect::Ready_GameObject(OBJECT_DESTORY eid, _int iCnt, _vec3 vPos, _vec3 vScale, _vec3 vRot) {


	if (FAILED(Component_Initialize())) return E_FAIL;

	m_pTransform->Set_Pos(vPos);
	m_pTransform->Set_Scale(vScale);
	m_pTransform->Set_Rotation(vRot);
	m_eDestory = eid;
	switch (m_eDestory)
	{
		case OBJECT_DESTORY::STONE:
		Add_Effect(OBJECT_DESTORY::STONE, L"StoneBox_Destruction_%d.png", iCnt);
		break;
		case OBJECT_DESTORY::POTALEFFECT:
		Add_Effect(OBJECT_DESTORY::POTALEFFECT, L"Spr_InfectionThorns_DestructionEffect_0%d.png", iCnt);
		break;
	}
		
	return S_OK;
}
INT	TileDestoryEffect::Update_GameObject(const _float& _DT) {

	GameObject::Update_GameObject(_DT);

	Frame_Move(_DT);
	
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_TILE, this);
		return 0;

}
VOID TileDestoryEffect::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

}

VOID TileDestoryEffect::Render_GameObject()
{
	
	if (m_bEffect)
	{

		GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
		GRPDEV->SetTexture(0, m_vecTileEffectList[static_cast<int>(m_eDestory)][m_fFrame]);

		m_pTileEffectBuff->Render_Buffer();
		
	}

}


void TileDestoryEffect::Frame_Move(const FLOAT& _DT)
{ 
	if (m_bEffect)
	{

		switch (m_eDestory)
		{
		case OBJECT_DESTORY::STONE:
			
				m_fTime += _DT;		 //지난 시간
				if (m_fTime > 0.1f) //0.1초가 지나면
				{
					++m_fFrame;     //프레임 증가
					m_fTime = 0.f;	//시간 초기화

					if (m_fFrame >= m_iCnt-1)
					{
						//m_fFrame = 1.f;
						m_bEffect = false;
						Set_ObjectDead(TRUE);
					}
				}
			break;
		case OBJECT_DESTORY::POTALEFFECT:
			m_fTime += _DT;		 //지난 시간
			if (m_fTime > 0.1f) //0.1초가 지나면
			{
				++m_fFrame;     //프레임 증가
				m_fTime = 0.f;	//시간 초기화

				if (m_fFrame >= m_iCnt - 1)
				{
					//m_fFrame = 1.f;
					m_bEffect = false;
					Set_ObjectDead(TRUE);
				}
			}
			break;
		}
	}
	
	
}

void TileDestoryEffect::Add_Effect(OBJECT_DESTORY eid, const _tchar* pName, _int iCnt)
{
	for (_int i = 1; i < iCnt+1; ++i)
	{
		TCHAR   Name[128] = L"";
		wsprintf(Name, pName, i);
		auto Tex = ResourceManager::GetInstance()->Find_Texture(Name);
		if (Tex != nullptr)
		{
			Tex->AddRef();
			m_vecTileEffectList[static_cast<int>(eid)].push_back(Tex);
		}

		
	}
	m_iCnt = iCnt;
	
}


HRESULT TileDestoryEffect::Component_Initialize() {

	m_pTileEffectBuff = ADD_COMPONENT_TILEFRONT;
	m_pTransform = ADD_COMPONENT_TRANSFORM;
	
	return S_OK;
}

TileDestoryEffect* TileDestoryEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, OBJECT_DESTORY eid, _int iCnt, _vec3 vPos, _vec3 vScale, _vec3 vRot) {
	
	TileDestoryEffect* pTileDestoryEffect = new TileDestoryEffect(_GRPDEV);
	
	if (FAILED(pTileDestoryEffect->Ready_GameObject(eid, iCnt, vPos, vScale, vRot))) {
		MSG_BOX("Cannot Create TileDestoryEffect.");
		Safe_Release(pTileDestoryEffect);
		return nullptr;
	}
	
	return pTileDestoryEffect;
}
VOID TileDestoryEffect::Free() {

	for(auto& iter : m_vecTileEffectList[static_cast<int>(m_eDestory)])
			Safe_Release(iter);

	GameObject::Free();
}