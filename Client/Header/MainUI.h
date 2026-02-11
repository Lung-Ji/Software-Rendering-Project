#pragma once
#include "GameObject.h"
#include "Player.h"

class MainUI : public GameObject {
private:
	explicit MainUI(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit MainUI(CONST GameObject& _RHS);
	virtual ~MainUI();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:		// Trigger Function
	VOID			Player_LostHP();
	VOID			Player_KeyModify();
	VOID			Player_MoneyModify();
	VOID			Player_CrystalModify();
	VOID			Player_UseSkill();
	VOID			PopUp_Interaction_Notice(wstring _Text, BOOL _Vis);
	VOID			PopUp_ItemInfo(wstring ItemTag, FLOAT _DT);
	VOID			PopUp_Speech_Bubble(wstring _Text, FLOAT _DT);

	VOID			Speech_PopUp(wstring _Text) { Speech_Text = _Text; Speech_Bubble = TRUE; }

	VOID			All_UI_FadeOUT();
	VOID			All_UI_FadeIN();

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Effect_Initialize();
	HRESULT	Text_Initialize();

	static	MainUI*		Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject*		Component_Sprite;
	vector<SpriteINFO>*	TextureList;

	BOOL	Speech_Bubble;
	wstring Speech_Text;

	BOOL	ItemInfo;
	wstring ItemTag;

	INT		Current_KeyCount;
	INT		Current_CoinCount;
	INT		Current_CrystalCount;

	Player* PlayerObject;

	FLOAT	Timer01, Timer02, Timer03;

	FLOAT	MainUIOpacity;

private:
	virtual	VOID		Free();
};

