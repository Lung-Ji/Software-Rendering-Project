#include "../Include/PCH.h"

GameObject* Monster::Set_Target(const TCHAR* _TAG, GameObject* GameObj)
{
	GameObj = SceneManager::GetInstance()->Get_GameObject(_TAG);
	return GameObj;
}

D3DSURFACE_DESC Monster::Get_SurfaceDesc(LPDIRECT3DTEXTURE9 pTexture)
{
	return D3DSURFACE_DESC();
}

IDirect3DTexture9* Monster::Find_CurrTexture(const TCHAR* _FileName, IDirect3DTexture9* pTexture)
{
	pTexture = ResourceManager::GetInstance()->Find_Texture(_FileName);
	return pTexture;
}

TEXTUREINFO* Monster::Set_Textureinfo(TEXTUREINFO* __Textureinfo, const TCHAR* __Filename)
{
	LPDIRECT3DTEXTURE9 pTexture = ResourceManager::GetInstance()->Find_Texture(__Filename);

	D3DSURFACE_DESC Surface;
	pTexture->GetLevelDesc(0, &Surface);

	if (__Textureinfo->MAXWidth < Surface.Width)
		__Textureinfo->MAXWidth = Surface.Width;

	if (__Textureinfo->MAXHeight < Surface.Height)
		__Textureinfo->MAXHeight = Surface.Height;

	__Textureinfo->vecTexture.push_back(pTexture);
	return __Textureinfo;
}

