#include "../Include/PCH.h"
#include "Effect.h"

Effect:: Effect(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV), TextureIndex(0), FrameTick(0.f){}
Effect:: Effect(CONST GameObject& _RHS)		: GameObject(_RHS), TextureIndex(0), FrameTick(0.f) {}
Effect::~Effect(){}

HRESULT Effect::Ready_Effect(PLAYER_SKILL _SKILLTYPE, Transform* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;

	if (_SKILLTYPE == PLAYER_SKILL::SKILL_1) {
		ENDFRAME = 21;			// 이펙트 파일 개수 + 1 ~ 이펙트 변경하시려면 파일개수 체크하기
		for (INT FRAME = 1; FRAME < ENDFRAME; ++FRAME) {
			wstring FileName = L"Spr_Effect_ExplosionNormal02_" + to_wstring(FRAME) + L".png";
			TextureList.push_back(ResourceManager::GetInstance()->Find_Texture(FileName.c_str()));
		}
		Component_Transform->Set_Pos(*_PlayerPOS->Get_Position());
		Repeatable = _Repeatable;
	}
	if (_SKILLTYPE == PLAYER_SKILL::SKILL_2) {
		ENDFRAME = 24;			// 이펙트 파일 개수 + 1 ~ 이펙트 변경하시려면 파일개수 체크하기
		for (INT FRAME = 1; FRAME < ENDFRAME; ++FRAME) {
				wstring FileName = L"Spr_Ui_Effect_BossClear_lraCharge_" + to_wstring(FRAME) + L".png";
				TextureList.push_back(ResourceManager::GetInstance()->Find_Texture(FileName.c_str()));
		}
		Component_Transform->Set_Pos(*_PlayerPOS->Get_Position());
		Repeatable = _Repeatable;
	}
	if (_SKILLTYPE == PLAYER_SKILL::SKILL_3) {
		ENDFRAME = 33;			// 이펙트 파일 개수 + 1 ~ 이펙트 변경하시려면 파일개수 체크하기
		for (INT FRAME = 1; FRAME < ENDFRAME; ++FRAME) {
			wstring FileName = L"Spr_Ui_Stage01_TureMapEffect_" + to_wstring(FRAME) + L".png";
			TextureList.push_back(ResourceManager::GetInstance()->Find_Texture(FileName.c_str()));
		}
		Component_Transform->Set_Pos(*_PlayerPOS->Get_Position());
		Repeatable = _Repeatable;
	}
	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_vec3 cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };

	_float angle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&cameraDir, &cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	angle = angle / D3DX_PI * 180.f;

	Component_Transform->Rotation(ROT_X, 90.f - angle);

	Sustainablility = TRUE;
	PlayTime = _PlayTime;

	return S_OK;
}
INT  Effect::Update_GameObject(CONST FLOAT& _DT) {
	if (!Sustainablility)	return 0;
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_EFFECT, this);

	FrameTick += _DT;

	return 0;
}
VOID Effect::LateUpdate_GameObject(CONST FLOAT& _DT) {
	if (!Sustainablility)	return ;
	_matrix		BillboardMat, WorldMat, ViewMat;

	WorldMat = *Component_Transform->Get_World();
	GRPDEV->GetTransform(D3DTS_VIEW, &ViewMat);

	D3DXMatrixIdentity(&BillboardMat);

	// y축 회전만 제거
	BillboardMat._11 = ViewMat._11;
	BillboardMat._13 = ViewMat._13;
	BillboardMat._31 = ViewMat._31;
	BillboardMat._33 = ViewMat._33;

	D3DXMatrixInverse(&BillboardMat, 0, &BillboardMat);

	// 주의 할 것
	WorldMat = BillboardMat * WorldMat;

	Component_Transform->Set_World(&WorldMat);

	_vec3		vPos;
	Component_Transform->Get_Info(INFO_POS, &vPos);

	AlphaSorting(&vPos);
	if (FrameTick > PlayTime / ENDFRAME) {
		if (TextureIndex++ >= ENDFRAME - 2) {	
			if (Repeatable) { TextureIndex = 0;}
			else { TextureIndex = ENDFRAME - 2; Sustainablility = FALSE; }
		}
		FrameTick = 0.f;
	}
}
VOID Effect::Render_GameObject() {
	if (!Sustainablility)	return;
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, TextureList[TextureIndex]);
	
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
BOOL Effect::OnCollisionEnter(GameObject* _Other) {
	return TRUE;
}	 
BOOL Effect::OnCollisionStay(GameObject* _Other) {
	return TRUE;
}	 
BOOL Effect::OnCollisionExit(GameObject* _Other) {
	return TRUE;
}
HRESULT	Effect::Component_Initialize() {
	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	//Component_Collider	= ADD_COMPONENT_COLLIDER;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;

	return S_OK;
}
Effect* Effect::Create(LPDIRECT3DDEVICE9 _GRPDEV, PLAYER_SKILL _SKILLTYPE, Transform* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime) {
	Effect* EFT = new Effect(_GRPDEV);
	if (FAILED(EFT->Ready_Effect(_SKILLTYPE, _PlayerPOS, _Repeatable, _PlayTime))) {
		MSG_BOX("Cannot Create Effect.");
		Safe_Release(EFT);
		return nullptr;
	}
	return EFT;
}
VOID Effect::Free() {
	GameObject::Free();
}