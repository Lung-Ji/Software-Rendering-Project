#include "../Include/PCH.h"
#include "Arrow.h"

Arrow::Arrow(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Arrow::Arrow(const GameObject& _RHS) : GameObject(_RHS) {}
Arrow::~Arrow() {}

HRESULT Arrow::Ready_GameObject(ArrowType _ARROWTYPE, _vec3* _PlayerPOS)
{
    if (FAILED(Component_Initialize())) return E_FAIL;

    _type = ArrowType::IceArrow_LV1;
    _speed = 15.f;
    _sumSpeed = 0.f;
    _lifeTime = 0.f;
    _frame = 1;

    _playerPos = { _PlayerPOS->x, _PlayerPOS->y, _PlayerPOS->z };

    POINT MousePoint{ 0, 0 };
    GetCursorPos(&MousePoint);
    ScreenToClient(hWnd, &MousePoint);

    _vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
    _vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

    _vec2 dir2D = mousePos - screenCenter;
    D3DXVec2Normalize(&dir2D, &dir2D);

    _angle = atan2f(dir2D.y, dir2D.x);

    return S_OK;
}

INT Arrow::Update_GameObject(const _float& _DT)
{
    GameObject::Update_GameObject(_DT);
    RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

    _vec3		upDir, rightDir;
    upDir = { 0.f, 0.f, 1.f };
    rightDir = { 1.f, 0.f, 0.f };

    _lifeTime += _DT;

    if (_lifeTime > 0.5f)
        return -1;

    {
        CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Camera"));
        _vec3 cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
        D3DXVec3Normalize(&cameraDir, &cameraDir);

        _vec3 eye = { 0.f, 0.f, 0.f };
        _vec3 at = cameraDir;
        _vec3 up = { 0.f, 1.f, 0.f };

        _matrix matSize;
        D3DXMatrixIdentity(&matSize);
        D3DXMatrixScaling(&matSize, 1.f, 1.f, 1.f);

        _matrix matBillboard;
        D3DXMatrixLookAtLH(&matBillboard, &eye, &at, &up);
        D3DXMatrixInverse(&matBillboard, nullptr, &matBillboard);

        _matrix matRotZ;
        D3DXMatrixRotationZ(&matRotZ, _angle);

        _matrix matWorld = matSize * matRotZ * matBillboard;

        _sumSpeed += _DT * _speed;
        matWorld._41 = _playerPos.x + _sumSpeed * cosf(_angle);
        matWorld._42 = _playerPos.y;
        matWorld._43 = _playerPos.z - _sumSpeed * sinf(_angle);

        Component_Transform->Set_World(&matWorld);
    }

    return S_OK;
}

VOID Arrow::LateUpdate_GameObject(const _float& _DT)
{
    GameObject::LateUpdate_GameObject(_DT);
}

VOID Arrow::Render_GameObject()
{
    GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

    SetGrahpic();

    Component_Buffer->Render_Buffer();

    GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    return VOID();
}

HRESULT Arrow::Component_Initialize()
{
    Component_Buffer = ADD_COMPONENT_RECTTEX;
    Component_Transform = ADD_COMPONENT_TRANSFORM;
    Component_Texture = ADD_COMPONENT_TEXTURE;

    return S_OK;
}

void Arrow::SetGrahpic()
{
    TCHAR FileName[128] = L"";

    switch (_type) {
    case ArrowType::IceArrow_LV1:
        if (_frame > 6) _frame = 1;
        wsprintfW(FileName, L"IceArrow_LV1_%d.png", _frame++);
        break;
    case ArrowType::IceArrow_LV2:
        if (_frame > 6) _frame = 1;
        wsprintfW(FileName, L"IceArrow_%d.png", _frame++);
        break;
    default:
        if (_frame > 6) _frame = 1;
        wsprintfW(FileName, L"IceArrow_LV1_%d.png", _frame++);
        break;
    }
    
    GRPDEV->SetTexture(0, (ResourceManager::GetInstance()->Find_Texture(FileName)));
}

Arrow* Arrow::Create(LPDIRECT3DDEVICE9 _GRPDEV, ArrowType _ARROWTYPE, _vec3* _PlayerPOS)
{
    Arrow* arrow = new Arrow(_GRPDEV);
    if (FAILED(arrow->Ready_GameObject(_ARROWTYPE, _PlayerPOS))) {
        MSG_BOX("Cannot Create arrow.");
        Safe_Release(arrow);
        return nullptr;
    }
    return arrow;
}

VOID Arrow::Free()
{
    GameObject::Free();
}
