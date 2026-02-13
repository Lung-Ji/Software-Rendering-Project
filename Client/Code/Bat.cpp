#include "../Include/PCH.h"

Bat::Bat(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bat::Bat(const GameObject& _RHS) : GameObject(_RHS) {}
Bat::~Bat() {}

HRESULT Bat::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	Component_Transform->Get_Info(INFO_LOOK, &vDir);
	pTarget = nullptr;
	pTargetPos = nullptr;
	CurrState = BAT_IDLE;
	PrevState = CurrState;

	Timer1 = 0.f;
	Timer2 = 0.f;
	_hp = 100;

	Default_Speed = 1.f;
	Speed = Default_Speed;

	return S_OK;
}
INT	Bat::Update_GameObject(const _float& _DT)
{
	// <플레이어 업데이트 시점>
	GameObject::Update_GameObject(_DT);

	m_tTexInfo._frameTick += _DT;

	if (_hp <= 0)
		return -1;

	Set_Target(L"Player");

	if (pTarget == nullptr)
	{
		Change_State(BAT_IDLE);
	}

	switch (CurrState)
	{
	case BAT_IDLE:
		State_Idle();
		break;
	case BAT_TRACKING:
		State_Tracking(_DT);
		break;
	case BAT_ATTACKING:
		State_Attacking(_DT);
		break;
	case BAT_Hit:
		break;
	case BAT_DEAD:
		break;
	default:
		break;
	}
	if (KEY_DOWN(DIK_7)) {
		Set_ObjectDead(TRUE);
		return 0;
	}

	D3DXVec3Normalize(&vDir, &vDir);
	vDir.y = 0.f;
	Component_Transform->Move_Pos(&vDir, Speed, _DT);

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Bat::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

	Monster::Set_TextureList(L"Spr_Monster_BlueEvilBat", &m_tTexInfo);

	if (m_tTexInfo._frameTick > 0.1f)
	{
		m_tTexInfo._frameTick = 0.f;
		++m_tTexInfo._frame %= m_tTexInfo._Endframe / 2;
	}

	Monster::Flip_Horizontal(Component_Transform, &vDir, 0.1f);

	Monster::BillBoard(Component_Transform, GRPDEV);



}
VOID Bat::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());


	GRPDEV->SetTexture(0, m_tTexInfo._vecTexture[m_tTexInfo._frame]);

	Component_Buffer->Render_Buffer();

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

	Component_Transform->Set_Pos(10.f, 0.5f, 10.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.56f, 0.438f, 1.f);

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);

	Component_Collider->Set_Scale(0.3f, 0.3f, 0.3f);

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
VOID Bat::Free() {

	GameObject::Free();
}

VOID Bat::Set_Target(const TCHAR* _TAG)
{
	pTarget = SceneManager::GetInstance()->Get_GameObject(_TAG);
	if (pTarget != nullptr)
	{
		pTargetPos = POS(pTarget);
	}
}

VOID Bat::Change_State(BAT_STATE eState)
{
	PrevState = CurrState;
	CurrState = eState;
	Speed = 0.f;
	Timer1 = 0.f;
	Timer2 = 0.f;
}

VOID Bat::State_Idle()
{
	Speed = 0.f;
	Timer2 = 0.f;
	Timer1 = 0.f;

	if (pTarget != nullptr)
	{
		vDir = *POS(pTarget) - *MYPOS;
		vDir.y = 0;
		if (D3DXVec3Length(&vDir) < BATTRACKINGDIS)
		{
			Change_State(BAT_TRACKING);
		}
	}
}

VOID Bat::State_Tracking(const _float& _DT)
{
	Speed = Default_Speed;
	vDir = *POS(pTarget) - *MYPOS;
	vDir.y = 0;
	if (D3DXVec3Length(&vDir) < BATTRACKINGDIS)
	{
		Timer1 += _DT;
		Timer2 = 0.f;
	}
	else
	{
		Timer2 += _DT;
	}

	if (Timer1 >= BATTRACKINGMAX)
	{
		Change_State(BAT_ATTACKING);
	}

	if (Timer2 >= BATTRACKINGMIN)
	{
		Change_State(BAT_IDLE);
	}
}

VOID Bat::State_Attacking(const _float& _DT)
{
	Timer1 += _DT;
	if (Timer1 < BATATTACKREADY)
	{
		Speed = 0;
	}
	else if (Timer1 < BATATTACKEND)
	{
		Speed = Default_Speed * 5;
		Timer2 += _DT;

		if (Timer2 > 0.2f)
		{
			Timer2 = 0.f;
			GameObject* pBullet = Bullet_Standard::Create(GRPDEV);

			if (nullptr != pBullet)
			{
				pBullet->Set_ObjectTag(L"Bullet_Standard");
				static_cast<Transform*>(pBullet->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Pos(*MYPOS);
				static_cast<Bullet_Standard*>(pBullet)->Set_Master(this);
				_vec3 vShootingDir;
				vShootingDir = *pTargetPos - *MYPOS;
				static_cast<Bullet_Standard*>(pBullet)->Set_Dir(*D3DXVec3Normalize(&vShootingDir, &vShootingDir));
				SceneManager::GetInstance()->Get_CurrentScene()->Get_Layer(LAYER_TYPE::LAYER_STATIC_OBJECT)
					->Add_GameObject(pBullet);
				//CollisionManager::GetInstance()->Add_ColliderObject(pBullet);
			}
		}
	}
	else
	{
		Change_State(BAT_IDLE);
	}
}
