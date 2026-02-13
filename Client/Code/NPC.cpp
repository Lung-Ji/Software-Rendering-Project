#include "../Include/PCH.h"
#include "NPC.h"

NPC::NPC(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)	{}
NPC::NPC(const GameObject& _RHS)	: GameObject(_RHS)		{}
NPC::~NPC()													{}

HRESULT NPC::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	Timer_Tif = 0.f;
	Tif_AnimIDX = 1;

	Interaction_Possible = FALSE;

	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_vec3 cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };

	_float angle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&cameraDir, &cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	_float _cameraAngle = angle / D3DX_PI * 180.f;

	Component_Transform->Rotation(ROT_X, 90.f - _cameraAngle);
	return S_OK;
}
INT	NPC::Update_GameObject(const _float& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	TalkWithNPC(_DT);

	return 0;
}
VOID NPC::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
	if (Timer_Tif > 0.2f) {
		Tif_AnimIDX = Tif_AnimIDX % 7 + 1;
		Timer_Tif = 0.f;
	}
}
VOID NPC::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	GRPDEV->SetTexture(0, Tif_TextureList[Tif_AnimIDX]);

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT NPC::Component_Initialize() {

	Component_Buffer	= ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture	= ADD_COMPONENT_TEXTURE;
	Component_Collider	= ADD_COMPONENT_COLLIDER;

	for (INT PIC = 1; PIC <= 8; ++PIC) {
		wstring Base = L"Tif_Stand" + to_wstring(PIC) + L".png";
		Tif_TextureList.push_back(ResourceManager::GetInstance()->Find_Texture(Base.c_str()));
	}
	
	Component_Collider->Set_CenterPos(Component_Transform);
	Component_Collider->Set_Scale(1.f, 1.f, 1.f);

	Component_Transform->Set_Pos(5.f, 1.f, 5.f);
	Component_Transform->Set_Scale(0.6f, 1.2f, 1.f);

	return S_OK;
}
NPC* NPC::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	NPC* NPN = new NPC(_GRPDEV);
	if (FAILED(NPN->Ready_GameObject())) {
		MSG_BOX("Cannot Create NPC.");
		Safe_Release(NPN);
		return nullptr;
	}
	return NPN;
}
VOID NPC::Free() {
	GameObject::Free();
}

BOOL NPC::OnCollisionEnter(GameObject* _Other) {
	PlayerUI = dynamic_cast<MainUI*>(SceneManager::GetInstance()->Get_GameObject(L"MainUI"));
	NPCTalkUI = dynamic_cast<NPCTalk*>(SceneManager::GetInstance()->Get_GameObject(L"NPCTalk"));

	if (_Other->Get_ObjectTag() == L"Player") {
		
		PlayerUI->PopUp_Interaction_Notice(L"대화 - 티프", TRUE);
		
		return TRUE;
	}
	return FALSE;
}
BOOL NPC::OnCollisionStay(GameObject* _Other) {
	if (KEY_DOWN(DIK_E)) 
		Interaction_Possible = TRUE;
	
	return FALSE;
}
BOOL NPC::OnCollisionExit(GameObject* _Other) {
	if (_Other->Get_ObjectTag() == L"Player") {
		PlayerUI->PopUp_Interaction_Notice(L"", FALSE);
		return TRUE;
	}
	return FALSE;
}

VOID NPC::TalkWithNPC(FLOAT _DT) {
	if (Interaction_Possible) {
		if (ObjectTAG == L"NPC_Tif") 
			if (NPCTalkUI->Activate_NPCTalk(NPC_CHARACTER::NPC_TIF, _DT) == TRUE) {
				Interaction_Possible = FALSE;
			}
		if (ObjectTAG == L"NPC_Shop")
			if(NPCTalkUI->Activate_NPCTalk(NPC_CHARACTER::NPC_SHOP, _DT) == TRUE) {
				Interaction_Possible = FALSE;
			}
	}
}
