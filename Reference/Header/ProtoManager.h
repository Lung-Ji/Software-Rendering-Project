#pragma once
#include "Base.h"

#include "Buffer.h"
#include "Transform.h"
#include "Texture.h"
#include "Sprite.h"
#include "Collider.h"
#include "StateMachine.h"
#include "TileInfo.h"
BEGIN(Engine)
class ENGINE_DLL ProtoManager : public Base {
	DECLARE_SINGLETON(ProtoManager)
private:
	explicit ProtoManager();
	virtual ~ProtoManager();

public:
	HRESULT		Ready_Prototype(LPDIRECT3DDEVICE9 _GRPDEV);
	Component*	Clone_Prototype(COMPONENT_TYPE _TYPE);

private:
	vector<Component*>		ComponentList;
private:
	virtual VOID	Free();
};

END