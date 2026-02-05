#pragma once

#include "Base.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL UIManager : public Base {
	DECLARE_SINGLETON(UIManager)

private:
	explicit UIManager();
	virtual ~UIManager();

public:
	HRESULT Ready_UIObject(SpriteObject* _Component_Sprite );
	VOID  Show_UI(SpriteObject* _Sprite);
	VOID	Hide_UI(SpriteObject* _Sprite);


private:
	virtual VOID	Free();
	BOOL		isActive;
private:
	std::list<vector<SpriteINFO>*> ActiveList;
	std::list<vector<SpriteINFO>*> ReverseList;
};

END