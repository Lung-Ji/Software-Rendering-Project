#include "../Include/PCH.h"
#include "Bow.h"
#include <random>

Bow::Bow(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bow::Bow(const GameObject& _RHS) : GameObject(_RHS) {}
Bow::~Bow() {}

HRESULT Bow::Ready_GameObject()
{
	if (FAILED(Component_Initialize())) return E_FAIL;

	_lateReady = true;
	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };

	_cameraAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&_cameraDir, &_cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	_cameraAngle = _cameraAngle / D3DX_PI * 180.f;

	_alphaRatio = 0.f;

	Component_Transform->Set_Scale({ 1.f, 1.f, 1.f });

	_Charging = 0;

	return S_OK;
}

INT Bow::Update_GameObject(const _float& _DT)
{
	if (_lateReady) {
		Late_Ready();
		_lateReady = false;
	}
		

	if (_isEquip) {
		GameObject::Update_GameObject(_DT);
		RenderManager::GetInstance()->Add_RenderGroup(RENDER_NONALPHA, this);

		if (_isDestroied) return -1;

		float alphaSpeed = 3.f;

		bool mouseLB = KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80;
		if (mouseLB || KEY_HOLD(DIK_SPACE)) {
			if (_alphaRatio < 1.f)
				_alphaRatio += _DT * alphaSpeed;
			if (_alphaRatio > 1.f)
				_alphaRatio = 1.f;
		}
		else
		{
			if (_alphaRatio > 0.f)
				_alphaRatio -= _DT * alphaSpeed;
			if (_alphaRatio < 0.f)
				_alphaRatio = 0.f;

			_ChargingTime = 0;
			_Charging = 0;
			_Charge = 0;
		}

		POINT MousePoint{ 0, 0 };
		GetCursorPos(&MousePoint);
		ScreenToClient(hWnd, &MousePoint);

		_vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
		_vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

		_vec2 dir2D = mousePos - screenCenter;
		D3DXVec2Normalize(&dir2D, &dir2D);

		float angle = atan2f(dir2D.y, dir2D.x);

		float radius = 1.f;
		if (_type == BowType::FairyBow) radius = 1.5f;

		float offsetX = cosf(angle) * radius;
		float offsetY = sinf(angle) * radius;

		Component_Transform->Set_Pos({
			(*_playerPos).x + offsetX,
			(*_playerPos).y + offsetY,
			(*_playerPos).z
			});

		_vec3 eye = { 0.f, 0.f, 0.f };
		_vec3 at = _cameraDir;
		_vec3 up = { 0.f, 1.f, 0.f };

		_matrix matSize;
		D3DXMatrixIdentity(&matSize);
		D3DXMatrixScaling(&matSize, 1.0f, 2.0f, 1.0f);

		_matrix matBillboard;
		D3DXMatrixLookAtLH(&matBillboard, &eye, &at, &up);
		D3DXMatrixInverse(&matBillboard, nullptr, &matBillboard);

		float radian = D3DX_PI / 180.f;
		_matrix matRotZ;
		D3DXMatrixRotationZ(&matRotZ, angle - D3DX_PI);

		_matrix matWorld = matSize * matRotZ * matBillboard;

		matWorld._41 = (*_playerPos).x + offsetX;
		matWorld._42 = (*_playerPos).y;
		matWorld._43 = (*_playerPos).z - offsetY;

		Component_Transform->Set_World(&matWorld);


		if (KEY_HOLD(DIK_SPACE)) {
			if (_ChargingTime < 1.f) {
				if (_Charge++ == 0) {
					float radius = 1.f;
					if (_type == BowType::FairyBow) radius = 1.1f;
					else if (_type == BowType::IceBow) radius = 1.6f;
					else if (_type == BowType::EvilHeadBow) radius = 1.0f;
					else if (_type == BowType::WindBow) radius = 1.6f;

					float offsetX = cosf(angle) * radius;
					float offsetY = sinf(angle) * radius;

					_pulsepos = { _playerPos->x + offsetX , _playerPos->y, _playerPos->z - offsetY };
					_vec3 Size = { 1.f, 1.f, 1.f };
					PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::ICE_CHARGE, &_pulsepos, 1.f, Size);
				}

				_ChargingTime += _DT;
				_Charging = 0;
			}
			else
				_Charging++;

			CreateChargingEffect(_DT);

			if (_ChargingTime > 1.f && MOUSE_LBUTTON) {
				CreateEffect(_DT);
				CreateArrow(_DT);
				_ChargingTime = 0.f;
				_Charge = 0;
				_Charging = 0;
			}
		}
		else {
			CreateEffect(_DT);
			CreateArrow(_DT);
		}
	}
	else
		_alphaRatio = 0.f;
	
	return S_OK;
}

