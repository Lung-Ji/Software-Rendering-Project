#include "Sprite.h"

SpriteObject:: SpriteObject()							:					  Sprite(nullptr){}
SpriteObject:: SpriteObject(LPDIRECT3DDEVICE9 _GRPDEV)	: Component(_GRPDEV), Sprite(nullptr){}
SpriteObject:: SpriteObject(CONST SpriteObject& _RHS)	: Component(_RHS)	, Sprite(_RHS.Sprite), TextureList(_RHS.TextureList){}
SpriteObject::~SpriteObject()																									{}

HRESULT SpriteObject::Ready_Sprite() {
	D3DXCreateSprite(GRPDEV, &Sprite);
	
	return S_OK;
}
INT SpriteObject::Update_Sprite() {

	return 0;
}
VOID SpriteObject::Render_Sprite() {
	GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (auto& SPR : TextureList) {
		if(SPR.VISIBLE == TRUE)
			Sprite->Draw(SPR.TEXTURE, NULL, NULL, &SPR.POS, D3DCOLOR_ARGB(SPR.OPACITY, 255, 255, 255));
	}

	Sprite->End();
	GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT SpriteObject::Import_Sprite(CONST TCHAR* _PATH, CONST TCHAR* _KEY, FLOAT _POSX, FLOAT _POSY, UINT _WIDTH, UINT _HEIGHT, BOOL _VIS, INT _OPACITY) {
	TextureList.push_back(SpriteINFO(_KEY, _WIDTH, _HEIGHT, _POSX, _POSY, _VIS, _OPACITY));

	D3DXCreateTextureFromFileExW(GRPDEV, _PATH, TextureList.back().WIDTH, TextureList.back().HEIGHT,
		1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, (LPDIRECT3DTEXTURE9*)&TextureList.back().TEXTURE);
	
	return S_OK;
}

SpriteINFO* SpriteObject::Get_Texture(wstring _KEY) {
	SpriteINFO* Sprite = nullptr;

	for (auto& i : TextureList) {
		if (i.KEY == _KEY)
			Sprite = &i;
	}
	return Sprite;
}

SpriteObject* SpriteObject::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	SpriteObject* SPR = new SpriteObject(_GRPDEV);
	if (FAILED(SPR->Ready_Sprite())) {
		MSG_BOX("Cannot Create Sprite.");
		Safe_Release(SPR);
		return nullptr;
	}
	return SPR;
}
Component* SpriteObject::Clone() {
	return new SpriteObject(*this);
}
VOID		SpriteObject::Free() {
	Component::Free();
}