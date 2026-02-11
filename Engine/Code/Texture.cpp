#include "Texture.h"

Texture::Texture()													{}
Texture::Texture(LPDIRECT3DDEVICE9 _GRPDEV) : Component(_GRPDEV)	{}
Texture::Texture(const Texture& _RHS) : Component(_RHS)				{ TextureList = _RHS.TextureList; }
Texture::~Texture()													{}

VOID Texture::Set_Texture(CONST TCHAR* _FileName)	{
	auto iter = find_if(TextureList.begin(), TextureList.end(), CTag_Finder(_FileName));
	if (iter == TextureList.end())	return;
	GRPDEV->SetTexture(0, iter->second);
}
IDirect3DTexture9* Texture::Find_Texture(const TCHAR* _FileName){
	auto iter = find_if(TextureList.begin(), TextureList.end(), CTag_Finder(_FileName));
	if (iter == TextureList.end())	return nullptr;
	return iter->second;
}
HRESULT Texture::Import_TextureFromFolder(wstring _FolderName)	{
	 
	_wfinddata64_t Data;
	
	INT Result = 1;

	wstring STRUNI = _FolderName + L"/*.*";
	
	intptr_t Handle = _wfindfirst64(STRUNI.c_str(), &Data);

	IDirect3DTexture9* TEX = nullptr;
	
	if (Handle == -1)	return E_FAIL;
	while (Result != -1) {
		wstring WideRootPath = _FolderName + L"/" + Data.name;
		wstring* KEY = new wstring(Data.name);
		KEY_Array.push_back(KEY);
		D3DXCreateTextureFromFile(GRPDEV, WideRootPath.c_str(), (LPDIRECT3DTEXTURE9*)&TEX);
		if(TEX !=nullptr)	TextureList.insert({ KEY_Array.back()->c_str(), TEX});
		Result = _wfindnext64(Handle, &Data);
	}
	
	_findclose(Handle);
	
	return S_OK;
}
Texture*	Texture::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Texture* TXT = new Texture(_GRPDEV);
	if (FAILED(TXT->Ready_Component())) {
		MSG_BOX("Cannot Create Texture.");
		Safe_Release(TXT);
		return nullptr;
	}
	return TXT;
}
Component*	Texture::Clone() {
	return new Texture(*this);
}
VOID		Texture::Free() {
	for_each(TextureList.begin(), TextureList.end(), CDeleteMap());
	for (auto& TXT : KEY_Array) {
		Safe_Delete(TXT);
	}
	TextureList.clear();

	Component::Free();
}