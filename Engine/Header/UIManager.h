#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL UIManager : public Base {
	DECLARE_SINGLETON(UIManager)
private:
	explicit UIManager();
	virtual ~UIManager();

public:
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
};

END