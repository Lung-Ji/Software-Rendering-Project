#include "UIManager.h"

IMPLEMENT_SINGLETON(UIManager)

UIManager::UIManager() : Sprite(nullptr), isActive(false) {}
UIManager::~UIManager() {}

HRESULT UIManager::Ready_UIObject(LPDIRECT3DDEVICE9 _GRPDEV)

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
HRESULT UIManager::Ready_UIObject(UIManager* _Sprite)
{
  D3DXCreateSprite(_GRPDEV , &Sprite);
  return S_OK;
}

UIManager* UIManager::Create(LPDIRECT3DDEVICE9 _GRPDEV,CONST TCHAR* _uiName,CONST TCHAR* _PATH, UINT _WIDTH, 
  UINT _HEIGHT,  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY)
{
  
  return 0;
} 

HRESULT UIManager::Import_UISprite(LPDIRECT3DDEVICE9 _GRPDEV, UIType _uitype, CONST TCHAR* _PATH, UINT _WIDTH,
  UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY)
{
  vecList.push_back({ _uitype, {SpriteINFO(_PATH,_WIDTH,_HEIGHT,_POSX,_POSY,_VIS,_OPACITY)} });

  D3DXCreateTextureFromFileExW(_GRPDEV,
    vecList.back().second.back().PATH.c_str(),
    vecList.back().second.back().WIDTH,
    vecList.back().second.back().HEIGHT,
    1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
    (LPDIRECT3DTEXTURE9*)&vecList.back().second.back().TEXTURE);

  return S_OK;
}

VOID UIManager::Render_UI(LPDIRECT3DDEVICE9 _GRPDEV, UIType _uitype)
{
  _GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
  Sprite->Begin(D3DXSPRITE_ALPHABLEND);
  if(!isActive)
  {
    for (auto& pair : vecList)
    {
      if (pair.first == _uitype)
      {
        for (auto& sprite : pair.second)
          Sprite->Draw(sprite.TEXTURE, NULL, NULL, &sprite.POS, D3DCOLOR_ARGB(sprite.OPACITY, 255, 255, 255));
      }
      else
      {
        MSG_BOX("Not exist UIType");
      }
    }
  }
  Sprite->End();
  _GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}


VOID UIManager::Free() {
	for_each(TextureList.begin(), TextureList.end(), CDeleteMap());
	for (auto& TXT : KEY_Array) {
		Safe_Delete(TXT);
	}
	TextureList.clear();
}
VOID UIManager::Free()
{
}