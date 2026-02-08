#pragma once
#include "Component.h"
#include "Sprite.h"

BEGIN(Engine)
class UISprite :  public Component
{
private:
  explicit UISprite();
	explicit UISprite(LPDIRECT3DDEVICE9 _GRPDEV);
  virtual ~UISprite();

public:
	HRESULT	Ready_UI(CONST TCHAR* _PATH, CONST TCHAR* _KEY, UINT _WIDTH, UINT _HEIGHT,
		FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);
	INT			Update_Sprite();
	VOID		Render_Sprite();

public:
  static  UISprite* Create(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _PATH, CONST TCHAR* _KEY, UINT _WIDTH, UINT _HEIGHT,
	  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

  virtual Component* Clone();

	BOOL		Get_Visible()								 { return m_Visible; }
	VOID		Set_Visible(BOOL _isVisible) { m_Visible = _isVisible; }
	
private:
  ID3DXSprite* Sprite;
	BOOL				m_Visible;
	SpriteObject* c_Sprite;

private:
	virtual VOID Free();
};

END