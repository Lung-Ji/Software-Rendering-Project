#include "../Include/PCH.h"

Fireball::Fireball(LPDIRECT3DDEVICE9 _GRPDEV) : 
	GameObject(_GRPDEV),
	m_pMaster(nullptr),
	m_fSpeed(2.f)	{}
Fireball::Fireball(const GameObject& _RHS) : 
	GameObject(_RHS),
	m_pMaster(nullptr),
	m_fSpeed(2.f){}
Fireball::~Fireball() {}

HRESULT Fireball::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	Fireball::Update_GameObject(const _float& _DT)
{
	// <플레이어 업데이트 시점>
	_frameTick += _DT;

	GameObject::Update_GameObject(_DT);

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Fireball::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
	Component_Transform->Move_Pos(&m_vDir, m_fSpeed, _DT);
	RenderManager::Make_BillBoard(Component_Transform, GRPDEV);
}
VOID Fireball::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	if (_frameTick > 0.1f)
	{
		++_frame;
		_frameTick = 0.0f;
	}

	if (_frame>10)
	{
		_frame = 1;
	}
	TCHAR FileName[256] = L"";
	wsprintfW(FileName, L"d%02d",_frame);

	GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(FileName));
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Fireball::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(0.2f, 1.f, 0.2f);
	Component_Transform->Set_Pos(0.f, 0.5f, 0.f);

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);
	Component_Collider->Set_Scale(1.f, 1.f, 1.f);

	return S_OK;
}

Fireball* Fireball::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Fireball* MST = new Fireball(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create Fireball.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID Fireball::Free()
{
	GameObject::Free();
}