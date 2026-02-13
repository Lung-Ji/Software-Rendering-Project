#include "../Include/PCH.h"

ScorpionBullet::ScorpionBullet(LPDIRECT3DDEVICE9 _GRPDEV) :
	GameObject(_GRPDEV),
	m_pMaster(nullptr),
	m_fSpeed(2.f) {
}
ScorpionBullet::ScorpionBullet(const GameObject& _RHS) :
	GameObject(_RHS),
	m_pMaster(nullptr),
	m_fSpeed(2.f) {
}
ScorpionBullet::~ScorpionBullet() {}

HRESULT ScorpionBullet::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	m_fKillTimer = 0.f;
	return S_OK;
}
INT	ScorpionBullet::Update_GameObject(const _float& _DT)
{
	Monster::Set_TextureList(L"Spr_Bullet_ScorpionBullet", &m_tTexInfo);

	m_fKillTimer += _DT;
	if (m_fKillTimer > 20.f)
	{
		ObjectDead = true;
		return 0;
	}

	m_tTexInfo._frameTick += _DT;
	if (m_tTexInfo._frameTick > 0.f)
		++m_tTexInfo._frame %= m_tTexInfo._Endframe;

	GameObject::Update_GameObject(_DT);

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID ScorpionBullet::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);

	m_vDir.y = 0.f;
	Component_Transform->Move_Pos(&m_vDir, m_fSpeed, _DT);

	Monster::BillBoard(Component_Transform, GRPDEV);

	_matrix* pmatWorld = Component_Transform->Get_World();
	_matrix matView, matRot;
	_vec3* vAxis = (_vec3*)&matView._31;
	_float Radian = D3DX_PI / 2 * m_tTexInfo._frame / m_tTexInfo._Endframe;

	GRPDEV->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXMatrixRotationAxis(&matRot, vAxis, Radian);

	_vec3 vPos = { pmatWorld->_41,pmatWorld->_42, pmatWorld->_43 };
	pmatWorld->_41 = pmatWorld->_42 = pmatWorld->_43 = 0.f;

	*Component_Transform->Get_World() *= matRot;
	pmatWorld->_41 = vPos.x;
	pmatWorld->_42 = vPos.y;
	pmatWorld->_43 = vPos.z;


	Component_Collider->Set_Scale(MYSCALE->x, 1.f, MYSCALE->z);
	//AlphaSorting(Component_Transform->Get_Position());
	//AlphaSorting((_vec3*)&Component_Transform->Get_World()->_41);
}
VOID ScorpionBullet::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, m_tTexInfo._vecTexture[m_tTexInfo._frame]);
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT ScorpionBullet::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.2f, 0.2f, 0.2f);
	Component_Transform->Set_Pos(0.f, 0.5f, 0.f);

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);
	Component_Collider->Set_Scale(1.f, 1.f, 1.f);

	return S_OK;
}

ScorpionBullet* ScorpionBullet::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	ScorpionBullet* MST = new ScorpionBullet(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create ScorpionBullet.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID ScorpionBullet::Free()
{
	GameObject::Free();
}