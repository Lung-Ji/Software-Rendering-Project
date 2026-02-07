#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL ResourceManager : public Base {
	DECLARE_SINGLETON(ResourceManager)
private:
	explicit ResourceManager();
	virtual ~ResourceManager();
public:
	HRESULT					GlobalImport_Texture(IDirect3DDevice9* _GRPDEV, wstring _MasterFolder);
	HRESULT					PathFinder(IDirect3DDevice9* _GRPDEV, wstring _MasterFolder);

	IDirect3DBaseTexture9* Find_Texture(const TCHAR* _FileName);

private:
	map<CONST TCHAR*, IDirect3DBaseTexture9*>	TextureList;
	vector<wstring*>							KEY_Array;
public:
	virtual			VOID	Free();
};

END