#include "../Include/PCH.h"

GameObject* Monster::Set_Target(const TCHAR* _TAG, GameObject* GameObj)
{
	GameObj = SceneManager::GetInstance()->Get_GameObject(_TAG);
	return GameObj;
}
