#pragma once
#include "GameObject.h"

class CButton :  public GameObject
{
private:
  explicit CButton(LPDIRECT3DDEVICE9 _GRPDEV);
  explicit CButton(const GameObject& ths);
  virtual ~CButton();

public:

  virtual			HRESULT		Ready_GameObject();
  virtual			INT			Update_GameObject(CONST FLOAT& _DT);
  virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
  virtual			VOID		Render_GameObject();

private:
  HRESULT			Component_Initialize();

private:
  Buffer* m_pBuffer;
  Transform* m_pTransform;
  SpriteObject* Component_Sprite;
  SpriteObject* Component_Sprite2;
  
  BOOL        m_bCheckMouse;

public:
  static      CButton* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
  virtual void            Free();

};


