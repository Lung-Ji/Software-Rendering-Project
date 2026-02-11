#include "../Include/PCH.h"
#include "Bow.h"

Bow::Bow(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Bow::Bow(const GameObject& _RHS) : GameObject(_RHS) {}
Bow::~Bow() {}

HRESULT Bow::Ready_GameObject()
{
	if (FAILED(Component_Initialize())) return E_FAIL;

	CameraObject* Camera = dynamic_cast<CameraObject*>(SceneManager::GetInstance()->Get_CurrentScene()->
		Get_GameObject(L"Camera"));

	_cameraDir = *(Camera->Get_EyeVec()) - *(Camera->Get_AtVec());
	_vec3 planeDir = { 0.f, 1.f, 0.f };

	_cameraAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&_cameraDir, &_cameraDir), D3DXVec3Normalize(&planeDir, &planeDir)));
	_cameraAngle = _cameraAngle / D3DX_PI * 180.f;

	_alphaRatio = 0.f;

	Component_Transform->Set_Scale({ 1.f, 1.f, 1.f });

	switch (_type) {
	case BowType::FairyBow:
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 987654321;
		_Stat.curArrow = 987654321;
		_Stat.bowLv = 1;
		break;
	case BowType::IceBow:
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 180;
		_Stat.curArrow = 180;
		_Stat.bowLv = 1;
		break;
	case BowType::EvilHeadBow:
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 150;
		_Stat.curArrow = 150;
		_Stat.bowLv = 1;
		break;
	case BowType::WindBow:
		_Stat.minAtk = 20;
		_Stat.maxAtk = 23;
		_Stat.maxArrow = 180;
		_Stat.curArrow = 180;
		_Stat.bowLv = 1;
		break;
	}

	Player* player = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player"));
	PSTATUS* _playerStatus = player->Get_Status();

	return S_OK;
}

INT Bow::Update_GameObject(const _float& _DT)
{
	if (_isEquip) {
		GameObject::Update_GameObject(_DT);
		RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

		if (_isDestroied) return -1;

		Player* player = dynamic_cast<Player*>(SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(L"Player"));
		PSTATUS* playerStatus = player->Get_Status();

		// 최대 화살 수
		_Stat.maxArrow	*= playerStatus->maxBowRatio;
		_Stat.minAtk	+= playerStatus->atk;
		_Stat.maxAtk	+= playerStatus->atk;

		float alphaSpeed = 3.f;

		bool mouseLB = KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80;
		if (mouseLB) {
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
	default:
		wsprintfW(FileName, L"FairyBow.png");
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
