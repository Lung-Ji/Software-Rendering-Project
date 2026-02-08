#include "../Include/PCH.h"
#include "MonsterEffect.h"

MonsterEffect::MonsterEffect(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV),	TextureIndex(0), FrameTick(0.f)		{}
MonsterEffect::MonsterEffect(CONST GameObject& _RHS)	: GameObject(_RHS),		TextureIndex(0), FrameTick(0.f)		{}
MonsterEffect::~MonsterEffect()																						{}

HRESULT MonsterEffect::Ready_Effect(MONSTER_SKILL _SKILLTYPE, _vec3* _MonsterPOS, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;

	if (_SKILLTYPE == MONSTER_SKILL::SKILL_1) { Make_TextureList(L"Spr_Effect_ExplosionNormal02_"); }
	else if (_SKILLTYPE == MONSTER_SKILL::SKILL_2) { Make_TextureList(L"Spr_Ui_Effect_BossClear_lraCharge_"); }
	else if (_SKILLTYPE == MONSTER_SKILL::SKILL_3) { Make_TextureList(L"Spr_Ui_Stage01_TureMapEffect_"); }

	Component_Transform->Set_Pos(*_MonsterPOS);
	Repeatable = _Repeatable;

	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Camera"));

	_vec3 cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };

	_float angle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&cameraDir, &cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	angle = angle / D3DX_PI * 180.f;

	Component_Transform->Rotation(ROT_X, 90.f - angle);
	PlayTime = _PlayTime;
	//CollisionManager::GetInstance()->Add_ColliderObject(this);

	return S_OK;
}
HRESULT MonsterEffect::Make_TextureList(wstring _FileName) {
	INT FRAME = 0;
	while (++FRAME) {
		wstring FileName = _FileName + to_wstring(FRAME) + L".png";
		IDirect3DBaseTexture9* TEX = ResourceManager::GetInstance()->Find_Texture(FileName.c_str());
		if (TEX == nullptr) break;
		else { TextureList.push_back(TEX); }
	}
	ENDFRAME = TextureList.size() + 1;

	return S_OK;
}
INT  MonsterEffect::Update_GameObject(CONST FLOAT& _DT) {
	if (ObjectDead)	return 0;
	GameObject::Update_GameObject(_DT);

	FrameTick += _DT;

	return 0;
}
VOID MonsterEffect::LateUpdate_GameObject(CONST FLOAT& _DT) {
	if (ObjectDead)	return;
	//_matrix		BillboardMat, WorldMat, ViewMat;
	//
	//WorldMat = *Component_Transform->Get_World();
	//GRPDEV->GetTransform(D3DTS_VIEW, &ViewMat);
	//
	//D3DXMatrixIdentity(&BillboardMat);
	//
	//BillboardMat._11 = ViewMat._11;
	//BillboardMat._13 = ViewMat._13;
	//BillboardMat._31 = ViewMat._31;
	//BillboardMat._33 = ViewMat._33;
	//
	//D3DXMatrixInverse(&BillboardMat, 0, &BillboardMat);
	//
	//WorldMat = BillboardMat * WorldMat;
	//
	//Component_Transform->Set_World(&WorldMat);
	//
	//_vec3		vPos;
	//Component_Transform->Get_Info(INFO_POS, &vPos);
	//
	//AlphaSorting(&vPos);
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

	Component_Collider = ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);			// 충돌체가 오브젝트를 따라 다니도록
	Component_Collider->Set_Scale(0.1f, 0.1f, 0.1f);				// 충돌체의 범위 조절

	Component_Texture = ADD_COMPONENT_TEXTURE;

	return S_OK;
}
MonsterEffect*	MonsterEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, MONSTER_SKILL _SKILLTYPE, _vec3* _MonsterPOS, BOOL _Repeatable, FLOAT _PlayTime) {
	MonsterEffect* EFT = new MonsterEffect(_GRPDEV);
	if (FAILED(EFT->Ready_Effect(_SKILLTYPE, _MonsterPOS, _Repeatable, _PlayTime))) {
		MSG_BOX("Cannot Create Effect.");
		Safe_Release(EFT);
		return nullptr;
	}
	return EFT;
}
VOID MonsterEffect::Free() {
	GameObject::Free();
}