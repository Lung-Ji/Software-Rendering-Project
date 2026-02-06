#include "../Include/PCH.h"
#include"Bullet_Standard.h"

Bullet_Standard::Bullet_Standard(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bullet_Standard::Bullet_Standard(const GameObject& _RHS) : GameObject(_RHS) {}
Bullet_Standard::~Bullet_Standard() {}

HRESULT Bullet_Standard::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	Bullet_Standard::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	_frameTick += _DT;
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Bullet_Standard::LateUpdate_GameObject(const _float& _DT) {
	
	GameObject::LateUpdate_GameObject(_DT);

	Component_Transform->Move_Pos(&m_vDir, m_fSpeed, _DT);
}
VOID Bullet_Standard::Render_GameObject() {

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	TCHAR FileName[128] = L"";
	wsprintfW(FileName, L"Standard%d.png", _frame);

	Component_Texture->Set_Texture(FileName);

	if (_frameTick > 0.1f)
	{
		if (++_frame > 5)
			_frame = 1;

		_frameTick = 0.f;
	}
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Bullet_Standard::Component_Initialize() {

	m_fSpeed = 1.f;

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;


	Component_Transform->Set_Pos(1.f, 1.f, 1.f);
	Component_Transform->Set_Rotation(0.f, 0.f, 0.f);
	Component_Transform->Set_Scale(1.f, 1.f, 1.f);

	Component_Texture = ADD_COMPONENT_TEXTURE;
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Monster/Bullet");

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);

	_vec3 vColliderScale = *Component_Transform->Get_Scale();
	vColliderScale *= 0.3f;
	Component_Collider->Set_Scale(vColliderScale.x, 1.f, vColliderScale.z);

	return S_OK;
}
Bullet_Standard* Bullet_Standard::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Bullet_Standard* NPN = new Bullet_Standard(_GRPDEV);
	if (FAILED(NPN->Ready_GameObject())) {
		MSG_BOX("Cannot Create Bullet_Standard.");
		Safe_Release(NPN);
		return nullptr;
	}
	return NPN;
}
VOID Bullet_Standard::Free() {
	GameObject::Free();
}