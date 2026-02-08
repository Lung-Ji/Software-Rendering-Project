#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

// UI 오브젝트들의 enum값을 설정, 각각의 분류에 따라 구분 가능케 함.
enum UIType {
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
	HRESULT Ready_UIObject(LPDIRECT3DDEVICE9 _GRPDEV);

	HRESULT			Ready_UIManager(LPDIRECT3DDEVICE9 _GRPDEV);
	INT				Update_UIManager(CONST FLOAT& _DT);
	VOID			LateUpdate_UIManager(CONST FLOAT& _DT);
	VOID			Render_UIManager(LPDIRECT3DDEVICE9 _GRPDEV);

	HRESULT			PathFinder(LPDIRECT3DDEVICE9 _GRPDEV, wstring _MasterFolder);
	HRESULT			Append_Sprite(wstring PATH, UINT WIDTH, UINT HEIGHT);

private:
	ID3DXSprite*							Sprite;
	vector<wstring*>						KEY_Array;
	map<wstring, LPDIRECT3DTEXTURE9>		TextureList;

private:
	
private:
	virtual VOID	Free();
	HRESULT Ready_UIObject(UIManager* _Component_Sprite );
	
public:
	HRESULT		Ready_UI();
	INT				Update_UI();


	VOID			Render_UI(LPDIRECT3DDEVICE9 _GRPDEV, UIType _uitype);

	HRESULT		Import_UISprite(LPDIRECT3DDEVICE9 _GRPDEV, UIType _uitype, CONST TCHAR* _PATH, UINT _WIDTH,
		UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

public:
	static  UIManager* Create(LPDIRECT3DDEVICE9 _GRPDEV,CONST TCHAR* _uiName,
		CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

라이트 출력 중인지 아닌지 판별하는 BOOL 타입 isActive의 게터 / 세터
	BOOL		Get_Active() { return isActive; }
	VOID		Set_Active(BOOL _isActive) { isActive = _isActive; }

private: 
	ID3DXSprite* Sprite;

	// 스프라이트 관련 BOOL 변수
	BOOL		isActive;
	// 벡터 내에서 특정 타입의 UI만 출력해줄 수 있게 하는 벡터 컨테이너
	// UIType에 따른 특정 UI만 출력하게 해놓았음.
	vector<pair<UIType,vector<SpriteINFO>>> vecList;

private:
	virtual VOID Free();

};

END