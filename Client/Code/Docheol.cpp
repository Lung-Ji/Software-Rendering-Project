#include "../Include/PCH.h"

Docheol::Docheol(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_pTarget(nullptr) {}
Docheol::Docheol(const GameObject& _RHS)	: GameObject(_RHS), m_pTarget(nullptr)	{}
Docheol::~Docheol() {}

HRESULT Docheol::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	Docheol::Update_GameObject(const _float& _DT)
{
	// <플레이어 업데이트 시점>

	if (m_pTarget == nullptr)
	{
		Monster::Set_Target(L"Player", m_pTarget);
	}

	_frameTick += _DT;
	switch (m_eCurrStatus)
	{
	case DOCHEOL_IDLE:
		break;
	default:
		break;
	}

	GameObject::Update_GameObject(_DT);

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Docheol::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
	RenderManager::Make_BillBoard(Component_Transform, GRPDEV);
}
VOID Docheol::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());
	if (_frameTick > 0.1f)
	{
		++_frame;
		_frameTick = 0.0f;
	}
	TCHAR FileName[256] = L"";
	switch (m_eCurrStatus)
	{
	case DOCHEOL_IDLE:
		wsprintfW(FileName, L"Spr_Boss_Docheol_%ls_%02d.png", L"Stand", _frame);
		if (_frame == 8)
			_frame = 1;
		break;
	default:
		break;
	}

	GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(FileName));
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Docheol::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(2.f, 2.f, 2.f);
	Component_Transform->Set_Pos(0.f, Component_Transform->Get_Scale()->y / 2.f, 0.f);

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);
	Component_Collider->Set_Scale(1.f, 1.f, 1.f);

	Change_Status(DOCHEOL_IDLE);

	return S_OK;
}

VOID Docheol::Change_Status(DOCHEOL_STATUS eState)
{
	m_ePrevStatus = m_eCurrStatus;
	m_eCurrStatus = eState;
	m_fTimer1 = 0.f;
	m_fTimer2 = 0.f;
	_frame = 0;
	_frameTick = 0.f;
}

Docheol* Docheol::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Docheol* MST = new Docheol(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create Docheol.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID Docheol::Free() 
{
	GameObject::Free();
}