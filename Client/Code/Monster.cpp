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
