#include "../Include/PCH.h"

Bat::Bat(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bat::Bat(const GameObject& _RHS) : GameObject(_RHS) {}
Bat::~Bat() {}

HRESULT Bat::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	m_tInfo.eState[0] = MONSTER_STATE_SUMMON;

	m_tInfo.fHp = BAT_HP;

	return S_OK;
}
INT	Bat::Update_GameObject(const _float& _DT)
{
	if (m_tInfo.fHp <= 0.f)
		m_tInfo.Change_State(MONSTER_STATE_DEAD);

	GameObject::Update_GameObject(_DT);

	switch (m_tInfo.eState[0])
	{
	case MONSTER_STATE_SUMMON:
	case MONSTER_STATE_APPEAR:
		Bat::State_Appear(_DT);
		break;
	case MONSTER_STATE_IDLE:
		Bat::State_Idle();
		break;
	case MONSTER_STATE_TRACKING:
		Bat::State_Tracking(_DT);
		break;
	case MONSTER_STATE_CASTING:
		Bat::State_Casting(_DT);
		break;
	case MONSTER_STATE_CHANNELING:
		Bat::State_Channeling(_DT);
		break;
	case MONSTER_STATE_DEAD:
		Bat::State_Dead();
		break;
	default:
		break;
	}

	if (KEY_DOWN(DIK_Q)) {
		//Set_ObjectDead(TRUE);
		//Bat::Change_State(BAT_SUMMON);
		GameObject* test = Monster::Create<EvilSlime>(GRPDEV, { (_float)(rand() % 20), 0.5f, (_float)(rand() % 20)}, 3.f);
		Monster::Add_Monster_to_Scene(test);
		return 0;
	}
	if (KEY_DOWN(DIK_O)) {
		//Set_ObjectDead(TRUE);
		//Bat::Change_State(BAT_SUMMON);
		GameObject* test = Monster::Create<ShotGunEvilSoul>(GRPDEV, { (_float)(rand() % 20), 0.5f, (_float)(rand() % 20)}, 3.f);
		Monster::Add_Monster_to_Scene(test);
		return 0;
	}
	if (KEY_DOWN(DIK_P))
	{
		m_tInfo.Change_State(MONSTER_STATE_DEAD);
	}


	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Bat::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

	m_tInfo.vDirection.y = 0.f;
	Component_Transform->Move_Pos(D3DXVec3Normalize(&m_tInfo.vDirection, &m_tInfo.vDirection), m_tInfo.fSpeed, _DT);

	switch (m_tInfo.eState[0])
	{
	default:
		Monster::Set_TextureList(L"Spr_Monster_BlueEvilBat", &m_tInfo.Textureinfo);
		m_tInfo.Textureinfo._frameTick += _DT;
		if (m_tInfo.Textureinfo._frameTick > FRAMETICK)
		{
			m_tInfo.Textureinfo._frameTick = 0.f;
			++m_tInfo.Textureinfo._frame %= m_tInfo.Textureinfo._Endframe / 2;
		}
		break;
	}

	Monster::Flip_Horizontal(Component_Transform, &m_tInfo.vDirection, BAT_HORIZONTALFLIP_BUFFER);

	Monster::BillBoard(Component_Transform, GRPDEV);
}
VOID Bat::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());
	
	switch (m_tInfo.eState[0])
	{
	default:
		GRPDEV->SetTexture(0, m_tInfo.Textureinfo._vecTexture[m_tInfo.Textureinfo._frame]);
		Component_Buffer->Render_Buffer();
		break;
	case MONSTER_STATE_SUMMON:
	case MONSTER_STATE_APPEAR:
	case MONSTER_STATE_DEAD:
		break;
	}

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
BOOL Bat::OnCollisionEnter(GameObject* _Other)
{
	if (_Other->Get_ObjectTag() == L"PlayerArrow")
	{
		int atk = dynamic_cast<Arrow*>(_Other)->Get_Atk();
		_hp -= atk;
	}

	return 0;
}
HRESULT Bat::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(10.f, 0.112f, 10.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.289f, 0.223f, 1.f);

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);
	Component_Collider->Set_Scale(0.289f, 1.f, 0.289f);

	return S_OK;
}
Bat* Bat::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Bat* MST = new Bat(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create Bat.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
BOOL Bat::OnCollisionEnter(GameObject* _Other)
{
	wstring Tag = _Other->Get_ObjectTag();
	if (Tag == L"PlayerArrow")
	{
		Arrow* pArrow = static_cast<Arrow*>(_Other);
		//m_tColInfo._hp -= pArrow->Get_Atk();  // ¾ø³×;;
	}
	else
	{
		return false;
	}

	return TRUE;
}
BOOL Bat::OnCollisionStay(GameObject* _Other)
{
	return TRUE;
}
BOOL Bat::OnCollisionExit(GameObject* _Other)
{
	return TRUE;
}
VOID Bat::Free() {

	GameObject::Free();
}

VOID Bat::State_Appear(const _float& _DT)
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

VOID Bat::State_Idle()
{
	if (m_tInfo.pGameObj[0] == nullptr)
		m_tInfo.pGameObj[0]=(Monster::Set_Target(L"Player"));

	_vec3 vDir = *POS(m_tInfo.pGameObj[0]) - *MYPOS;
	vDir.y = 0.f;

	if (D3DXVec3Length(&vDir) < BAT_TRACKINGDIS)
		m_tInfo.Change_State(MONSTER_STATE_TRACKING);
}

VOID Bat::State_Tracking(const _float& _DT)
{
	if (nullptr == m_tInfo.pGameObj[0] || m_tInfo.pGameObj[0]->Get_ObjectDead())
		m_tInfo.Change_State(MONSTER_STATE_IDLE);

	m_tInfo.fSpeed = BAT_SPEED;
	m_tInfo.vDirection = *POS(m_tInfo.pGameObj[0]) - *MYPOS;

	if (D3DXVec3Length(&m_tInfo.vDirection) < BAT_TRACKINGDIS)
	{
		m_tInfo.fTimer[0] += _DT;
		m_tInfo.fTimer[1] = 0.f;
	}
	else
	{
		m_tInfo.fTimer[1] += _DT;
	}

	if (m_tInfo.fTimer[0] >= BAT_TRACKING_TIME)
	{
		m_tInfo.Change_State(MONSTER_STATE_CASTING);
	}
	else if (m_tInfo.fTimer[1] >= BAT_LOST_TIME)
	{
		m_tInfo.Change_State(MONSTER_STATE_IDLE);
	}

}
VOID Bat::State_Casting(const _float& _DT)
{
	if (nullptr == m_tInfo.pGameObj[0] || m_tInfo.pGameObj[0]->Get_ObjectDead())
		m_tInfo.Change_State(MONSTER_STATE_IDLE);

	m_tInfo.fTimer[0]	+= _DT;
	m_tInfo.fSpeed		 = 0.f;
	
	if (m_tInfo.fTimer[0] >= BAT_CASTING_TIME)
	{
		m_tInfo.Change_State(MONSTER_STATE_CHANNELING);
	}
}

VOID Bat::State_Channeling(const _float& _DT)
{
	if (nullptr == m_tInfo.pGameObj[0] || m_tInfo.pGameObj[0]->Get_ObjectDead())
		m_tInfo.Change_State(MONSTER_STATE_IDLE);

	m_tInfo.fSpeed = BAT_RUSHSPEED;
	m_tInfo.fTimer[0] += _DT;
	m_tInfo.fTimer[1] += _DT;

	if (m_tInfo.fTimer[1] >= BAT_CHANNELING_TIME / (BAT_BULLET_NUM + 1))
	{
		m_tInfo.fTimer[1] = 0.f;
		//m_tInfo.pGameObj[1] = Bullet_Standard::Create(GRPDEV);
		m_tInfo.pGameObj[1] = Monster::Create<Bullet_Standard>(GRPDEV, { MYPOS->x, 0.5f, MYPOS->z });

		Bullet_Standard* pBullet = static_cast<Bullet_Standard*>(m_tInfo.pGameObj[1]);
		pBullet->Set_Master(this);
		_vec3 vDir = *POS(m_tInfo.pGameObj[0]) - *MYPOS;
		D3DXVec3Normalize(&vDir, &vDir);
		pBullet->Set_Dir(vDir);

		Monster::Add_Monster_to_Scene(m_tInfo.pGameObj[1]);
		
	}

	if (m_tInfo.fTimer[0] >= BAT_CHANNELING_TIME)
	{
		m_tInfo.Change_State(MONSTER_STATE_IDLE);
	}
}

VOID Bat::State_Dead()
{
	PLAY_MONSTER_EFFECT_ONCE(MONSTER_EFFECT::MONSTER_DEATH, *MYPOS, 1.f);
	ObjectDead = true;
}
