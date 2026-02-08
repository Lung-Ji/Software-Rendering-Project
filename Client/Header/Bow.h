#pragma once
#include "GameObject.h"

enum class BowType {
	IceBow,

	End
};

class Bow : public GameObject
{
private:
	explicit Bow(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Bow(const GameObject& _RHS);
	virtual ~Bow();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

public:
	void			Set_PlayerPos(_vec3* pos) { _playerPos = pos; }

private:
	HRESULT			Component_Initialize();
	void			SetGrahpic();
private:
	Buffer* Component_Buffer;
	Transform* Component_Transform;
	Texture* Component_Texture;
public:
	static Bow* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();
private:
	_vec3* _playerPos;
	float _motionDelay;
	BowType _type;
	_float _cameraAngle;
	_vec3 _cameraDir;
};

