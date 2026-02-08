#include "UIManager.h"

IMPLEMENT_SINGLETON(UIManager)

UIManager:: UIManager()	{			}
UIManager::~UIManager() {	Free();	}

HRESULT UIManager::Ready_UIManager(LPDIRECT3DDEVICE9 _GRPDEV) {
	PathFinder(_GRPDEV, L"../../UI");
	return S_OK;
}
INT UIManager::Update_UIManager(const FLOAT& _DT) {
	return 0;
}
VOID UIManager::LateUpdate_UIManager(const FLOAT& _DT) {
	
}
VOID UIManager::Render_UIManager(LPDIRECT3DDEVICE9 _GRPDEV) {
	_GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//for (auto& SPR : TextureList)
	//	Sprite->Draw(SPR.second, NULL, NULL, &SPR.POS, D3DCOLOR_ARGB(SPR.OPACITY, 255, 255, 255));

	Sprite->End();
	_GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT UIManager::PathFinder(LPDIRECT3DDEVICE9 _GRPDEV, wstring _MasterFolder) {
	_wfinddata64_t Data;
	
	INT Result = 1;
	
	wstring STRUNI = _MasterFolder + L"/*.*";
	
	intptr_t Handle = _wfindfirst64(STRUNI.c_str(), &Data);
	if (Handle == -1)	return E_FAIL;
	
	LPDIRECT3DTEXTURE9 TEX = nullptr;
	
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
			D3DXCreateTextureFromFileW(_GRPDEV, WideRootPath.c_str(), &TEX);
			if (TEX != nullptr)	TextureList.insert({ KEY_Array.back()->c_str(), TEX });
		}
		Result = _wfindnext64(Handle, &Data);
	}
	
	_findclose(Handle);
	
	return S_OK;
}

HRESULT UIManager::Append_Sprite(wstring PATH, UINT WIDTH, UINT HEIGHT) {
	
	return S_OK;
}


VOID UIManager::Free() {
	for_each(TextureList.begin(), TextureList.end(), CDeleteMap());
	for (auto& TXT : KEY_Array) {
		Safe_Delete(TXT);
	}
	TextureList.clear();
}
