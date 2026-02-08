#include"GameObject.h"

#pragma region Macros
#define POS(GAMEOBJECT)			static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define ROTATION(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation()
#define MYPOS					Component_Transform->Get_Position()
#pragma endregion

class Monster
{
public:
	explicit Monster() {}
	virtual ~Monster() {}

	static GameObject*	Set_Target(CONST TCHAR* _TAG, GameObject* GameObj = nullptr);



};