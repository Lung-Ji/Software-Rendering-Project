#include "../Include/PCH.h"

EvilSlime::EvilSlime(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
EvilSlime::EvilSlime(const GameObject& _RHS) : GameObject(_RHS) {}
EvilSlime::~EvilSlime() {}

HRESULT EvilSlime::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	m_tInfo.eState[0] = MONSTER_STATE_SUMMON;
	m_tInfo.fHp = EVILSLIME_HP;
	m_tInfo.vDirection = { -1.f,0.f,0.f };

	return S_OK;
}
INT	EvilSlime::Update_GameObject(const _float& _DT)
{
	// <플레이어 업데이트 시점>
	GameObject::Update_GameObject(_DT);

	Component_Transform->Get_Position()->y = MYSCALE->y * 0.5f;

	switch (m_tInfo.eState[0])
	{
	default:
		break;
	case MONSTER_STATE_SUMMON:
		EvilSlime::State_Summon(_DT);
		break;
	case MONSTER_STATE_IDLE:
		EvilSlime::State_Idle(_DT);
		break;
	case MONSTER_STATE_TRACKING:
		EvilSlime::State_Tracking(_DT);
		break;
	case MONSTER_STATE_CASTING:
		EvilSlime::State_Casting(_DT);
		break;
	case MONSTER_STATE_CHANNELING:
		EvilSlime::State_Channeling(_DT);
		break;
	case MONSTER_STATE_DEAD:
		EvilSlime::State_Dead();
		break;
	}

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}
VOID EvilSlime::LateUpdate_GameObject(const _float& _DT) {

	GameObject::LateUpdate_GameObject(_DT);

	m_tInfo.vDirection.y = 0.f;
	Component_Transform->Move_Pos(D3DXVec3Normalize(&m_tInfo.vDirection, &m_tInfo.vDirection), m_tInfo.fSpeed, _DT);

	m_tInfo.Textureinfo._frameTick += _DT;

	switch (m_tInfo.eState[0])
	{
	default:
		if (FAILED(Monster::Set_TextureList(L"Spr_Monster_BlueEvilSlime_Move", &m_tInfo)))
		{
			m_tInfo.Change_State(MONSTER_STATE_DEAD);
			return;
		}

		if (m_tInfo.Textureinfo._frameTick > 2.f * D3DX_PI)
			m_tInfo.Textureinfo._frameTick -= (2.f * D3DX_PI);
		
		{
			_float fNormalized = m_tInfo.Textureinfo._frameTick / (2.f * D3DX_PI);
			_float fTriangle = 1.f - fabsf(fNormalized * 2.f - 1.f);

			m_tInfo.Textureinfo._frame = (int)(fTriangle * 4.99f);
		}
		break;

	case MONSTER_STATE_TRACKING:
		if (FAILED(Monster::Set_TextureList(L"Spr_Monster_BlueEvilSlime_Move", &m_tInfo)))
		{
			m_tInfo.Change_State(MONSTER_STATE_DEAD);
			return;
		}

		if (m_tInfo.Textureinfo._frameTick >= FRAMETICK)
		{
			++m_tInfo.Textureinfo._frame %= m_tInfo.Textureinfo._Endframe;
			m_tInfo.Textureinfo._frameTick = 0.f;
		}
		break;

	case	MONSTER_STATE_CASTING:
		if (m_tInfo.Textureinfo._frameTick >= FRAMETICK)

	case MONSTER_STATE_APPEAR:
	case MONSTER_STATE_SUMMON:
	case MONSTER_STATE_DEAD:
		break;
	}
	Monster::BillBoard(Component_Transform, GRPDEV);
}
VOID EvilSlime::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	switch (m_tInfo.eState[0])
	{
	default:
		GRPDEV->SetTexture(0, m_tInfo.Textureinfo._vecTexture[m_tInfo.Textureinfo._frame]);
		Component_Buffer->Render_Buffer();
		break;
	case MONSTER_STATE_APPEAR:
	case MONSTER_STATE_SUMMON:
	case MONSTER_STATE_DEAD:
		break;
	}

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT EvilSlime::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(10.f, 0.5f, 0.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.384f, 0.311f, 1.f);
	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);

	Component_Collider->Set_Scale(0.28f, 1.f, 0.3f);

	return S_OK;
}
EvilSlime* EvilSlime::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	EvilSlime* MST = new EvilSlime(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create EvilSlime.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
BOOL EvilSlime::OnCollisionEnter(GameObject* _Other)
{
	return TRUE;
}
BOOL EvilSlime::OnCollisionStay(GameObject* _Other)
{
	switch (_Other->Get_ObjectType())
	{
	default:
		break;
	case GAMEOBJECT_TYPE::OBJECT_MONSTER:
		_vec3	vDir = *POS(_Other) - *MYPOS;
		if (D3DXVec3Dot(&m_tInfo.vDirection, &vDir) > 0.f)
		{
			switch (m_tInfo.eState[0])
			{
			default:
				m_tInfo.fSpeed = 0.f;
				break;
			case MONSTER_STATE_CASTING:
			case MONSTER_STATE_CHANNELING:
				break;
			}
		}
	}
	return TRUE;
}
BOOL EvilSlime::OnCollisionExit(GameObject* _Other)
{
	return TRUE;
}
VOID EvilSlime::Free() {

	GameObject::Free();
}

VOID EvilSlime::State_Summon(const _float& _DT)
{
	m_tInfo.fTimer[0] += _DT;
	if (nullptr == m_tInfo.pGameObj[0])
	{
		m_tInfo.bTrigger[0] = false;
		_vec3 vPos = { MYPOS->x, 0.01f, MYPOS->z };
		m_tInfo.pGameObj[0] = MonsterEffect::Create(GRPDEV, MONSTER_EFFECT::MONSTER_SUMMONS03, vPos, FALSE, MONSTER_SUMMON03_PLAYTIME);
		//*static_cast<Transform*>(pTarget->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Scale() = *Component_Transform->Get_Scale();
		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::MONSTER, m_tInfo.pGameObj[0]);
	}

	if (m_tInfo.fTimer[0] >= MONSTER_SUMMON03_PLAYTIME)
	{
		_vec3 vPos = { MYPOS->x, 0.01f, MYPOS->z };
		m_tInfo.fTimer[0] = 0.f;
		m_tInfo.bTrigger[0] = true;
		m_tInfo.pGameObj[0] = MonsterEffect::Create(GRPDEV, MONSTER_EFFECT::MONSTER_SUMMONS01, vPos, FALSE, MONSTER_SUMMON01_PLAYTIME);
		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::MONSTER, m_tInfo.pGameObj[0]);
		PLAY_MONSTER_EFFECT_ONCE(MONSTER_EFFECT::MONSTER_SUMMONS02, vPos, MONSTER_SUMMON02_PLAYTIME);
	}

	if (m_tInfo.bTrigger[0])
		if (m_tInfo.fTimer[0] >= (MONSTER_SUMMON01_PLAYTIME * 0.5f))
		{
			m_tInfo.Change_State(MONSTER_STATE_IDLE);
			m_tInfo.pGameObj[0] = nullptr;
		}
}

