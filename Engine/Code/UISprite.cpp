#include "UISprite.h"

UISprite::UISprite()
{
}

UISprite::~UISprite()
{
}

UISprite* UISprite::Create(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY)
{
  UISprite* US = new UISprite();
  if (FAILED(US->Ready_UI(_PATH, _WIDTH, _HEIGHT, _POSX, _POSY, _VIS, _OPACITY)))
  {
    MSG_BOX("Cannot Create Sprite.");
    Safe_Release(US);
    return nullptr;
  }
  return US;
}

HRESULT	UISprite::Ready_UI(CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY) {

  IDirect3DBaseTexture9* pTexture = nullptr;

  if (FAILED(D3DXCreateTextureFromFileExW(GRPDEV, _PATH, _WIDTH, _HEIGHT, 1, 0, D3DFMT_A8B8G8R8,
    D3DPOOL_MANAGED, D3DX_DEFAULT, 0, NULL, NULL, NULL, (LPDIRECT3DTEXTURE9*)pTexture)))
  {
    MSG_BOX("Cannot Create Texture");
    Safe_Release(pTexture);
    return E_FAIL;
  }
  return S_OK;
}

INT UISprite::Update_Sprite() {
  return 0;
}

VOID UISprite::Render_Sprite() {
  GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
  Sprite->Begin(D3DXSPRITE_ALPHABLEND);

  Sprite->End();
  GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

Component* UISprite::Clone() {
  return new UISprite(*this);
}

VOID UISprite::Free()
{
  Safe_Release(GRPDEV);
}