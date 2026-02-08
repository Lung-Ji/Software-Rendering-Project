#include "UIManager.h"

IMPLEMENT_SINGLETON(UIManager)

UIManager::UIManager() : Sprite(nullptr), isActive(false) {}
UIManager::~UIManager() {}

HRESULT UIManager::Ready_UIObject(LPDIRECT3DDEVICE9 _GRPDEV)
{
  D3DXCreateSprite(_GRPDEV , &Sprite);
  return S_OK;
}

UIManager* UIManager::Create(LPDIRECT3DDEVICE9 _GRPDEV,CONST TCHAR* _uiName,CONST TCHAR* _PATH, UINT _WIDTH, 
  UINT _HEIGHT,  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY)
{
  
  return 0;
} 

HRESULT UIManager::Import_UISprite(LPDIRECT3DDEVICE9 _GRPDEV, UIType _uitype, CONST TCHAR* _PATH, UINT _WIDTH,
  UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY)
{
  vecList.push_back({ _uitype, {SpriteINFO(_PATH,_WIDTH,_HEIGHT,_POSX,_POSY,_VIS,_OPACITY)} });

  D3DXCreateTextureFromFileExW(_GRPDEV,
    vecList.back().second.back().PATH.c_str(),
    vecList.back().second.back().WIDTH,
    vecList.back().second.back().HEIGHT,
    1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
    (LPDIRECT3DTEXTURE9*)&vecList.back().second.back().TEXTURE);

  return S_OK;
}

VOID UIManager::Render_UI(LPDIRECT3DDEVICE9 _GRPDEV, UIType _uitype)
{
  _GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
  Sprite->Begin(D3DXSPRITE_ALPHABLEND);
  if(!isActive)
  {
    for (auto& pair : vecList)
    {
      if (pair.first == _uitype)
      {
        for (auto& sprite : pair.second)
          Sprite->Draw(sprite.TEXTURE, NULL, NULL, &sprite.POS, D3DCOLOR_ARGB(sprite.OPACITY, 255, 255, 255));
      }
      else
      {
        MSG_BOX("Not exist UIType");
      }
    }
  }
  Sprite->End();
  _GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT UIManager::Ready_UI()
{
  return E_NOTIMPL;
}
INT UIManager::Update_UI() {
  return 0;
}
VOID UIManager::Free()
{
}