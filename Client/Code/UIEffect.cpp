#include "../Include/PCH.h"
#include "UIEffect.h"

UIEffect::UIEffect(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)		{}
UIEffect::UIEffect(CONST GameObject& _RHS)	  : GameObject(_RHS)		{}
UIEffect::~UIEffect(){}

HRESULT   UIEffect::Ready_Effect(MAIN_UI_EFFECT _EFTTYPE, wstring _TAG, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _UISCALE, INT _OPAC, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;

	D3DXCreateSprite(GRPDEV, &Sprite);

	if		(_EFTTYPE == MAIN_UI_EFFECT::COIN_EFFECT)		{ Make_TextureList(L"MainUI/Coin"		, L"", _UIPOS.x, _UIPOS.y, _UISCALE.x, _UISCALE.y, TRUE, _OPAC); }
	else if (_EFTTYPE == MAIN_UI_EFFECT::DASHSTOCK_EFFECT)  { Make_TextureList(L"MainUI/DashStock"	, L"", _UIPOS.x, _UIPOS.y, _UISCALE.x, _UISCALE.y, TRUE, _OPAC); }
	else if (_EFTTYPE == MAIN_UI_EFFECT::HP_EFFECT)			{ Make_TextureList(L"MainUI/HP_Lost"		, L"", _UIPOS.x, _UIPOS.y, _UISCALE.x, _UISCALE.y, TRUE, _OPAC); }
	else if (_EFTTYPE == MAIN_UI_EFFECT::TOKEN_EFFECT)		{ Make_TextureList(L"MainUI/Token_Lost"	, L"", _UIPOS.x, _UIPOS.y, _UISCALE.x, _UISCALE.y, TRUE, _OPAC); }
	
	PlayTime	= _PlayTime;
	Repeatable	= _Repeatable;
	ObjectTAG	= _TAG;

	return S_OK;
}
INT	 UIEffect::Update_GameObject(const _float& _DT) {
	if (ObjectDead)	return 0;
	GameObject::Update_GameObject(_DT);

	FrameTick += _DT;

	return 0;
}
VOID UIEffect::LateUpdate_GameObject(const _float& _DT) {
	if (ObjectDead)	return;
	if (FrameTick > PlayTime / ENDFRAME) {
		if (TextureIndex++ >= ENDFRAME - 2) {
			if (Repeatable) { TextureIndex = 0; }
			else {
				TextureIndex = ENDFRAME - 2;
				//ObjectDead = TRUE;
			}
		}
		FrameTick = 0.f;
	}
}
VOID UIEffect::Render_GameObject() {
	if (ObjectDead)	return;
	GRPDEV->SetRenderState(D3DRS_ZENABLE, FALSE);
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (TextureList[TextureIndex].VISIBLE == TRUE) {
		Sprite->Draw(TextureList[TextureIndex].TEXTURE, NULL, NULL, &TextureList[TextureIndex].POS,
			D3DCOLOR_ARGB(TextureList[TextureIndex].OPACITY, 255, 255, 255));
	}
	
	Sprite->End();
	GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT   UIEffect::Component_Initialize() {
	Component_Sprite	= ADD_COMPONENT_SPRITE;
	return S_OK;
}
HRESULT	  UIEffect::Make_TextureList(wstring _PATH, wstring _KEY, FLOAT _POSX, FLOAT _POSY, UINT _WIDTH, UINT _HEIGHT, BOOL _VIS, INT _OPACITY) {
	INT FRAME = 0;
	while (++FRAME) {
		wstring FileName = L"../../UI/" + _PATH + to_wstring(FRAME) + L".png";
		//wstring FileName = _PATH + to_wstring(FRAME) + L".png";
		TextureList.push_back(EffectINFO(_KEY, _WIDTH, _HEIGHT, _POSX, _POSY, _VIS, _OPACITY));

		D3DXCreateTextureFromFileExW(GRPDEV, FileName.c_str(), TextureList.back().WIDTH, TextureList.back().HEIGHT,
			1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, (LPDIRECT3DTEXTURE9*)&TextureList.back().TEXTURE);
		if (TextureList.back().TEXTURE == nullptr) {
			TextureList.pop_back();
			break;
		}
	}
	ENDFRAME = TextureList.size() + 1;
	return S_OK;
}
UIEffect* UIEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, wstring _TAG, MAIN_UI_EFFECT _SKILLTYPE, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _SCALE, INT _OPACITY, BOOL _Repeatable, FLOAT _PlayTime) {
	UIEffect* EFT = new UIEffect(_GRPDEV);
	if (FAILED(EFT->Ready_Effect(_SKILLTYPE, _TAG, _UIPOS, _SCALE, _OPACITY, _Repeatable, _PlayTime))) {
		MSG_BOX("Cannot Create Effect.");
		Safe_Release(EFT);
		return nullptr;
	}
	return EFT;
}
VOID UIEffect::Replay_Effect(wstring _TAG) {
	UIEffect* Effect = dynamic_cast<UIEffect*>(EffectManager::GetInstance()->Get_Effect(EFFECT_OWNER::UI, _TAG));
	if (Effect == nullptr)	return;
	Effect->TextureIndex = 0;
}
VOID	  UIEffect::Free() {
	GameObject::Free();
}