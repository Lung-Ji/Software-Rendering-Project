#include "Arrow.h"

Arrow::~Arrow()
{
}

HRESULT Arrow::Ready_GameObject()
{
    return E_NOTIMPL;
}

INT Arrow::Update_GameObject(const _float& _DT)
{
    return 0;
}

VOID Arrow::LateUpdate_GameObject(const _float& _DT)
{
    return VOID();
}

VOID Arrow::Render_GameObject()
{
    return VOID();
}

HRESULT Arrow::Component_Initialize()
{
    return E_NOTIMPL;
}

void Arrow::SetGrahpic()
{
}

Arrow* Arrow::Create(LPDIRECT3DDEVICE9 _GRPDEV)
{
    return nullptr;
}

VOID Arrow::Free()
{
    return VOID();
}
