#include "../Include/PCH.h"
#include "PlayerEffect.h"

PlayerEffect:: PlayerEffect(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV), TextureIndex(0), FrameTick(0.f){}
PlayerEffect:: PlayerEffect(CONST GameObject& _RHS)		: GameObject(_RHS), TextureIndex(0), FrameTick(0.f) {}
PlayerEffect::~PlayerEffect(){}

HRESULT PlayerEffect::Ready_Effect(PLAYER_SKILL _SKILLTYPE, _vec3* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;

	if		(_SKILLTYPE == PLAYER_SKILL::SKILL_1)	{ Make_TextureList(L"Spr_Effect_ExplosionNormal02_");		}
	else if (_SKILLTYPE == PLAYER_SKILL::SKILL_2)	{ Make_TextureList(L"Spr_Ui_Effect_BossClear_lraCharge_");	}
	else if (_SKILLTYPE == PLAYER_SKILL::SKILL_3)	{ Make_TextureList(L"Spr_Ui_Stage01_TureMapEffect_");		}

	Component_Transform->Set_Pos(*_PlayerPOS);		// 기본 위치 : 플레이어 중심 
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

HRESULT PlayerEffect::Make_TextureList(wstring _FileName) {
	INT FRAME = 0;
	while (++FRAME){
		wstring FileName = _FileName + to_wstring(FRAME) + L".png";
		IDirect3DBaseTexture9* TEX = ResourceManager::GetInstance()->Find_Texture(FileName.c_str());
		if (TEX == nullptr) break;
		else { TextureList.push_back(TEX); }
	}

	ENDFRAME = TextureList.size() + 1;

	return S_OK;
}

INT  PlayerEffect::Update_GameObject(CONST FLOAT& _DT) {
	if (ObjectDead)	return 0;
	GameObject::Update_GameObject(_DT);
	 
	FrameTick += _DT;

	return 0;
}
VOID PlayerEffect::LateUpdate_GameObject(CONST FLOAT& _DT) {
	if (ObjectDead)	return ;
	if (FrameTick > PlayTime / ENDFRAME) {
		if (TextureIndex++ >= ENDFRAME - 2) {	
			if (Repeatable) { TextureIndex = 0;}
			else {
				TextureIndex = ENDFRAME - 2; 
				ObjectDead = TRUE;
			}
		}
		FrameTick = 0.f;
	}
}
VOID PlayerEffect::Render_GameObject() {
	if (ObjectDead)	return;
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, TextureList[TextureIndex]);
	
	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
BOOL PlayerEffect::OnCollisionEnter(GameObject* _Other) {
	return TRUE;
}
BOOL PlayerEffect::OnCollisionStay(GameObject* _Other) {
	return TRUE;
}
BOOL PlayerEffect::OnCollisionExit(GameObject* _Other) {
	return TRUE;
}
HRESULT	PlayerEffect::Component_Initialize() {
	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Collider	= ADD_COMPONENT_COLLIDER;
	Component_Collider->Set_CenterPos(Component_Transform);			// 충돌체가 오브젝트를 따라 다니도록
	Component_Collider->Set_Scale(0.1f, 0.1f, 0.1f);				// 충돌체의 범위 조절

	Component_Texture	= ADD_COMPONENT_TEXTURE;

	return S_OK;
}
PlayerEffect* PlayerEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, PLAYER_SKILL _SKILLTYPE, _vec3* _PlayerPOS, BOOL _Repeatable, FLOAT _PlayTime) {
	PlayerEffect* EFT = new PlayerEffect(_GRPDEV);
	if (FAILED(EFT->Ready_Effect(_SKILLTYPE, _PlayerPOS, _Repeatable, _PlayTime))) {
		MSG_BOX("Cannot Create Effect.");
		Safe_Release(EFT);
		return nullptr;
	}
	return EFT;
}
VOID PlayerEffect::Free() {
	GameObject::Free();
}