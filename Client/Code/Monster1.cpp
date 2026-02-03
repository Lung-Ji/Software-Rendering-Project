#include "../Include/PCH.h"

Monster1::Monster1(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Monster1::Monster1(const GameObject& _RHS) : GameObject(_RHS) {}
Monster1::~Monster1() {}

HRESULT Monster1::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	Is_Tracking = false;
	Tracking_Counter = 0;
	Lost_Counter = 0;

	Is_Attacking = false;

	Default_Speed = 300.f;
	Speed = Default_Speed;

	return S_OK;
}
INT	Monster1::Update_GameObject(const _float& _DT) 
{
	GameObject::Update_GameObject(_DT);
	_vec3 TargetPos = *dynamic_cast<Transform*>(SceneManager::GetInstance()->Get_GameObject(L"Player")->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position();

	_vec3 Dir = TargetPos - *Component_Transform->Get_Position();
	//float time = 3.f;
	//if (플레이어가 밖) {
	//	time -= _DT;
	//	if (time < 0) {
	//		
	//	}
	//}
	if (D3DXVec3Length(&Dir) < TRACKINGDIS)
	{
		if (!Is_Tracking)
			Tracking_Counter = 0;
		
		Lost_Counter = 0;
		Is_Tracking = true;
	}
	else
	{
		++Lost_Counter;
	}

	if (Lost_Counter > TRACKINGTIME)
		Is_Tracking = false;

	if (Is_Tracking)
	{
		++Tracking_Counter;
		Speed = Default_Speed;
		Component_Transform->Move_Pos(D3DXVec3Normalize(&Dir, &Dir), Speed, _DT);
	}
	else
	{
		if (!Is_Attacking)
		{
			Speed = 0;
		}
	}

	if (Tracking_Counter > 300)
	{
		if (Tracking_Counter < 400)
		{
			Is_Attacking = true;
			Speed = 0;
		}
		else if (Tracking_Counter < 500)
		{
			Speed = RUSHSPEED;
		}
		else
		{
			Is_Attacking = false;
			Speed = Default_Speed;
			Tracking_Counter = 0;
		}
	}


	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Monster1::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
}
VOID Monster1::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	Component_Texture->Set_Texture(L"Monster1.png");

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Monster1::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(0.f, 0.f, 1.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(2.f, 2.f, 2.f);

	Component_Texture = ADD_COMPONENT_TEXTURE;
	Component_FSM = ADD_COMPONENT_FSM;

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Monster");
	Component_FSM->FSM_StateInit(MONSTER_IDLE::GetInstance()->Instance());

	//pTarget = SceneManager::GetInstance()->Get_GameObject(L"Player");

	return S_OK;
}
Monster1* Monster1::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Monster1* MST = new Monster1(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create Monster1.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID Monster1::Free() {

	MONSTER_IDLE::DestroyInstance();
	MONSTER_ATTACK::DestroyInstance();
	MONSTER_CHASE::DestroyInstance();
	MONSTER_DAMAGED::DestroyInstance();
	MONSTER_DEAD::DestroyInstance();

	GameObject::Free();
}