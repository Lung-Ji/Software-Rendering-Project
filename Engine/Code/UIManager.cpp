#include "UIManager.h"

IMPLEMENT_SINGLETON(UIManager)

HRESULT UIManager::Ready_UIObject(SpriteObject* _Sprite)
{
  return S_OK;
}

VOID UIManager::Show_UI(SpriteObject* _Sprite)
{
}

VOID UIManager::Hide_UI(SpriteObject* _Sprite)
{
}


VOID UIManager::Free() 
{
}
