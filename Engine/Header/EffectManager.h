#pragma once
#include "Base.h"
#include "Engine_Define.h"
#include "GameObject.h"

BEGIN(Engine)
class ENGINE_DLL EffectManager : public Base {
	DECLARE_SINGLETON(EffectManager)

private:
	explicit EffectManager();
	virtual ~EffectManager();
public:
	HRESULT		Ready_EffectManager();
	INT			Update_EffectManager(CONST FLOAT& _DT);
	VOID		LateUpdate_EffectManager(CONST FLOAT& _DT);
	VOID		Render_EffectManager(LPDIRECT3DDEVICE9 _GRPDEV);
public:
	HRESULT		Append_Effect(EFFECT_OWNER _Owner, GameObject* _Effect);

private:
	list<GameObject*>	Container_PlayerEffect;
	list<GameObject*>	Container_MonsterEffect;
	list<GameObject*>	Container_EnviromentEffect;
	list<GameObject*>	Container_UIEffect;
public:
	virtual			VOID	Free();
};

END