VOID EvilSlime::State_Idle(const _float& _DT)
{
	if (m_tInfo.pGameObj[0] == nullptr)
		m_tInfo.pGameObj[0] = (Monster::Set_Target(L"Player"));

	_vec3 vDir = *POS(m_tInfo.pGameObj[0]) - *MYPOS;
	vDir.y = 0.f;

	if (D3DXVec3Length(&vDir) < BAT_TRACKINGDIS)
		m_tInfo.Change_State(MONSTER_STATE_TRACKING);
}

VOID EvilSlime::State_Tracking(const _float& _DT)
{
	if (nullptr == m_tInfo.pGameObj[0] || m_tInfo.pGameObj[0]->Get_ObjectDead())
		m_tInfo.Change_State(MONSTER_STATE_IDLE);

	m_tInfo.vDirection = *POS(m_tInfo.pGameObj[0]) - *MYPOS;

	_float fDis = D3DXVec3Length(&m_tInfo.vDirection);

	m_tInfo.fSpeed = (fDis > SCORPIONEVILSOUL_TRACKINGMIN) * SCORPIONEVILSOUL_SPEED;

	if (fDis < EVILSLIME_TRACKINGDIS)
	{
		m_tInfo.fTimer[0] += _DT;
		m_tInfo.fTimer[1] = 0.f;
	}
	else
	{
		m_tInfo.fTimer[1] += _DT;
	}

	if (m_tInfo.fTimer[0] >= EVILSLIME_TRACKING_TIME)
	{
		m_tInfo.Change_State(MONSTER_STATE_CASTING);
	}
	else if (m_tInfo.fTimer[1] >= EVILSLIME_LOST_TIME)
	{
		m_tInfo.Change_State(MONSTER_STATE_IDLE);
	}
}