VOID Bow::LateUpdate_GameObject(const _float& _DT)
{
	if(_isEquip)
		GameObject::LateUpdate_GameObject(_DT);
}

VOID Bow::Render_GameObject()
{
	if (_isEquip) {
		GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

		SetGrahpic();

		Component_Buffer->Render_Buffer();

		GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// 초기화
		GRPDEV->SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
		GRPDEV->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
	
	return VOID();
}

HRESULT Bow::Component_Initialize()
{
	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;
	Component_Texture = ADD_COMPONENT_TEXTURE;
	Component_Texture->Import_TextureFromFolder(L"../../Resource/Weapon/IceBow");

	//D3DXCreateTextureFromFile(g_pd3dDevice, L"image.png", &g_pTexture);
	//D3DXCreateSprite(g_pd3dDevice, &g_pSprite);
	return S_OK;
}

void Bow::SetGrahpic()
{
	TCHAR FileName[128] = L"";

	switch (_type) {
	case BowType::FairyBow:
		wsprintfW(FileName, L"FairyBow.png");
		break;
	case BowType::IceBow:
		wsprintfW(FileName, L"IceBow.png");
		break;
	case BowType::EvilHeadBow:
		wsprintfW(FileName, L"EvilHeadBow.png");
		break;
	case BowType::WindBow:
		wsprintfW(FileName, L"WindBow.png");
		break;
	}

	DWORD tfactor = D3DCOLOR_ARGB(
		(BYTE)(_alphaRatio * 255.f),
		255, 255, 255
	);

	GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	GRPDEV->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	GRPDEV->SetRenderState(D3DRS_TEXTUREFACTOR, tfactor);

	GRPDEV->SetTexture(0, (ResourceManager::GetInstance()->Find_Texture(FileName)));
	
	// COLOR = Texture * TFACTOR
	GRPDEV->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GRPDEV->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GRPDEV->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	// ALPHA = TextureAlpha * TFACTORAlpha
	GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GRPDEV->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
}

void Bow::CreateArrow(const _float& _DT)
{
	bool mouseLB = KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80;

	if (mouseLB)
	{
		if (_attackDelay > 0.6) {
			POINT MousePoint{ 0, 0 };
			GetCursorPos(&MousePoint);
			ScreenToClient(hWnd, &MousePoint);

			_vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
			_vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

			_vec2 dir2D = mousePos - screenCenter;
			D3DXVec2Normalize(&dir2D, &dir2D);

			float angle = atan2f(dir2D.y, dir2D.x);

			float radius = 1.8f;

			float offsetX = cosf(angle) * radius;
			float offsetY = sinf(angle) * radius;

			_arrowPos = { _playerPos->x + offsetX , _playerPos->y, _playerPos->z - offsetY };

			_vec2 side = { dir2D.y, dir2D.x };
			D3DXVec2Normalize(&side, &side);
			_vec3 rightPos = _arrowPos;
			_vec3 leftPos = _arrowPos;
			float convergeAngle = D3DXToRadian(5.f);
			_vec2 rightDir = {
				cosf(angle - convergeAngle),
				sinf(angle - convergeAngle)
			};
			
			_vec2 leftDir = {
				cosf(angle + convergeAngle),
				sinf(angle + convergeAngle)
			};
      GameObject* arrow = Arrow::Create(GRPDEV, ArrowType::IceArrow_LV1, &_arrowPos);

				arrow->Set_ObjectTag(L"PlayerArrow");
				arrow->Set_ObjectType(GAMEOBJECT_TYPE::OBJECT_PLAYER);

				SceneManager::GetInstance()->Get_CurrentScene()->Get_Layer(LAYER_TYPE::LAYER_DYNAMIC_OBJECT)->Add_GameObject(arrow);
			switch (_type)
			{
			case BowType::FairyBow :
				MakeArrow(_arrowPos, dir2D);
				break;
			case BowType::IceBow:
				if (KEY_HOLD(DIK_SPACE)) {
					MakeArrow(_arrowPos, dir2D, true);
				}
				else{
					MakeArrow(_arrowPos, dir2D);
					rightPos.x -= side.x * 1.5f;
					rightPos.z -= side.y * 1.5f;
					leftPos.x += side.x * 1.5f;
					leftPos.z += side.y * 1.5f;
					MakeArrow(rightPos, rightDir);
					MakeArrow(leftPos, leftDir);
				}
				break;
			default :
				MakeArrow(_arrowPos, dir2D);

			}

			_attackDelay = 0.f;
		}
	}

}

void Bow::CreateEffect(const _float& _DT)
{
	bool mouseLB = KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80;
	_attackDelay += _DT;

	POINT MousePoint{ 0, 0 };
	GetCursorPos(&MousePoint);
	ScreenToClient(hWnd, &MousePoint);

	_vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
	_vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

	_vec2 dir2D = mousePos - screenCenter;
	D3DXVec2Normalize(&dir2D, &dir2D);

	float angle = atan2f(dir2D.y, dir2D.x);

	float radius = 1.f;
	if (_type == BowType::FairyBow) radius = 1.1f;
	else if (_type == BowType::IceBow) radius = 1.6f;
	else if (_type == BowType::EvilHeadBow) radius = 1.0f;
	else if (_type == BowType::WindBow) radius = 1.6f;

	float offsetX = cosf(angle) * radius;
	float offsetY = sinf(angle) * radius;

	_pulsepos = { _playerPos->x + offsetX , _playerPos->y, _playerPos->z - offsetY };

	if (mouseLB)
	{
		// 이펙트
		if (_attackDelay > 0.6) {
			_vec3 Size = { 1.f, 1.f, 1.f };
			switch (_type)
			{
			case BowType::FairyBow :
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::FAIRY_PULSE, &_pulsepos, 0.2f, Size);
				break;
			case BowType::IceBow:
				Size = { 1.5f, 1.5f, 1.5f };
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::ICEARROW_PULSE, &_pulsepos, 0.2f, Size);
				break;
			case BowType::EvilHeadBow:
				Size = { 2.f, 2.2f, 2.f };
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::EVILHEAD_PULSE, &_pulsepos, 0.5f, Size);
				break;
			case BowType::WindBow:
				Size = { 1.f, 1.f, 1.f };
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::WIND_PULSE, &_pulsepos, 0.3f, Size);
				Size = { 1.f, 1.f, 1.f };
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::WIND_CHARGING, &_pulsepos, 0.6f, Size);
				break;
			}
			
		}
	}
}

