#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Texture : public Component {
private:
	explicit Texture();
	explicit Texture(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Texture(CONST Texture& _RHS);
	virtual ~Texture();

public:
	HRESULT		Ready_Texture(TEXTUREID _TID, CONST TCHAR* _PATH, CONST UINT& _COUNT);
	VOID		Set_Texture(CONST TCHAR* _FileName);
	IDirect3DTexture9* Find_Texture(CONST TCHAR* _FileName);

	HRESULT		Import_TextureFromFolder(wstring _FolderName);
private:
	map<CONST TCHAR*, IDirect3DTexture9*>	TextureList;
	vector<wstring*> KEY_Array;
public:
	static		Texture*	Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component*	Clone();

private:
	virtual		VOID		Free();
};

END