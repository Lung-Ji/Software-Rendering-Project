#include "../Include/PCH.h"
#include "MonsterEffect.h"

MonsterEffect::MonsterEffect(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV),	TextureIndex(0), FrameTick(0.f)		{}
MonsterEffect::MonsterEffect(CONST GameObject& _RHS)	: GameObject(_RHS),		TextureIndex(0), FrameTick(0.f)		{}
MonsterEffect::~MonsterEffect()																						{}

HRESULT MonsterEffect::Ready_Effect(MONSTER_EFFECT _SKILLTYPE, _vec3 vPos, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;

	Notify = 0;

	m_eEffect = _SKILLTYPE;

	switch (_SKILLTYPE)
	{
	case MONSTER_EFFECT::MONSTER_SUMMONS01:		Make_TextureList(L"Spr_Effect_MonsterSummons01");		break;
	case MONSTER_EFFECT::MONSTER_SUMMONS02:		Make_TextureList(L"Spr_Effect_MonsterSummons02");		break;
	case MONSTER_EFFECT::MONSTER_SUMMONS03:		Make_TextureList(L"Spr_Effect_MonsterSummons03");		break;
	case MONSTER_EFFECT::MONSTER_DEATH:			Make_TextureList(L"Spr_Effect_baseDeathEffect_B");		break;
	case MONSTER_EFFECT::ALERT_CIRCLE:			TextureList.push_back(ResourceManager::GetInstance()->Find_Texture(L"AlertCircle.png")); break;
	case MONSTER_EFFECT::SKILL_END:				default:		break;
	}


	Component_Transform->Set_Scale(2.f, 2.f, 2.f);

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

	TCHAR Filename[256] = L"";

	while (++_frame)
	{
		++ENDFRAME;
		swprintf_s(Filename, 256, L"%s_%02d.png", _Filename, ENDFRAME);
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
	if (TextureList.size() == 1)
	{
		ObjectDead = FRAMETICK >= PlayTime;
	}
	else if (FrameTick > PlayTime / ENDFRAME) {
		if (TextureIndex++ >= ENDFRAME - 2) {
			if (Repeatable) { TextureIndex = 0; }
			else {
				TextureIndex = ENDFRAME - 2;
				ObjectDead = TRUE;
			}
		}
		FrameTick = 0.f;
	}

	if (TextureIndex > ENDFRAME / 2)
		Notify = true;

	switch (m_eEffect)
	{
	default:
		Monster::BillBoard_Standard(GRPDEV, Component_Transform);
		break;
	case MONSTER_EFFECT::MONSTER_SUMMONS01:
		Monster::BillBoard(Component_Transform, GRPDEV);
		break;
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
MonsterEffect*	MonsterEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, MONSTER_EFFECT _SKILLTYPE, _vec3 vPos, BOOL _Repeatable = false, FLOAT _PlayTime = 1.f){
	MonsterEffect* EFT = new MonsterEffect(_GRPDEV);
	if (FAILED(EFT->Ready_Effect(_SKILLTYPE, vPos, _Repeatable, _PlayTime))) {
		MSG_BOX("Cannot Create Effect.");
		Safe_Release(EFT);
		return nullptr;
	}
	return EFT;
}
VOID MonsterEffect::Free() {
	GameObject::Free();
}