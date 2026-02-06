#pragma once

#include "Component.h"
#include "UISprite.h"

BEGIN(Engine)

enum class UIType {
	Inventory,
	Object,
	Settings
};

class ENGINE_DLL UIManager : public Base {
	DECLARE_SINGLETON(UIManager)

private:
	explicit UIManager();
	virtual ~UIManager();

public:
	HRESULT Ready_UIObject(UIManager* _Component_Sprite );
	UISprite* Find_Sprite(const _tchar* pSpriteTag);

	UISprite* Set_UIType(UIType _type);

	VOID  Show_UI(UIManager* _Sprite);
	VOID	Hide_UI(UIManager* _Sprite);

public:
	HRESULT		Ready_UI();
	INT				Update_UI();
	VOID			Render_UI(CONST _tchar* _UINAME);

	HRESULT		Import_UISprite(const _tchar* _UINAME, CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY = 255);

public:
	static  UIManager* Create(LPDIRECT3DDEVICE9 _GRPDEV,CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

private:
	virtual VOID	Free();
	BOOL		isActive;

private:
	ID3DXSprite* Sprite;
	map<const _tchar*, SpriteINFO> UIList;
private:
	virtual VOID Free();

};

END