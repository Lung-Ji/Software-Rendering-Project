#include "../Include/PCH.h"
#include "MonsterEffect.h"

MonsterEffect::MonsterEffect(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV),	TextureIndex(0), FrameTick(0.f)		{}
MonsterEffect::MonsterEffect(CONST GameObject& _RHS)	: GameObject(_RHS),		TextureIndex(0), FrameTick(0.f)		{}
MonsterEffect::~MonsterEffect()																						{}

HRESULT MonsterEffect::Ready_Effect(CONST TCHAR* _Filename, _vec3 vPos, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;

	if (FAILED(Make_TextureList(_Filename)))
	{
		ObjectDead = true;
		return E_FAIL;
	}

	//if		(_SKILLTYPE == MONSTER_SKILL::SKILL_1) { Make_TextureList(L"Spr_Effect_ExplosionNormal02_"); }
	//else if (_SKILLTYPE == MONSTER_SKILL::SKILL_2) { Make_TextureList(L"Spr_Ui_Effect_BossClear_lraCharge_"); }
	//else if (_SKILLTYPE == MONSTER_SKILL::SKILL_3) { Make_TextureList(L"Spr_Ui_Stage01_TureMapEffect_"); }

	Component_Transform->Set_Pos(vPos);
	Repeatable = _Repeatable;

	PlayTime = _PlayTime;

	return S_OK;
}

HRESULT MonsterEffect::Make_TextureList(CONST TCHAR* _Filename)
{
	ENDFRAME = 0;
	INT _frame = 0;
	IDirect3DTexture9* pTexture = nullptr;

	while (++_frame)
	{
		++ENDFRAME;
		TCHAR Filename[256] = L"";
		swprintf_s(Filename, 256, L"%s_%02d", _Filename, ENDFRAME);
		pTexture = ResourceManager::GetInstance()->Find_Texture(Filename);
		if (nullptr == pTexture) break;
		TextureList.push_back(pTexture);
	}

	ENDFRAME = _frame - 1;

	if (ENDFRAME == 0)
		return E_FAIL;

	return S_OK;
}


//HRESULT MonsterEffect::Make_TextureList(wstring _FileName) {
//	INT FRAME = 0;
//	while (++FRAME) {
//		wstring FileName = _FileName + to_wstring(FRAME) + L".png";
//		IDirect3DBaseTexture9* TEX = ResourceManager::GetInstance()->Find_Texture(FileName.c_str());
//		if (TEX == nullptr) break;
//		else { TextureList.push_back(TEX); }
//	}
//	ENDFRAME = TextureList.size() + 1;
//
//	return S_OK;
//}

INT  MonsterEffect::Update_GameObject(CONST FLOAT& _DT) {
	if (ObjectDead)	return 0;
	GameObject::Update_GameObject(_DT);

	FrameTick += _DT;

	return 0;
}
VOID MonsterEffect::LateUpdate_GameObject(CONST FLOAT& _DT) {
	if (ObjectDead)	return;

	//_matrix World = *Component_Transform->Get_World();
	//_matrix BillBoard = RenderManager::Make_BillBoardMatrix(World, GRPDEV);
	//World *= BillBoard;
	//Component_Transform->Set_World(&World);

	if (FrameTick > PlayTime / ENDFRAME) {
		if (TextureIndex++ >= ENDFRAME - 2) {
			if (Repeatable) { TextureIndex = 0; }
			else {
				TextureIndex = ENDFRAME - 2;
				ObjectDead = TRUE;
			}
		}
		FrameTick = 0.f;
	}
}
VOID MonsterEffect::Render_GameObject() {
	if (ObjectDead)	return;
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, TextureList[TextureIndex]);

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

BOOL MonsterEffect::OnCollisionEnter(GameObject* _Other) {
	return TRUE;
}
BOOL MonsterEffect::OnCollisionStay(GameObject* _Other) {
	return TRUE;
}
BOOL MonsterEffect::OnCollisionExit(GameObject* _Other) {
	return TRUE;
}
HRESULT			MonsterEffect::Component_Initialize() {
	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	return S_OK;
}
MonsterEffect*	MonsterEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _Filename, _vec3 vPos, BOOL _Repeatable = false, FLOAT _PlayTime = 1.f){
	MonsterEffect* EFT = new MonsterEffect(_GRPDEV);
	if (FAILED(EFT->Ready_Effect(_Filename, vPos, _Repeatable, _PlayTime))) {
		MSG_BOX("Cannot Create Effect.");
		Safe_Release(EFT);
		return nullptr;
	}
	return EFT;
}
VOID MonsterEffect::Free() {
	GameObject::Free();
}