void Bow::CreateChargingArrow(const _float& _DT)
{
	POINT MousePoint{ 0, 0 };
	GetCursorPos(&MousePoint);
	ScreenToClient(hWnd, &MousePoint);

	_vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
	_vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

	_vec2 dir2D = mousePos - screenCenter;
	D3DXVec2Normalize(&dir2D, &dir2D);

	float angle = atan2f(dir2D.y, dir2D.x);

	float radius = 1.8f;

	float offsetX = cosf(angle) * radius;
	float offsetY = sinf(angle) * radius;

	_arrowPos = { _playerPos->x + offsetX , _playerPos->y, _playerPos->z - offsetY };

	_vec2 side = { -dir2D.y, dir2D.x };
	D3DXVec2Normalize(&side, &side);
	_vec3 rightPos = _arrowPos;
	_vec3 leftPos = _arrowPos;

	MakeArrow(_arrowPos, dir2D, true);

	_attackDelay = 0.f;
}

void Bow::CreateChargingEffect(const _float& _DT)
{
	bool mouseLB = KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80;
	_attackDelay += _DT;

	POINT MousePoint{ 0, 0 };
	GetCursorPos(&MousePoint);
	ScreenToClient(hWnd, &MousePoint);

	_vec2 mousePos = { (float)MousePoint.x, (float)MousePoint.y };
	_vec2 screenCenter = { WINCX * 0.5f, WINCY * 0.5f };

	_vec2 dir2D = mousePos - screenCenter;
	D3DXVec2Normalize(&dir2D, &dir2D);

	float angle = atan2f(dir2D.y, dir2D.x);

	float radius = 1.f;
	if (_type == BowType::FairyBow) radius = 1.6f;
	else if (_type == BowType::IceBow) radius = 1.6f;
	else if (_type == BowType::EvilHeadBow) radius = 1.0f;
	else if (_type == BowType::WindBow) radius = 1.6f;

	float offsetX = cosf(angle) * radius;
	float offsetY = sinf(angle) * radius;

	_pulsepos = { _playerPos->x + offsetX , _playerPos->y, _playerPos->z - offsetY };

	if (_Charging == 1)
	{
		if (_ChargingTime > 1.f)
		{
			// 이펙트
			_vec3 Size = { 1.5f, 1.5f, 1.5f };
			switch (_type)
			{
			case BowType::FairyBow:
				PLAY_PLAYER_EFFECT(PLAYER_SKILL::FAIRY_CHARGING, &_pulsepos, 0.2f, Size);
				break;
			case BowType::IceBow:
				PLAY_PLAYER_EFFECT(PLAYER_SKILL::ICE_CHARGING, &_pulsepos, 0.2f, Size);
				break;
			case BowType::EvilHeadBow:
				break;
			case BowType::WindBow:
				Size = { 1.f, 1.f, 1.f };
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::WIND_PULSE, &_pulsepos, 0.3f, Size);
				Size = { 1.f, 1.f, 1.f };
				PLAY_PLAYER_EFFECT_ONCE(PLAYER_SKILL::WIND_CHARGING, &_pulsepos, 0.6f, Size);
				break;
			}
		}
	}

}