VOID EvilSlime::State_Casting(const _float& _DT)
{
	m_tInfo.fTimer[0] += _DT;

	if (nullptr == m_tInfo.pGameObj[0] || m_tInfo.pGameObj[0]->Get_ObjectDead())
		m_tInfo.Change_State(MONSTER_STATE_IDLE);

	if (nullptr == m_tInfo.pGameObj[1] && nullptr == m_tInfo.pGameObj[2])
	{
		m_tInfo.bTrigger[1] = true;
		_vec3 vDst = *POS(m_tInfo.pGameObj[0]);

		vDst.y = 0.01f;
		m_tInfo.pGameObj[2] = MonsterEffect::Create(GRPDEV, MONSTER_EFFECT::ALERT_CIRCLE, vDst, FALSE, EVILSLIME_CASTING_TIME);
		static_cast<Transform*>(m_tInfo.pGameObj[2]->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))
			->Set_Scale(2.f, 2.f, 2.f);
		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::MONSTER, m_tInfo.pGameObj[2]);

		vDst.y += 0.01f;
		m_tInfo.pGameObj[1] = MonsterEffect::Create(GRPDEV, MONSTER_EFFECT::ALERT_CIRCLE, vDst, FALSE, EVILSLIME_CASTING_TIME);
		static_cast<Transform*>(m_tInfo.pGameObj[1]->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))
			->Set_Scale(0.f, 0.f, 0.f);
		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::MONSTER, m_tInfo.pGameObj[1]);



		vDst = *POS(m_tInfo.pGameObj[1]) - *MYPOS;
		vDst.y = 0.f;
		m_fFlyingDis = D3DXVec3Length(&vDst);
		m_tInfo.fSpeed = m_fFlyingDis / EVILSLIME_CASTING_TIME;
		D3DXVec3Normalize(&m_tInfo.vDirection, &vDst);
	}
	else
	{
		Transform*	pDst		= static_cast<Transform*>(m_tInfo.pGameObj[1]->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		_vec3		vDir		= *static_cast<Transform*>(m_tInfo.pGameObj[2]->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position() - *MYPOS;
		_float		fRatio		= 1 - D3DXVec3Length(&vDir) / m_fFlyingDis;

		pDst->Set_Scale(fRatio * 2.f, fRatio * 2.f, fRatio * 2.f);
		//pDst->Get_Position()->y = fRatio;

		Component_Transform->Get_Position()->y += sinf(D3DX_PI * fRatio) * EVILSIME_JUMP_HEIGHT;
	}

	if (m_tInfo.fTimer[0] >= EVILSLIME_CASTING_TIME)
	{
		m_tInfo.pGameObj[1]->Set_ObjectDead(true);
		m_tInfo.pGameObj[2]->Set_ObjectDead(true);
		m_tInfo.pGameObj[1] = nullptr;
		m_tInfo.pGameObj[2] = nullptr;
		m_tInfo.Change_State(MONSTER_STATE_CHANNELING);
	}
}

VOID EvilSlime::State_Channeling(const _float& _DT)
{
	if (nullptr == m_tInfo.pGameObj[0] || m_tInfo.pGameObj[0]->Get_ObjectDead())
		m_tInfo.Change_State(MONSTER_STATE_IDLE);

	m_tInfo.fTimer[0] += _DT;

	if (m_tInfo.fTimer[0] >= EVILSLIME_CHANNELING_TIME)
	{
		for (int i = 0; i < EVILSLIME_BULLET_NUM; ++i)
		{
			m_tInfo.pGameObj[1] = Monster::Create<Bullet_Standard>(GRPDEV, *MYPOS);

			_float fRadian = 2.f * D3DX_PI * ((_float)i / EVILSLIME_BULLET_NUM);
			fRadian = (fRadian > D3DX_PI) ? fRadian - (2.f * D3DX_PI) : fRadian;

			static_cast<Bullet_Standard*>(m_tInfo.pGameObj[1])->Set_Dir(cosf(fRadian), 0.f, sinf(fRadian));

			Monster::Add_Monster_to_Scene(m_tInfo.pGameObj[1]);
		}
		m_tInfo.pGameObj[1] = nullptr;
		m_tInfo.Change_State(MONSTER_STATE_IDLE);
	}
}
VOID EvilSlime::State_Dead()
{
	PLAY_MONSTER_EFFECT_ONCE(MONSTER_EFFECT::MONSTER_DEATH, *MYPOS, 1.f);
	ObjectDead = true;
}