#pragma once
#include "GameObject.h"

enum class ArrowType {
	FairyArrow,
	IceArrow_LV1,
	IceArrow_LV2,
	IceCharging,
	EvilHead_Arrow,
	Wind_Arrow,

	End
};

class Arrow : public GameObject
{
private:
	explicit Arrow(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Arrow(const GameObject& _RHS);
	virtual ~Arrow();

public:
	virtual			HRESULT		Ready_GameObject(BowType _BOWTYPE, int _LVEL, int arrowAtk, _vec3* _PlayerPOS, _vec2 _arrowDir);
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();
	void			SetGrahpic();
private:
	Buffer*			Component_Buffer;
	Transform*		Component_Transform;
	Collider*		Component_Collider;

	IDirect3DTexture9* g_pTexture = NULL; // 로드된 이미지
	ID3DXSprite* g_pSprite = NULL;   // 스프라이트 객체

public:
	static Arrow*	Create(LPDIRECT3DDEVICE9 _GRPDEV, BowType _BOWTYPE, int _LVEL, int arrowAtk, _vec3* _PlayerPOS, _vec2 _arrowDir);
	int				Get_Atk()	{ return _arrowAtk; }
	BOOL			OnCollisionEnter(GameObject* _Other);
private:
	virtual VOID Free();

private:
	ArrowType	_type;
	int			_hp;
	_float		_originAngle;

	_vec3		_playerPos;
	float		_angle;
	float		_size;

	int			_frame;
	float		_frameDelay;

	float		_lifeTime;
	float		_speed;
	float		_sumSpeed;
	int			_arrowAtk;

	float _EvilTime;
};

