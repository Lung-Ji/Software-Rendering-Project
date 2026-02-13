#include "../Include/PCH.h"

GameObject* Monster::Set_Target(const TCHAR* _TAG, GameObject*& GameObj)
{
	GameObj = SceneManager::GetInstance()->Get_GameObject(_TAG);
	return GameObj;
}
GameObject* Monster::Set_Target(CONST TCHAR* _TAG)
{
	GameObject* GameObj = SceneManager::GetInstance()->Get_GameObject(_TAG);
	return GameObj;
}

_vec3 Monster::Normalize(_vec3 vec)
{
	_vec3 vTemp = vec;
	D3DXVec3Normalize(&vTemp, &vec);
	return vTemp;
}

HRESULT Monster::Set_TextureList(const TCHAR* __FileName, TEXINFO* __Textures)
{
	if (nullptr == __Textures)
		return E_POINTER;
		
	if (!wcscmp(__FileName, __Textures->_Filename))
		return S_OK;

	__Textures->_frame = 0;
	__Textures->_frameTick = 0.f;
	__Textures->_Endframe = 0;
	__Textures->_vecTexture.clear();
	__Textures->_vecTexture.reserve(32);
	wcscpy_s(__Textures->_Filename, 256, __FileName);

	while (true)
	{
		IDirect3DTexture9* pTexture = nullptr;
		TCHAR Filename[256];
		swprintf_s(Filename, 256, L"%s_%02d.png", __FileName, ++__Textures->_Endframe);
		pTexture = ResourceManager::GetInstance()->Find_Texture(Filename);
		if (nullptr == pTexture) break;
		else __Textures->_vecTexture.push_back(pTexture);
	}

	if (--__Textures->_Endframe) return S_OK;
	else return E_FAIL;
}

HRESULT Monster::Set_TextureList(const TCHAR* __FileName, MONINFO* _MonsterInfo)
{

	return Monster::Set_TextureList(__FileName, &_MonsterInfo->Textureinfo);
}

FLOAT Monster::BillBoard(Transform* TransCom, LPDIRECT3DDEVICE9 _GRPDEV, _vec3 vRight)
{
	if (D3DXVec3Length(&vRight) == 0) return 0.f;

	// View 행렬
	_matrix	matWorld;
	_GRPDEV->GetTransform(D3DTS_VIEW, &matWorld);

	// 카메라 위치 백업
	_vec3 Campos = *(_vec3*)&matWorld._41;

	// Right 벡터 대입
	D3DXVec3Normalize((_vec3*)&matWorld._11, &vRight);

	// 대입한 Right 벡터로 Up 벡터 재정의
	D3DXVec3Cross((_vec3*)&matWorld._21, (_vec3*)&matWorld._31, (_vec3*)&matWorld._11);

	// 역행렬 적용해서 BillBoard 행렬 구현및 스케일 적용
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);

	*(_vec3*)&matWorld._11 *= TransCom->Get_Scale()->x;
	*(_vec3*)&matWorld._22 *= TransCom->Get_Scale()->y;
	*(_vec3*)&matWorld._33 *= TransCom->Get_Scale()->z;

	// 이미지 위치 정렬
	matWorld._41 = TransCom->Get_Position()->x + matWorld._21 * 0.5f;
	matWorld._42 = TransCom->Get_Position()->y + matWorld._22 * 0.5f;
	matWorld._43 = TransCom->Get_Position()->z + matWorld._23 * 0.5f;

	// 쓰레기값 방지
	matWorld._14 = matWorld._24 = matWorld._34 = 0.f;
	matWorld._44 = 1.f;
	TransCom->Set_World(&matWorld);

	_float dx = Campos.x - matWorld._41;
	_float dy = Campos.y - matWorld._42;
	_float dz = Campos.z - matWorld._43;

	return sqrtf(dx * dx + dy * dy + dz * dz);
}

HRESULT Monster::Flip_Horizontal(Transform* TransCom, _vec3* pDir, _float Buffer)
{
	if (pDir->x	 < -Buffer)
	{
		if (TransCom->Get_Scale()->x < 0)
			TransCom->Get_Scale()->x *= -1.f;
	}
	else if (pDir->x > Buffer)
	{
		if (TransCom->Get_Scale()->x > 0)
			TransCom->Get_Scale()->x *= -1.f;
	}
	return S_OK;
}

VOID Monster::Add_Monster_to_Scene(GameObject* pMonster)
{
	TCHAR Classname[256];
	swprintf_s(Classname, 256, L"%S", typeid(*pMonster).name());

	CONST TCHAR* pName = wcschr(Classname, L' ');

	pName = (pName != nullptr) ? pName + 1 : Classname;
	pMonster->Set_ObjectTag(pName);
	SceneManager::GetInstance()->Get_CurrentScene()->Get_Layer(LAYER_TYPE::LAYER_DYNAMIC_OBJECT)->Add_GameObject(pMonster);

	CollisionManager::GetInstance()->Add_ColliderObject(pMonster);
}

	uint64_t Monster::XorShift128plus(uint64_t& _Seed1, uint64_t& _Seed2)
	{
		if (0 == _Seed1 || 0 == _Seed2)
		{
			_Seed1 = 0x123456789ABCDEF0;
			_Seed2 = 0xFEDCBA9876543210;
		}

		uint64_t x = _Seed1;
		uint64_t const y = _Seed2;
		_Seed1 = y;
		x ^= x << 23;
		_Seed2 = x ^ y ^ (x >> 17) ^ (y >> 26);

		return _Seed2 + y;
	}


VOID Monster::BillBoard_Standard(LPDIRECT3DDEVICE9 GRPDEV, Transform* Component_Transform)
{
	_matrix		matBill, matWorld, matView;

	matWorld = *Component_Transform->Get_World();
	GRPDEV->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	//X축
	matBill._11 = matView._11;
	matBill._12 = matView._12;
	matBill._13 = matView._13;
	//Y축
	matBill._21 = matView._21;
	matBill._22 = matView._22;
	matBill._23 = matView._23;
	//Z축
	matBill._31 = matView._31;
	matBill._32 = matView._32;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 주의 할 것
	matWorld = matBill * matWorld;

	Component_Transform->Set_World(&matWorld);
}
