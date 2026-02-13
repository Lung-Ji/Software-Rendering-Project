#pragma once
#include "GameObject.h"
#include "PlayerEquipMent.h"


class PlayerInven :  public GameObject {
	explicit PlayerInven(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit PlayerInven(CONST GameObject& _RHS);
	virtual ~PlayerInven();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	HRESULT Sprite_Initialize();
	HRESULT Text_Initialize();
	HRESULT Item_Initialize();

public:
	HRESULT Selecting_SavedItem();
	HRESULT Selecting_EquipItem();

	HRESULT	Equip_Item();

	HRESULT Display_ItemInfo();

	HRESULT Append_Item(ItemINFO* _ITEM);

public:
	static	PlayerInven* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	SpriteObject*	Component_Sprite;
	Player*			PlayerObject;

	BOOL			FocusOn_SavedItem;
	BOOL			FocusOn_EquipedItem;

	_int			SavedItemIndex;
	_int			EquipedItemIndex;

	ItemINFO*		Equip_ItemList[8];
	ItemINFO*		Saved_ItemList[10];

	vector<SpriteINFO*> ItemInfo_Screen;

	vector<FontObject*>	ItemInfo_Text;

	vector<SpriteINFO*> ItemDictionary_InvenFrame;
	vector<SpriteINFO*> ItemDictionary_InfoFrame;

	BOOL			EquipMode;
	ItemINFO*		EquipObject;

private:
	virtual	VOID		Free();
};