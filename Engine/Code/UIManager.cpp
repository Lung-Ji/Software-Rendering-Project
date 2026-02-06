#include "UIManager.h"

UIManager::UIManager() : Sprite(nullptr), isActive(true) {}
UIManager::~UIManager() {}

HRESULT UIManager::Ready_UIObject(UIManager* _Sprite)
{
  return S_OK;
}

UIManager* UIManager::Find_Sprite(const _tchar* pSpriteTag)
{
  auto	iter = find_if(UIList.begin(), UIList.end(), CTag_Finder(pSpriteTag));

  if (iter == UIList.end())
    return nullptr;

}

UISprite* UIManager::Set_UIType(UIType _type)
{

  return nullptr;
}

VOID UIManager::Show_UI(UIManager* _Sprite)
{
}

VOID UIManager::Hide_UI(UIManager* _Sprite)
{

}
VOID UIManager::Render_UI(CONST _tchar* _UINAME) {
  
  
}

HRESULT UIManager::Ready_UI()
{
  return E_NOTIMPL;
}
INT UIManager::Update_UI() {
  return 0;
}

HRESULT UIManager::Import_UISprite(const _tchar* _UINAME ,const TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY)
{
  UIList.insert({ _UINAME,SpriteINFO(_PATH,_WIDTH,_HEIGHT, _POSX, _POSY, _VIS, _OPACITY) });

  return S_OK;
}

VOID UIManager::Free()
{
  for_each(UIList.begin(), UIList.end(), CDeleteMap());
  UIList.clear();
}