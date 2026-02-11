#include "../Include/PCH.h"

ScorpoinEvilSoul::ScorpoinEvilSoul(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
ScorpoinEvilSoul::ScorpoinEvilSoul(const GameObject& _RHS) : GameObject(_RHS) {}
ScorpoinEvilSoul::~ScorpoinEvilSoul() {}

HRESULT ScorpoinEvilSoul::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	m_pTarget = nullptr;
	CurrState = SCROPOINEVILSOUL_APPEAR;
	PrevState = CurrState;

	m_fTimer1 = 0.f;
	m_fTimer2 = 0.f;

	m_fDefault_Speed = 1.f;
	m_fSpeed = 0.f;

	return S_OK;
}
INT	ScorpoinEvilSoul::Update_GameObject(const _float& _DT)
{
	// <플레이어 업데이트 시점>
	GameObject::Update_GameObject(_DT);

	m_tTexInfo._frameTick += _DT;
	if (m_tTexInfo._frameTick > 0.1f)
	{
		m_tTexInfo._frameTick = 0.f;
		if( CurrState == SCROPOINEVILSOUL_APPEAR)
			++m_tTexInfo._frame;
		else if( CurrState == SCROPOINEVILSOUL_DISAPPEAR)
			++m_tTexInfo._frame %= m_tTexInfo._Endframe;
		else
			++m_tTexInfo._frame %= m_tTexInfo._Endframe / 2;
	}

	switch (CurrState)
	{
	case SCROPOINEVILSOUL_APPEAR:
		ScorpoinEvilSoul::State_Appear();
		break;
	default:
	case SCROPOINEVILSOUL_IDLE:
		ScorpoinEvilSoul::State_Idle(_DT);
		break;
	case SCROPOINEVILSOUL_TRACKING:
		ScorpoinEvilSoul::State_Tracking(_DT);
		break;
	case SCROPOINEVILSOUL_CHARGING:
		ScorpoinEvilSoul::State_Charging(_DT);
		break;
	case SCROPOINEVILSOUL_ATTACKING:
	case SCROPOINEVILSOUL_HIT:
		break;
	case SCROPOINEVILSOUL_DISAPPEAR:
		break;
	}
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	if (GetAsyncKeyState('Q'))
		ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_APPEAR);
	if (GetAsyncKeyState('R'))
		ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_DISAPPEAR);

	return 0;
}
VOID ScorpoinEvilSoul::LateUpdate_GameObject(const _float& _DT) {
	
	GameObject::LateUpdate_GameObject(_DT);
	
	m_vDir.y = 0.f;
	Component_Transform->Move_Pos(D3DXVec3Normalize(&m_vDir, &m_vDir), m_fSpeed, _DT);

	switch (CurrState)
	{
	case SCROPOINEVILSOUL_APPEAR:
		Monster::Set_TextureList(L"Spr_Monster_BlueScorpionEvilSoul_appear", &m_tTexInfo);
		break;
	case SCROPOINEVILSOUL_IDLE:
	case SCROPOINEVILSOUL_TRACKING:
	case SCROPOINEVILSOUL_CHARGING:
	case SCROPOINEVILSOUL_ATTACKING:
	case SCROPOINEVILSOUL_HIT:
		Monster::Set_TextureList(L"Spr_Monster_BlueScorpionEvilSoul_Stand", &m_tTexInfo);
		Monster::Flip_Horizontal(Component_Transform, &m_vDir, 0.1f);
		if (fabsf(m_vDir.z) > 0.1f)
			if (m_vDir.z > 0.f)
					m_tTexInfo._frame += (m_tTexInfo._frame < m_tTexInfo._Endframe / 2) * m_tTexInfo._Endframe / 2;
		break;
	case SCROPOINEVILSOUL_DISAPPEAR:
		Monster::Set_TextureList(L"Spr_Monster_BlueScorpionEvilSoul_disappear", &m_tTexInfo);
		break;
	default:
		break;
	}

	Monster::BillBoard(Component_Transform, GRPDEV);
}
VOID ScorpoinEvilSoul::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, m_tTexInfo._vecTexture[m_tTexInfo._frame]);

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT ScorpoinEvilSoul::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(10.f, 0.5f, 0.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.572f, 0.896f, 1.f);
	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);

	Component_Collider->Set_Scale(0.5f, 1.f, 0.5f);

	return S_OK;
}
ScorpoinEvilSoul* ScorpoinEvilSoul::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	ScorpoinEvilSoul* MST = new ScorpoinEvilSoul(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create ScorpoinEvilSoul.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID ScorpoinEvilSoul::Free() {

	GameObject::Free();
}

VOID ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_STATE eState)
{
	m_fTimer1 = m_fTimer2 = m_fSpeed = 0.f;
	PrevState = CurrState;
	CurrState = eState;
}

VOID ScorpoinEvilSoul::State_Appear()
{
	if (m_tTexInfo._frame >= m_tTexInfo._Endframe)
		ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_IDLE);
}

VOID ScorpoinEvilSoul::State_Idle(const _float& _DT)
{
	if (nullptr == m_pTarget)
	{
		Monster::Set_Target(L"Player", m_pTarget);
		m_fTimer1 += _DT;
	}
	else
	{
		_vec3	Dir = *POS(m_pTarget) - *MYPOS;
		if (D3DXVec3Length(&Dir) < 100.f)
			ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_TRACKING);
	}

	//if (m_fTimer1 > 10.f)
	//	ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_DISAPPEAR);
}

VOID ScorpoinEvilSoul::State_Tracking(const _float& _DT)
{
	m_vDir = *POS(m_pTarget) - *MYPOS;
	m_fTimer1 += _DT;
	m_fSpeed = m_fDefault_Speed;

	if (D3DXVec3Length(&m_vDir) < 5.f)
		m_fTimer2 = 0.f;
	else
		m_fTimer2 += _DT;

	if (m_fTimer1 > 1.f)
		ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_CHARGING);
	else if(m_fTimer2 > 3.f)
		ScorpoinEvilSoul::Change_State(SCROPOINEVILSOUL_IDLE);
}

VOID ScorpoinEvilSoul::State_Charging(const _float& _DT)
{
}