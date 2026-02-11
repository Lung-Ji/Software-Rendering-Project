#pragma once
#include "GameObject.h"
#include "Bow.h"

enum class pState
{
	STATE_IDLE,
	STATE_DASH,
	STATE_ATTACK,
	STATE_LANDING,

	End
};

enum class eState
{
	STATE_STANDING,
	STATE_RUN_UP,
	STATE_RUN_DOWN,
	STATE_RUN_LEFT,
	STATE_RUN_RIGHT,
	STATE_RUN_LU,
	STATE_RUN_RU,
	STATE_RUN_LD,
	STATE_RUN_RD,
	STATE_DASH,
	STATE_HANDUP,
	STATE_LANDING_DOWN,
	STATE_LANDING_UP,

	STATE_ATTACK_LU,
	STATE_ATTACK_RU,
	STATE_ATTACK_LD,
	STATE_ATTACK_RD,

	STATE_ATTACK_RUN_LU,
	STATE_ATTACK_RUN_RU,
	STATE_ATTACK_RUN_LD,
	STATE_ATTACK_RUN_RD,

	STATE_ATTACK_RUN_BACK_LU,
	STATE_ATTACK_RUN_BACK_RU,
	STATE_ATTACK_RUN_BACK_LD,
	STATE_ATTACK_RUN_BACK_RD,

	STATE_DASH_LEFT,
	STATE_DASH_RIGHT,
	STATE_DASH_UP,
	STATE_DASH_DOWN,
	STATE_DASH_LU,
	STATE_DASH_RU,
	STATE_DASH_LD,
	STATE_DASH_RD,
	
	STATE_SLIDE,
	STATE_VICTORY,
	STATE_DEAD,

	End
};

enum class pSee
{
	SEE_UP,
	SEE_DOWN,
	SEE_RIGHT,
	SEE_LEFT,
	SEE_LU,
	SEE_RU,
	SEE_LD,
	SEE_RD,

	End
};

enum class mousePos
{
	MOUSE_LT,
	MOUSE_RT,
	MOUSE_LD,
	MOUSE_RD,

	End
};

class Player : public GameObject {
private:
	explicit Player(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Player(const GameObject& _RHS);
	virtual ~Player();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();
private:
	Buffer*			Component_Buffer;
	Transform*		Component_Transform;
	Texture*		Component_Texture;
	StateMachine*	Component_FSM;
	Collider*		Component_Collider;
public:
	static Player* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	float	Get_Speed()				{ return _speed;}
	////////////////////// 광윤 추가
	void	Set_Speed(INT _value)	{ _speed = _value; }

	int		Get_HP() { return _hp; }
	void	Set_HP(INT _value) { _hp = _value; }

	int		Get_Key() { return _key; }
	void	Set_Key(INT _value) { _key = _value; }

	int		Get_Coin() { return _coin; }
	void	Set_Coin(INT _value) { _coin = _value; }

	int		Get_Crystal() { return _crystal; }
	void	Set_Crystal(INT _value) { _crystal = _value; }
	
	int		Get_DashStock() { return _dashstock; }
	void	Set_DashStock(INT _value) { _dashstock = _value; }
	
	int		Get_Token() { return _token; }
	void	Set_Token(INT _value) { _token = _value; }
	//////////////////////

private:
	virtual VOID Free();

private:
	D3DXVECTOR3			MousePicker_NonTarget(HWND _hWnd, Buffer* _TerrainBuffer, Transform* _TerrainTransform);
	D3DXVECTOR3			RayOnTerrain();
	D3DXVECTOR3			SetOnTerrain();

	void			IDLE_STATE(const _float& _DT);
	void			DASH_STATE(const _float& _DT);
	void			ATTACK_STATE(const _float& _DT);
	void			Idle_Final_Input(const _float& _DT);
	void			SetGrahpic();
	void			Anim(TCHAR FileName[128], float delay, int maxIdx, bool reverse = false);
	


private:
	bool			Debug;
	float			_cameraAngle;

	pState			_pState;
	eState			_eState;
	pSee			_see;

	_uint			_frame;
	float			_frameTick;

	bool			_dashStart;
	float			_defaultSpeed;
	float			_dashTime;
	float			_dashG;
	float			_speed;
	////////////////////// 광윤 추가
	int				_hp;			// 플레이어 HP
	int				_dashstock;		// 플레이어 MP(눈물모양)
	int				_key;			// 플레이어 key
	int				_coin;			// 플레이어 coin
	int				_crystal;		// 플레이어 crystal
	int				_token;			// 플레이어 스킬 횟수(다이아몬드 모양)
	/////////////////////
	float			_g;
	float			_slideTime;

	GameObject*			_inventory[8];
	Bow*				_weaponSlot[4];
	GameObject*			_artifactSlot[4];
};