void Bow::Late_Ready()
{
	switch (_type) {
	case BowType::FairyBow:
		_Stat.bowLv = 1;
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 987654321;
		_Stat.curArrow = 987654321;
		_Stat.range = 10.f;
		_Stat.delay = 0.6f;
		break;
	case BowType::IceBow:
		_Stat.bowLv = 1;
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 180;
		_Stat.curArrow = 180;
		_Stat.range = 10.f;
		_Stat.delay = 0.6f;
		break;
	case BowType::EvilHeadBow:
		_Stat.bowLv = 1;
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 150;
		_Stat.curArrow = 150;
		_Stat.range = 10.f;
		_Stat.delay = 0.6f;
		break;
	case BowType::WindBow:
		_Stat.bowLv = 1;
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 180;
		_Stat.curArrow = 180;
		_Stat.range = 10.f;
		_Stat.delay = 0.6f;
		break;
	}
	Player* player = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player"));
	PSTATUS* playerStatus = player->Get_Status();

	// 최대 화살 수
	_Stat.maxArrow *= playerStatus->maxBowRatio;
	_Stat.minAtk += playerStatus->atk;
	_Stat.maxAtk += playerStatus->atk;
}

void Bow::MakeArrow(_vec3 pos, _vec2 arrowDir, bool charging)
{
	_arrowPos = pos;

	std::random_device rd;
	std::uniform_int_distribution<int> distribution(0, 100);

	int arrowAtk = distribution(rd) % (_Stat.maxAtk - _Stat.minAtk) + _Stat.minAtk;

	GameObject* arrow = nullptr;

	if (charging) arrow = Arrow::Create(GRPDEV, _type, 3, arrowAtk, &_arrowPos, arrowDir);
	else arrow = Arrow::Create(GRPDEV, _type, _Stat.bowLv, arrowAtk, &_arrowPos, arrowDir);

	TCHAR arrowTag[128] = L"";
	wsprintfW(arrowTag, L"PlayerArrow_%d", _arrowCount++);

	arrow->Set_ObjectTag(arrowTag);
	arrow->Set_ObjectType(GAMEOBJECT_TYPE::OBJECT_PLAYER);
	arrow->Set_ObjectTag(L"PlayerArrow");

	SceneManager::GetInstance()->Get_CurrentScene()->Get_Layer(LAYER_TYPE::LAYER_DYNAMIC_OBJECT)->Add_GameObject(arrow);
}

Bow* Bow::Create(LPDIRECT3DDEVICE9 _GRPDEV)
{
	Bow* BOW = new Bow(_GRPDEV);
	if (FAILED(BOW->Ready_GameObject())) {
		MSG_BOX("Cannot Create BOW.");
		Safe_Release(BOW);
		return nullptr;
	}
	return BOW;
}

VOID Bow::Free()
{
	GameObject::Free();
}
