#include "../Include/PCH.h"
#include "UIEffect.h"

UIEffect::UIEffect(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV)		{}
UIEffect::UIEffect(CONST GameObject& _RHS)	  : GameObject(_RHS)		{}
UIEffect::~UIEffect(){}

HRESULT   UIEffect::Ready_Effect(UI_EFFECT _EFTTYPE, wstring _TAG, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _UISCALE, INT _OPAC, BOOL _Repeatable, FLOAT _PlayTime) {
	if (FAILED(Component_Initialize())) return E_FAIL;
	D3DXCreateSprite(GRPDEV, &Sprite);
	if		(_EFTTYPE == UI_EFFECT::COIN_EFFECT) { Make_TextureList(L"PT_Coin 1_", _UIPOS, _UISCALE, _OPAC);			}
	else if (_EFTTYPE == UI_EFFECT::HP_EFFECT)	 { Make_TextureList(L"Spr_Ui_DashStock_Idle_", _UIPOS, _UISCALE, _OPAC); }

	PlayTime = _PlayTime;
	Repeatable = _Repeatable;
	ObjectTAG = _TAG;

	D3DXMatrixScaling(&MatScale, _UISCALE.x, _UISCALE.y, 1.f);
	D3DXMatrixTranslation(&MatPos, _UIPOS.x, _UIPOS.y, 0.f);
	MatTransform = MatScale * MatPos;

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
	Sprite->SetTransform(&MatTransform);
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (auto& SPR : TextureList) {
		Sprite->Draw(TextureList[TextureIndex]->BaseTexture, NULL, NULL, NULL,
			D3DCOLOR_ARGB(TextureList[TextureIndex]->Opacity, 255, 255, 255));
	}
	
	Sprite->End();
	GRPDEV->SetRenderState(D3DRS_ZENABLE, TRUE);
}

HRESULT   UIEffect::Component_Initialize() {
	Component_Sprite	= ADD_COMPONENT_SPRITE;

	return S_OK;
}
HRESULT	  UIEffect::Make_TextureList(wstring _FileName, D3DXVECTOR3 _POS, D3DXVECTOR3 _SCALE, INT _OPACITY) {
	INT FRAME = 0;
	while (++FRAME) {
		wstring FileName = _FileName + to_wstring(FRAME) + L".png";
		LPDIRECT3DTEXTURE9 TEX = ResourceManager::GetInstance()->Find_Texture(FileName.c_str());
		if (TEX == nullptr)	break;

		EffectINFO* EINFO = new EffectINFO(TEX, _POS, _SCALE, _OPACITY);
		TextureList.push_back(EINFO);
	}
	ENDFRAME = TextureList.size() + 1;

	return S_OK;
}
UIEffect* UIEffect::Create(LPDIRECT3DDEVICE9 _GRPDEV, wstring _TAG, UI_EFFECT _SKILLTYPE, D3DXVECTOR3 _UIPOS, D3DXVECTOR3 _SCALE, INT _OPACITY, BOOL _Repeatable, FLOAT _PlayTime) {
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
	for (auto& EI : TextureList) {
		Safe_Delete(EI);
	}
	GameObject::Free();
}