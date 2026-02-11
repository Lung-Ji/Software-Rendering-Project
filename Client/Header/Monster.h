#include"GameObject.h"

#pragma region Macros
#define POS(GAMEOBJECT)			static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define ROTATION(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation()
#define MYPOS					Component_Transform->Get_Position()
#define MYSCALE					Component_Transform->Get_Scale()
#define MYROTATION				Component_Transform->Get_Rotation()
#pragma endregion

#pragma region MonsterSummon
#define MONSTERSUMMON01PLAYTIME 0.5f
#define MONSTERSUMMON02PLAYTIME	0.5f
#define MONSTERSUMMON03PLAYTIME 0.55f

#pragma endregion

#pragma region Bat
#define BATTRACKINGDIS	5.f
#define BATTRACKINGMAX	3.f
#define BATTRACKINGMIN	2.f
#define BATATTACKREADY	1.f
#define BATATTACKEND	2.f
#define BATRUSHSPEED	2.f
#pragma endregion

typedef struct tagTextureInfo
{
	vector<IDirect3DTexture9*>	_vecTexture;
	TCHAR						_Filename[256]	= L"";
	_uint						_frame			=	0;
	_uint						_Endframe		=	0;
	_float						_frameTick		=	0.f;
}TEXINFO;

class Monster 
{
public:
	static	GameObject*		Set_Target(CONST TCHAR* _TAG, GameObject*& GameObj);
	static	GameObject*		Set_Target(CONST TCHAR* _TAG);

//·»´õ¸µ °ü·Ã
	static	HRESULT			Set_TextureList(CONST TCHAR* __FileName, TEXINFO* __Textures);
	static	FLOAT			BillBoard(Transform* TransCom, LPDIRECT3DDEVICE9 _GRPDEV, _vec3 vRight = { 1.f, 0.f,0.f });

	static	HRESULT			Flip_Horizontal(Transform* TransCom, _vec3* pDir, _float Buffer);
};