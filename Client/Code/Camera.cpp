#include "../Include/PCH.h"
#include "Camera.h"

CameraObject::CameraObject(LPDIRECT3DDEVICE9 _GRPDEV)	: GameObject(_GRPDEV)	{}
CameraObject::CameraObject(const GameObject& _RHS)		: GameObject(_RHS)		{}
CameraObject::~CameraObject() {}

HRESULT CameraObject::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	EyeVec = { 0.f,10.f,0.f };		AtVec = { 1.f,8.f,1.f };				UpVec = { 0.f,1.f,0.f };
	FOVValue = D3DXToRadian(60.f);	AspectValue = (_float)WINCX / WINCY;	NearValue = 0.1f; FarValue = 1000.f;

	Angle = { 0.f, 0.f, 0.f };		CameraSpeed = 10.f;

	MouseCheck = FALSE;

	Camera_Show = TRUE;
	Camera_Move = FALSE;

	D3DXMatrixLookAtLH(&ViewMatrix, &EyeVec, &AtVec, &UpVec);
	D3DXMatrixPerspectiveFovLH(&ProjMatrix, FOVValue, AspectValue, NearValue, FarValue);

	GRPDEV->SetTransform(D3DTS_VIEW, &ViewMatrix);
	GRPDEV->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	return S_OK;
}
INT	CameraObject::Update_GameObject(const _float& _DT) {

	if (!Camera_Move)
	{
		GameObject* player = dynamic_cast<GameObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
			Get_GameObject(L"Player"));

		_vec3* playerPos = (dynamic_cast<Transform*>(player->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM)))->Get_Position();

		_vec3 eyeCalc = { -5.f, 9.f, -5.f };
		_vec3 atCalc = { -4.f, 7.f, -4.f };

		EyeVec = (*playerPos) + eyeCalc;
		AtVec = (*playerPos) + atCalc;
	}

	D3DXMatrixLookAtLH(&ViewMatrix, &EyeVec, &AtVec, &UpVec);

	GRPDEV->SetTransform(D3DTS_VIEW, &ViewMatrix);
	return 0;
}
VOID CameraObject::LateUpdate_GameObject(const _float& _DT) {
	Camera_Transform_Control(_DT);
	if (MouseCheck) {
		POINT       ptMouse{ WINCX >> 1, WINCY >> 1 };

		ClientToScreen(hWnd, &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);

		Camera_Rotation_Control(_DT);
	}
}

VOID CameraObject::Camera_Transform_Control(CONST FLOAT& _DT) {

	_matrix CameraMatrix;
	_vec3	SideVector, FrontVector, UpVector;

	D3DXMatrixInverse(&CameraMatrix, 0, &ViewMatrix);

	if (Camera_Move)
	{
		if (KEY_HOLD(DIK_W)) {
			memcpy(&FrontVector, &CameraMatrix.m[2][0], sizeof(_vec3));

			_vec3 Length = *D3DXVec3Normalize(&FrontVector, &FrontVector) * _DT * CameraSpeed;
			EyeVec += Length; AtVec += Length;
		}
		if (KEY_HOLD(DIK_S)) {
			memcpy(&FrontVector, &CameraMatrix.m[2][0], sizeof(_vec3));

			_vec3 Length = *D3DXVec3Normalize(&FrontVector, &FrontVector) * _DT * CameraSpeed;
			EyeVec -= Length; AtVec -= Length;
		}
		if (KEY_HOLD(DIK_D)) {
			memcpy(&SideVector, &CameraMatrix.m[0][0], sizeof(_vec3));

			_vec3 Length = *D3DXVec3Normalize(&SideVector, &SideVector) * _DT * CameraSpeed;
			EyeVec += Length; AtVec += Length;
		}
		if (KEY_HOLD(DIK_A)) {
			memcpy(&SideVector, &CameraMatrix.m[0][0], sizeof(_vec3));

			_vec3 Length = *D3DXVec3Normalize(&SideVector, &SideVector) * _DT * CameraSpeed;
			EyeVec -= Length; AtVec -= Length;
		}
		if (KEY_HOLD(DIK_SPACE)) {
			memcpy(&UpVector, &CameraMatrix.m[1][0], sizeof(_vec3));

			_vec3 Length = *D3DXVec3Normalize(&UpVector, &UpVector) * _DT * CameraSpeed;
			EyeVec += Length; AtVec += Length;
		}
		if (KEY_HOLD(DIK_LCONTROL)) {
			memcpy(&UpVector, &CameraMatrix.m[1][0], sizeof(_vec3));

			_vec3 Length = *D3DXVec3Normalize(&UpVector, &UpVector) * _DT * CameraSpeed;
			EyeVec -= Length; AtVec -= Length;
		}
		if (KEY_DOWN(DIK_F1)) {		//	GUI 상태 바 숨김 여부 TRUE = Visible, FALSE = Hide
			Camera_Show ? Camera_Show = FALSE : Camera_Show = TRUE;
		}
	}

	if (KEY_DOWN(DIK_P)) {	//	마우스 커서 고정 여부 TRUE = 고정, FALSE = 고정 해제
		MouseCheck ? MouseCheck = FALSE : MouseCheck = TRUE;
		Camera_Move ? Camera_Move = FALSE : Camera_Move = TRUE;
	}
}
VOID CameraObject::Camera_Rotation_Control(CONST FLOAT& _DT){
	_matrix CameraMatrix;
	D3DXMatrixInverse(&CameraMatrix, 0, &ViewMatrix);

	LONG MouesAngle = 0;

	if (Camera_Move)
	{
		if (MouesAngle = MOUSE_MOVE(DIMS_Y)) {
			_matrix RotationMat;
			memcpy(&RightVec, &CameraMatrix.m[0][0], sizeof(_vec3));

			LookVec = AtVec - EyeVec;

			D3DXMatrixRotationAxis(&RotationMat, &RightVec, D3DXToRadian(MouesAngle / 10.f));

			D3DXVec3TransformNormal(&LookVec, &LookVec, &RotationMat);

			AtVec = EyeVec + LookVec;
		}
		if (MouesAngle = MOUSE_MOVE(DIMS_X)) {
			_matrix RotationMat;

			LookVec = AtVec - EyeVec;

			D3DXMatrixRotationAxis(&RotationMat, &UpVec, D3DXToRadian(MouesAngle / 10.f));

			D3DXVec3TransformNormal(&LookVec, &LookVec, &RotationMat);

			AtVec = EyeVec + LookVec;
		}
	}
}

HRESULT CameraObject::Component_Initialize() {

	//Component_Transform = ADD_COMPONENT_TRANSFORM;

	return S_OK;
}
CameraObject* CameraObject::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	CameraObject* CAM = new CameraObject(_GRPDEV);
	if (FAILED(CAM->Ready_GameObject())) {
		MSG_BOX("Cannot Create Camera.");
		Safe_Release(CAM);
		return nullptr;
	}
	return CAM;
}
VOID CameraObject::Free() {
	GameObject::Free();
}