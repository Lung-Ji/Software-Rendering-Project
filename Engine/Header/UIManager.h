#pragma once

#include "Component.h"
#include "GameObject.h"
#include "UISprite.h"

BEGIN(Engine)

// UI 오브젝트들의 enum값을 설정, 각각의 분류에 따라 구분 가능케 함.
enum UIType {
	Inventory,
	Object,
	Settings
};

class ENGINE_DLL UIManager : public Component {
	DECLARE_SINGLETON(UIManager)

private:
	explicit UIManager();
	virtual ~UIManager();

public:
	HRESULT Ready_UIObject(UIManager* _Component_Sprite );
	
public:
	HRESULT		Ready_UI();
	INT				Update_UI();
	// 스프라이트 출력 함수
	VOID			Render_UI(UIType _uitype, CONST TCHAR* _UINAME);

	// 스프라이트 추가 함수
	HRESULT		Import_UISprite(UIType _uitype, CONST TCHAR* _PATH, UINT _WIDTH,
		UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

public:
	static  UIManager* Create(LPDIRECT3DDEVICE9 _GRPDEV,CONST TCHAR* _uiName,CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

	// 스프라이트 출력 중인지 아닌지 판별하는 BOOL 타입 isActive의 게터 / 세터
	BOOL		Get_Active() { return isActive; }
	VOID		Set_Active(BOOL _isActive) { isActive = _isActive; }

private: 
	ID3DXSprite* Sprite;

	// 스프라이트 관련 BOOL 변수
	BOOL		isActive;
	//map<UIType, map<CONST _tchar*, SpriteINFO>> UIList;
	//map<const _tchar*,SpriteINFO>UIList;
	vector<pair<UIType,vector<SpriteINFO>>> vecList;
private:
	virtual VOID Free();

};

END