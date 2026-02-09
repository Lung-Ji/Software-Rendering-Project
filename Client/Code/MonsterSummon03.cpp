#include "../Include/PCH.h"

MonsterSummon03::MonsterSummon03(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
MonsterSummon03::MonsterSummon03(const GameObject& _RHS) : GameObject(_RHS) {}
MonsterSummon03::~MonsterSummon03() {}


HRESULT MonsterSummon03::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;
}
INT	MonsterSummon03::Update_GameObject(const _float& _DT)
{
	if (ObjectDead)
		return 0;

	_frameTick += _DT;

	if (_frameTick > MONSTERSUMMON03PLAYTIME / MONSTERSUMMON01EFFECTMAX)
		++_frame;

	if (_frame > MONSTERSUMMON03EFFECTMAX)
	{
		ObjectDead = true;
		return 0;
	}

	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID MonsterSummon03::LateUpdate_GameObject(const _float& _DT) {

	if (ObjectDead)
	{
		return;
	}

	GameObject::LateUpdate_GameObject(_DT);

	RenderManager::Make_BillBoard(Component_Transform, GRPDEV);
}
VOID MonsterSummon03::Render_GameObject() {
	if (ObjectDead)
		return;

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, _Textures.vecTexture[_frame]);
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT MonsterSummon03::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	
	Component_Transform->Set_Scale(1.f, 1.f, 1.f);

	_frame = 0;
	_frameTick = 0.f;

	ZeroMemory(&_Textures, sizeof(_Textures));

	for (int i = 0; i < MONSTERSUMMON01EFFECTMAX; ++i)
	{
		TCHAR Filename[128] = L"";
		wsprintfW(Filename, L"Spr_Effect_MonsterSummons03(%s)_%02d", L"Blue", i);

		Monster::Set_Textureinfo(&_Textures, Filename);
	}

	return S_OK;
}

MonsterSummon03* MonsterSummon03::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MonsterSummon03* MST = new MonsterSummon03(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create MonsterSummon03.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}

VOID MonsterSummon03::Free()
{
	GameObject::Free();
}
