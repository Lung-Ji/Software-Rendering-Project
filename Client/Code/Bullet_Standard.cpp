#include "../Include/PCH.h"
#include"Bullet_Standard.h"

Bullet_Standard::Bullet_Standard(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bullet_Standard::Bullet_Standard(const GameObject& _RHS) : GameObject(_RHS) {}
Bullet_Standard::~Bullet_Standard() {}

HRESULT Bullet_Standard::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	Monster::Set_TextureList(L"Spr_Bullet_Standard", &m_tInfo);
	m_tInfo.fSpeed = BULLET_STANDARD_SPEED;
	m_tInfo.fHp = 1.f;

	return S_OK;
}
INT	Bullet_Standard::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);

	m_tInfo.fTimer[0] += _DT;

	if (m_tInfo.fTimer[0] > 30.f)
		ObjectDead = true;

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Bullet_Standard::LateUpdate_GameObject(const _float& _DT) {
	
	GameObject::LateUpdate_GameObject(_DT);
	
	_vec3 ColliderScale = *Component_Transform->Get_Scale();

	Component_Collider->Set_Scale(MYSCALE->x * 0.8f, 1.f, MYSCALE->z * 0.8f);

	m_tInfo.vDirection.y = 0.f;
	Component_Transform->Move_Pos(&m_tInfo.vDirection, m_tInfo.fSpeed, _DT);

	m_tInfo.Textureinfo._frameTick += _DT;
	if (m_tInfo.Textureinfo._frameTick > FRAMETICK)
	{
		++m_tInfo.Textureinfo._frame %= m_tInfo.Textureinfo._Endframe;
		m_tInfo.Textureinfo._frameTick = 0.f;
	}

	Monster::BillBoard(Component_Transform, GRPDEV);
}
VOID Bullet_Standard::Render_GameObject() {

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTexture(0, m_tInfo.Textureinfo._vecTexture[m_tInfo.Textureinfo._frame]);


	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Bullet_Standard::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(1.f, 0.5f, 1.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.1f, 0.1f, 0.1f);

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);

	Component_Collider->Set_Scale(0.5f, 0.5f, 0.5f);

	return S_OK;
}
//Bullet_Standard* Bullet_Standard::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
//	Bullet_Standard* NPN = new Bullet_Standard(_GRPDEV);
//	if (FAILED(NPN->Ready_GameObject())) {
//		MSG_BOX("Cannot Create Bullet_Standard.");
//		Safe_Release(NPN);
//		return nullptr;
//	}
//	return NPN;
//}
VOID Bullet_Standard::Free() {
	GameObject::Free();
}
//
//VOID Bullet_Standard::BillBoard()
//{
//	_matrix		matBill, matWorld, matView;
//
//	matWorld = *Component_Transform->Get_World();
//	GRPDEV->GetTransform(D3DTS_VIEW, &matView);
//
//	D3DXMatrixIdentity(&matBill);
//
//	//X축
//	matBill._11 = matView._11;
//	matBill._12 = matView._12;
//	matBill._13 = matView._13;
//	//Y축
//	matBill._21 = matView._21;
//	matBill._22 = matView._22;
//	matBill._23 = matView._23;
//	//Z축
//	matBill._31 = matView._31;
//	matBill._32 = matView._32;
//	matBill._33 = matView._33;
//
//	D3DXMatrixInverse(&matBill, 0, &matBill);
//
//	// 주의 할 것
//	matWorld = matBill * matWorld;
//
//	Component_Transform->Set_World(&matWorld);
//}
