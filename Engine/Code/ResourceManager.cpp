#include "ResourceManager.h"

IMPLEMENT_SINGLETON(ResourceManager)

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() { Free(); }

HRESULT ResourceManager::GlobalImport_Texture(IDirect3DDevice9* _GRPDEV, wstring _MasterFolder) {
	PathFinder(_GRPDEV, _MasterFolder);
	return S_OK;
}

HRESULT ResourceManager::PathFinder(IDirect3DDevice9* _GRPDEV, wstring _MasterFolder) {
	_wfinddata64_t Data;

	INT Result = 1;

	wstring STRUNI = _MasterFolder + L"/*.*";

	intptr_t Handle = _wfindfirst64(STRUNI.c_str(), &Data);
	if (Handle == -1)	return E_FAIL;

	IDirect3DBaseTexture9* TEX = nullptr;

	if (Handle == -1)	return E_FAIL;
	while (Result != -1) {
		
		wstring Route = Data.name;
		if (Route == L".." || Route == L".") {
			Result = _wfindnext64(Handle, &Data);
			continue;
		}
		wstring WideRootPath = _MasterFolder + L"/" + Data.name;
		

		if (Data.attrib & FILE_ATTRIBUTE_DIRECTORY) {
			PathFinder(_GRPDEV, WideRootPath);
		}
		else {
			wstring* KEY = new wstring(Data.name);
			KEY_Array.push_back(KEY);
			D3DXCreateTextureFromFile(_GRPDEV, WideRootPath.c_str(), (LPDIRECT3DTEXTURE9*)&TEX);
			if (TEX != nullptr)	TextureList.insert({ KEY_Array.back()->c_str(), TEX });
		}
		Result = _wfindnext64(Handle, &Data);
	}

	_findclose(Handle);

	return S_OK;
}

IDirect3DBaseTexture9* ResourceManager::Find_Texture(const TCHAR* _FileName) {
	auto iter = find_if(TextureList.begin(), TextureList.end(), CTag_Finder(_FileName));
	if (iter == TextureList.end())	return nullptr;
	return iter->second;
}
VOID	ResourceManager::Free() {
	for_each(TextureList.begin(), TextureList.end(), CDeleteMap());
	for (auto& TXT : KEY_Array) {
		Safe_Delete(TXT);
	}
	TextureList.clear();
}