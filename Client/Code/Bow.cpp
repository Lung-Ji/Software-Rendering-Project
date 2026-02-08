#include "../Include/PCH.h"
#include "Bow.h"

Bow::Bow(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bow::Bow(const GameObject& _RHS) : GameObject(_RHS) {}
Bow::~Bow() {}

HRESULT Bow::Ready_GameObject()
{
	if (FAILED(Component_Initialize())) return E_FAIL;

	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };

	_cameraAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&_cameraDir, &_cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	_cameraAngle = _cameraAngle / D3DX_PI * 180.f;

	Component_Transform->Set_Scale({ 1.f, 1.f, 1.f });
	_type = BowType::IceBow;

	return S_OK;
}

INT Bow::Update_GameObject(const _float& _DT)
{
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	POINT MousePoint{ 0, 0 };
	GetCursorPos(&MousePoint);
	ScreenToClient(hWnd, &MousePoint);

	_vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
	_vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

	_vec2 dir2D = mousePos - screenCenter;
	D3DXVec2Normalize(&dir2D, &dir2D);

	float angle = atan2f(dir2D.y, dir2D.x);

	float radius = 1.5f;

	float offsetX = cosf(angle) * radius;
	float offsetY = sinf(angle) * radius;
	
	Component_Transform->Set_Pos({
		(*_playerPos).x + offsetX,
		(*_playerPos).y + offsetY,
		(*_playerPos).z
		});

	_vec3 eye = { 0.f, 0.f, 0.f };
	_vec3 at = _cameraDir;
	_vec3 up = { 0.f, 1.f, 0.f };

	_matrix matBillboard;
	D3DXMatrixLookAtLH(&matBillboard, &eye, &at, &up);
	D3DXMatrixInverse(&matBillboard, nullptr, &matBillboard);

	float radian = D3DX_PI / 180.f;
	_matrix matRotZ;
	D3DXMatrixRotationZ(&matRotZ, angle - D3DX_PI);

	_matrix matWorld = matRotZ * matBillboard;

	matWorld._41 = (*_playerPos).x + offsetX;
	matWorld._42 = (*_playerPos).y ;
	matWorld._43 = (*_playerPos).z - offsetY;

	// ===============================
	Component_Transform->Set_World(&matWorld);


	//POINT MousePoint{ 0, 0 };
	//GetCursorPos(&MousePoint);
	//ScreenToClient(hWnd, &MousePoint);
	//_vec2 mousePos = { (_float)MousePoint.x, (_float)MousePoint.y };
	//_vec2 playerVec2 = { WINCX / 2 , WINCY / 2 };
	//_vec2 mousedir = mousePos - playerVec2;
	//D3DXVec2Normalize(&mousedir, &mousedir);
	//_vec2 right = { 1.f , 0.f };
	//float angle = atan2f(mousedir.y, mousedir.x);
	//
	//_vec3 camForward = _cameraDir;
	//D3DXVec3Normalize(&camForward, &camForward);
	//
	//_vec3 worldUp = { 0.f, 1.f, 0.f };
	//
	//_vec3 camRight;
	//D3DXVec3Cross(&camRight, &worldUp, &camForward);
	//D3DXVec3Normalize(&camRight, &camRight);
	//
	//_vec3 camUp;
	//D3DXVec3Cross(&camUp, &camForward, &camRight);
	//
	//float radius = 1.f;
	//
	//angle -= D3DX_PI / 180.f * 20.f;
	//_vec3 offset = camRight * cosf(angle) * radius + camUp * sinf(angle) * radius;
	//
	//Component_Transform->Set_Pos({
	//	(*_playerPos).x - offset.x,
	//	(*_playerPos).y - offset.y,
	//	(*_playerPos).z - offset.z
	//	});
	//
	//Component_Transform->Set_Rotation(0, 0, 0);
	//Component_Transform->Rotation(ROT_Z, -angle / D3DX_PI * 180.f);
	//Component_Transform->Rotation(ROT_X, 90.f - _cameraAngle);


	
	//
	//
	//float distance = 1.f;
	//float offsetx = 1 * cosf(angle);
	//float offsety = -1 * sinf(angle);
	//
	//Component_Transform->Set_Pos({ (*_playerPos).x + offsetx, (*_playerPos).y + offsety, (*_playerPos).z });
	//Component_Transform->Set_Rotation(0, 0, 0);
	//Component_Transform->Rotation(ROT_X, 90.f - _cameraAngle);
	//
	//_matrix baseWorld = *Component_Transform->Get_World();
	//
	//_vec3 axis = _cameraDir;
	//
	//_matrix invBase;
	//D3DXMatrixInverse(&invBase, nullptr, &baseWorld);
	//D3DXVec3TransformNormal(&axis, &axis, &invBase);
	//D3DXVec3Normalize(&axis, &axis);
	//
	//_matrix matWorld;
	//D3DXMatrixRotationAxis(&matWorld, &axis, angle);
	//
	//
	//matWorld = matWorld * baseWorld;
	//Component_Transform->Set_World(&matWorld);
	
	// UI
	//{
	//	_vec3 vRotation = *Component_Transform->Get_Rotation();
	//	_vec3 vPos = {};
	//	_float fMin(0.0f), fMax(100);
	//
	//	ImGui::SetNextWindowSize({ 600,600 });
	//
	//	ImGui::Begin("Rot", NULL, ImGuiWindowFlags_MenuBar);
	//	ImGui::Text("Rot2"); //텍스트 
	//	ImGui::SameLine(50.f, 0.f);//텍스트 오른쪽에
	//	ImGui::SliderFloat3("##1", vRotation, fMin, fMax); //scale 출력 ##하면 글자 다음으로 출력됨
	//
	//	ImGui::End();
	//}
	
	return S_OK;
}

VOID Bow::LateUpdate_GameObject(const _float& _DT)
{
	GameObject::LateUpdate_GameObject(_DT);
}

VOID Bow::Render_GameObject()
{
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	SetGrahpic();

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return VOID();
}

HRESULT Bow::Component_Initialize()
{
	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture = ADD_COMPONENT_TEXTURE;
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Weapon/IceBow");
	return S_OK;
}

void Bow::SetGrahpic()
{
	TCHAR FileName[128] = L"";

	switch (_type) {
	case BowType::IceBow:
		wsprintfW(FileName, L"IceBow_Top.png");
		break;

	default:
		wsprintfW(FileName, L"IceBow_Top.png");
		break;
	}

	Component_Texture->Set_Texture(FileName);
}

Bow* Bow::Create(LPDIRECT3DDEVICE9 _GRPDEV)
{
	Bow* BOW = new Bow(_GRPDEV);
	if (FAILED(BOW->Ready_GameObject())) {
		MSG_BOX("Cannot Create BOW.");
		Safe_Release(BOW);
		return nullptr;
	}
	return BOW;
}

VOID Bow::Free()
{
	GameObject::Free();
}
