#include "Tile.h"
#include "../Include/PCH.h"
#include <iostream>
#include <fstream>
const _tchar* m_pTileName[128];
Tile::Tile(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_bTileCheck(true), m_pTexture(nullptr), m_vXZ(0,0),
m_pTransform(nullptr), m_pBuffer(nullptr), m_pTileName(nullptr),
m_eMode(TILEMODE_CHANGE::MODE_END),m_eTile(Engine::TILE_SIDE::TILE_END) {}
Tile::Tile(const GameObject& _RHS) : GameObject(_RHS) {}
Tile::~Tile() {}

HRESULT Tile::Ready_GameObject() {

	if (FAILED(Component_Initialize())) return E_FAIL;
	wstring path = L"../../../Tile";
	BITMAPINFOHEADER InfoHeader{};
	BITMAPFILEHEADER fileHeader{};
	_wfinddata64_t Data;

	INT Result = 1;

	wstring STRUNI = path + L"/*.*";

	intptr_t Handle = _wfindfirst64(STRUNI.c_str(), &Data);

	if (Handle == -1)	return E_FAIL;
	while (Result != -1) 
	{
		wstring WideRootPath = path + L"/" + Data.name;
		wstring* KEY = new wstring(Data.name);

		ifstream fa(WideRootPath, ios_base::binary);
		ImageFile imf = {};

		imf.wstr = KEY;
		fa.seekg(16, ios::beg);
		unsigned char sizeBuf[8];
		fa.read(reinterpret_cast<char*>(sizeBuf), 8);
		
		imf.vSize.x = (_float)(sizeBuf[0] << 24| sizeBuf[1] << 16 |
					  sizeBuf[2] << 8 | sizeBuf[3]);

		imf.vSize.y = (_float)(sizeBuf[0] << 24 | sizeBuf[1] << 16 |
					  sizeBuf[2] << 8  | sizeBuf[3]);

		m_vecImage.push_back(imf);
		Result = _wfindnext64(Handle, &Data);
		fa.close();
	}
	_findclose(Handle);
	
	return S_OK;
}
INT	Tile::Update_GameObject(const _float& _DT) {

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return GameObject::Update_GameObject(_DT);

}
VOID Tile::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
	
	Mode_Change();  //타일 큐브 스왑용 O : 큐브, P : 타일
	Imgui();
	Check_TilePoint();
	
}

VOID Tile::Render_GameObject()
{
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	GRPDEV->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);
	GRPDEV->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//GRPDEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	
	m_pTexture->Set_Texture(m_pTileName);


	m_pBuffer->Render_Buffer();
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
}

void Tile::Mode_Change()
{
	if (KeyManager::GetInstance()->Get_KeyState(DIK_O))
	{
		m_eMode = TILEMODE_CHANGE::MODE_CUBE;
	}
	if (KeyManager::GetInstance()->Get_KeyState(DIK_P))
	{
		m_eMode = TILEMODE_CHANGE::MODE_TILE;
	}
	if (KeyManager::GetInstance()->Get_KeyState(DIK_F9))
	{
		m_eMode = TILEMODE_CHANGE::MODE_END;
	}
}

void Tile::Imgui()
{
	bool Scale(true);
	
	
	//ImGui::SetNextWindowPos({ 650,300 });
	ImGui::SetNextWindowSize({ 600,600 });
	ImGui::Begin("Editor",NULL,ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
				cout << ("Save clicked\n");
			ImGui::Separator(); //구분줄
			if (ImGui::MenuItem("Open"))
				cout << ("Open clicked\n");			
			ImGui::EndMenu();
		}
		
		ImGui::EndMenuBar();
	}
	Imgui_Setting();

	
	ImGui::End();
}

void Tile::Imgui_Setting()
{
	_vec3 vScale = *m_pTransform->Get_Scale();
	_vec3 vRotation = *m_pTransform->Get_Rotation();
	_float fMin(0.0f), fMax(10);
	_float fRotation(0.f), fRotationMax(180);
	if (!ImGui::CollapsingHeader("Setting"))
		return;
	else
	{
		ImGui::Text("Scale"); //텍스트 
		ImGui::SameLine(50.f, 0.f);//텍스트 오른쪽에
		ImGui::SliderFloat3("##1", vScale, fMin, fMax); //scale 출력
		m_pTransform->Set_Scale(vScale);

		ImGui::Text("Rotation");
		ImGui::SameLine(100.f, 0.f);
		ImGui::SliderFloat3("##2", vRotation, fRotation, fRotationMax);
		m_pTransform->Set_Rotation(vRotation);

		Imgui_Image();
	}

	
}

void Tile::Imgui_Image()
{
	_bool bSetTexture = false;
	_int  iChoice(0);
	const char* cTile[] = { "0","1","2","3","4","5" };
	ImGui::Text("IMAGE");
	ImGui::SameLine(50.f, 0.f);
	//기본 버튼 색
	ImGui::PushStyleColor(ImGuiCol_Button, D3DXCOLOR(0.0f, 0.f, 0.f, 1.f));
	//마우스 올라갔을때 버튼색
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
	//클릭했을 때 버튼 색
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5f, 0.7f, 0.7f));
	ImGui::Button("First");
	ImGui::PopStyleColor(3);	

	if (!ImGui::CollapsingHeader("Tiles"))
		return;

	ImGui::Text("Display Choice");
	ImGui::SameLine(140.0f, 0.f);
	bSetTexture = ImGui::Combo("##Choice", &iChoice, cTile, sizeof(char)*6);
	if (bSetTexture)
		cout << "Display Coice " << iChoice << endl;


	ImGui::Text("Tile Choice");
	ImVec2 chidSize = ImVec2(0.f, ImGui::GetFrameHeightWithSpacing() * 10);
	ImGuiID id = ImGui::GetCurrentWindow()->GetID("##Tiles");
	ImGui::BeginChildEx("##Tiles",  id, chidSize, ImGuiChildFlags_None,ImGuiWindowFlags_HorizontalScrollbar);
	//아
	_int nCount = 0;
	for (size_t i = 0; i < m_vecImage.size(); i++)
	{
		_vec2 size = m_vecImage[i].vSize;
		char scat[512] = "##";
		strncat_s(scat, (char*)m_vecImage[i].wstr, sizeof(char) * 512);
		
		if (ImGui::ImageButton(scat,
			m_pTexture->Find_Texture((m_vecImage[i].wstr)->c_str()),
			ImVec2(size.x * 0.1f, size.y * 0.1f), ImVec2(0.f, 0.f), ImVec2(1.f, 1.f)
			, ImVec4(0, 0, 0, 0)))
		{
			m_pTileName = m_vecImage[i].wstr->c_str();
		}
		nCount++;
		if (nCount < 3)
			ImGui::SameLine();
		else nCount = 0;
	}
	
	ImGui::EndChild();
}


HRESULT Tile::Component_Initialize() {

	m_pBuffer		   = ADD_COMPONENT_TILE; 
	m_pTransform	   = ADD_COMPONENT_TRANSFORM;
	m_pTexture		   = ADD_COMPONENT_TEXTURE;
	m_pTexture->Import_TextureFromFolder(L"../../Resource/Tile");

	
	return S_OK;
}
_bool Tile::Check_Bottom(_vec3* vOrigin)
{
	if (m_eMode == TILEMODE_CHANGE::MODE_END)
		return 0;
	_vec3 vCheckVertex;
	_float fx,fz;
	_int iDst(0);
	Component* pTransform = SceneManager::GetInstance()->Get_GameObject(L"Terrain")->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TERRAIN);
	Buffer* pBuffer = dynamic_cast<Buffer*>(pTransform);
	
	for (auto& iter : TileManager::GetInstance()->Get_TileList(m_eMode))
	{	
		switch (m_eMode)
		{
		case TILEMODE_CHANGE::MODE_TILE:
			if (dynamic_cast<CXZTile*>(iter) != nullptr)
			iDst = dynamic_cast<CXZTile*>(iter)->Get_TileNumber();
			break;
		case TILEMODE_CHANGE::MODE_CUBE:
			if(dynamic_cast<CubeTile*>(iter) != nullptr)
			iDst = dynamic_cast<CubeTile*>(iter)->Get_TileNumber();
			break;
		}
		//안겹치게 예외처리요 근데 정육면체 기준
		_int iMiddle	  = (_int) (vOrigin->z  * VTXCNTX + vOrigin->x	  );
		_int iCheckR	  = (_int) (vOrigin->z  * VTXCNTX + vOrigin->x - 1);
		_int iCheckL	  = (_int) (vOrigin->z  * VTXCNTX + vOrigin->x + 1);
		_int iCheckT      = (_int)((vOrigin->z + 1) * VTXCNTX + vOrigin->x);
		_int iCheckB      = (_int)((vOrigin->z - 1) * VTXCNTX + vOrigin->x);
		_int iCheckLT	  = (_int)((vOrigin->z + 1) * VTXCNTX + vOrigin->x - 1);
		_int iCheckRT	  = (_int)((vOrigin->z + 1) * VTXCNTX + vOrigin->x + 1);
		_int iCheckLB	  = (_int)((vOrigin->z - 1) * VTXCNTX + vOrigin->x - 1);
		_int iCheckRB	  = (_int)((vOrigin->z - 1) * VTXCNTX + vOrigin->x + 1);

		if (iDst == iCheckLT || iDst == iCheckRT || iDst == iCheckLB || iDst == iCheckRB || iDst == iCheckR || iDst == iCheckL || iDst == iCheckT || iDst == iCheckB)
		{
			switch (m_eMode)
			{
			case TILEMODE_CHANGE::MODE_TILE:
				vCheckVertex = *(pBuffer->Get_BufferPos(dynamic_cast<CXZTile*>(iter)->Get_TileNumber()));
				break;
			case TILEMODE_CHANGE::MODE_CUBE:
				vCheckVertex = *(pBuffer->Get_BufferPos(dynamic_cast<CubeTile*>(iter)->Get_TileNumber()));
				break;
			}
			fx = fabsf(vCheckVertex.x - floor(vOrigin->x));
			fz = fabsf(vCheckVertex.z - floor(vOrigin->z));
			
			if (iMiddle == iDst)
				return 0;

			if (fx <= 1 || fz<=1)
				return 1;
		}
	}	
		return 0;
}
void Tile::Check_TilePoint()
{
	//응애
	_matrix proj, vWorldInvese, matView, InversView;
	D3DVIEWPORT9 vp;
	_vec3 vPlayerPos, vRight, vLook, vOrigin, vDirection, vMousePos;
	POINT pt;
	GRPDEV->GetViewport(&vp);
	GRPDEV->GetTransform(D3DTS_PROJECTION, &proj);
	GRPDEV->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&InversView, 0, &matView);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	//픽킹 계산 :<
	Component* ComBuff = SceneManager::GetInstance()->Get_GameObject(L"Terrain")->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TERRAIN);
	Buffer* pBuffer = dynamic_cast<Buffer*>(ComBuff);
	
	Component* ComTransform = SceneManager::GetInstance()->Get_GameObject(L"Terrain")->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM);
	Transform* pTransform = dynamic_cast<Transform*>(ComTransform);

	D3DXMatrixIdentity(&vWorldInvese);
	memcpy(&vWorldInvese, pTransform->Get_World(), sizeof(_matrix));
	D3DXMatrixInverse(&vWorldInvese, 0, &vWorldInvese);

	vMousePos.x = (((2.0f  * pt.x) / vp.Width)  - 1.0f) / proj(0, 0);
	vMousePos.y = (((-2.0f * pt.y) / vp.Height) + 1.0f) / proj(1, 1);
	vMousePos.z = 1.f;
	vOrigin = { 0.f, 0.f ,0.f };
	vDirection = vMousePos - vOrigin;
	D3DXVec3TransformCoord(&vOrigin, &vOrigin, &InversView);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &InversView);

	D3DXVec3TransformCoord(&vOrigin, &vOrigin, &vWorldInvese);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &vWorldInvese);
	D3DXVec3Normalize(&vDirection, &vDirection);

	//지형 전체기준으로 광선 쏴서 어느 위치에 놓을지 결정
	_vec3 vMouseCheck, vMouseBlockCheck{}, vMouseTest;
	_float fu(0), fv(0), ft(0);
	if (D3DXIntersectTri(pBuffer->Get_BufferPos((VTXCNTZ - 1) * VTXCNTX), pBuffer->Get_BufferPos(0), pBuffer->Get_BufferPos((VTXCNTZ-1) * VTXCNTX + VTXCNTX -1), &vOrigin, &vDirection, &fu, &fv, &ft))
	{
		vMouseCheck = vOrigin + vDirection * ft;
		
	}
	if (D3DXIntersectTri(pBuffer->Get_BufferPos(0), pBuffer->Get_BufferPos((VTXCNTZ-1) * VTXCNTX + VTXCNTX-1), pBuffer->Get_BufferPos(VTXCNTX-1), &vOrigin, &vDirection, &fu, &fv, &ft))
	{
		vMouseCheck = vOrigin + vDirection * ft;
	}
	vMouseCheck.x = floor(vMouseCheck.x);
	vMouseCheck.y = floor(vMouseCheck.y);
	vMouseCheck.z = floor(vMouseCheck.z);
	_vec3 vPos, vTileLocalPos[8];
	_matrix InverseWorld, CheckWorld;
	_float	ftCheck(VTXCNTX - 1);
	_int    iCheckZero(0);
	//설치 되어있는 블럭 충돌 비교
	{
		if (m_eMode != TILEMODE_CHANGE::MODE_END)
		{
			for (auto iter : TileManager::GetInstance()->Get_TileList(m_eMode))
			{
				//흠
				dynamic_cast<Transform*>(iter->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Info(INFO_POS, &vPos);
				memcpy(&InverseWorld, dynamic_cast<Transform*>(iter->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_World(), sizeof(_matrix));
				vTileLocalPos[0] = { -1.f, 0.f, -1.f }; //좌하단 y+ 기준
				vTileLocalPos[1] = { 1.f, 0.f, -1.f }; //우하단 y+ 기준
				vTileLocalPos[2] = { -1.f, 0.f,  1.f }; //좌상단 y+ 기준
				vTileLocalPos[3] = { 1.f, 0.f,  1.f }; //우상단 y+ 기준

				for (int i = 0; i < 4; ++i)
					D3DXVec3TransformCoord(&vTileLocalPos[i], &vTileLocalPos[i], &InverseWorld);

				if (D3DXIntersectTri(&vTileLocalPos[0], &vTileLocalPos[1], &vTileLocalPos[2], &vOrigin, &vDirection, &fu, &fv, &ft) ||
					D3DXIntersectTri(&vTileLocalPos[3], &vTileLocalPos[2], &vTileLocalPos[1], &vOrigin, &vDirection, &fu, &fv, &ft))
				{
					vMouseCheck = vOrigin + vDirection * ft;
					if (ftCheck > ft)
					{
						//Check_Distance(vMouseCheck); //5방향 평면 비교 잠시 폐기

						m_eTile = TILE_SIDE::TILE_OTHER;
						vMouseBlockCheck = vMouseCheck;
						ftCheck = ft;
					}
				}
			}
		}
	}
		// 보정
		vMouseCheck.x = floor(vMouseCheck.x);
		vMouseCheck.y = floor(vMouseCheck.y);
		vMouseCheck.z = floor(vMouseCheck.z);

		if (vMouseCheck.y < 0)
			vMouseCheck.y = 0;

		if (vMouseCheck.x < 1)
			vMouseCheck.x = 1;

		if (vMouseCheck.z < 1)
			vMouseCheck.z = 1;

		if (Check_Bottom(&vMouseCheck))
		{
			m_bTileCheck = false;
		}
		m_pTransform->Set_Pos(vMouseCheck.x, vMouseCheck.y, vMouseCheck.z);
	   //좌클릭시 블럭 설치

		if (m_bTileCheck)
		{
			if (KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80)
			{
				////정육면체말고 다른 타일 깔고싶으면 클래스 만들어서 바꾸면됨
				GameObject* pTile = nullptr;
				switch (m_eMode)
				{
				case TILEMODE_CHANGE::MODE_TILE:
					pTile = CXZTile::Create(GRPDEV, m_eTile,m_pTileName);
					break;
				case TILEMODE_CHANGE::MODE_CUBE:
					pTile = CubeTile::Create(GRPDEV);
					break;
				}
				if (pTile != nullptr)
				{
					GRPDEV->AddRef();
					switch (m_eMode)
					{
					case TILEMODE_CHANGE::MODE_TILE:
						dynamic_cast<CXZTile*>(pTile)->Set_TileNumber((_int)vMouseCheck.z * VTXCNTX + (_int)vMouseCheck.x);
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(*m_pTransform->Get_Scale());
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(*m_pTransform->Get_Rotation());

						TileManager::GetInstance()->Add_Tile(pTile, vMouseCheck, m_eMode);
						
						break;
					case TILEMODE_CHANGE::MODE_CUBE:
						dynamic_cast<CubeTile*>(pTile)->Set_TileNumber((_int)vMouseCheck.z * VTXCNTX + (_int)vMouseCheck.x);
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(*m_pTransform->Get_Scale());
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(*m_pTransform->Get_Rotation());
						TileManager::GetInstance()->Add_Tile(pTile, vMouseCheck, m_eMode);
						break;
					}	
	
				}
				else
					Safe_Release(pTile);
			}
		}
		//우클릭 삭제
		if (KeyManager::GetInstance()->Get_MouseState(DIM_RB) & 0x80)
			TileManager::GetInstance()->Delete_Tile(vMouseCheck, vOrigin, vDirection);

		
		m_bTileCheck= true;
}

void Tile::Check_Distance(_vec3 vMouse)
{
	_float fRight, fLeft, fFront, fBack, fx, fz,fLength;
	fx = floor(vMouse.x);
	fz = floor(vMouse.z);

	_vec3 vRight{ fx + 1,0,fz }, vLeft{ fx - 1,0,fz }, vFront(fx, 0, fz - 1), vBack(fx, 0, fz + 1), vOriginMouse{ vMouse.x,0,vMouse.y };

	//D3DXVec3TransformCoord(&vRight,&)
	fLength = D3DXVec3Length(&vOriginMouse);

	fRight = fabsf(D3DXVec3Length(&vRight) - fLength); //1
	fLeft  = fabsf(D3DXVec3Length(&vLeft)  - fLength); //2
	fFront = fabsf(D3DXVec3Length(&vFront) - fLength); //3
	fBack  = fabsf(D3DXVec3Length(&vBack)  - fLength); //4

	_float Src;
	Src = min(min(fRight, fLeft), min(fFront, fBack));

	 if (Src == fRight)
		 m_eTile = TILE_SIDE::TILE_RIGHT;
	 else if (Src == fLeft)
		 m_eTile = TILE_SIDE::TILE_LEFT;
	 else if (Src == fFront)
		 m_eTile = TILE_SIDE::TILE_FRONT;
	 else if (Src == fBack)
		 m_eTile = TILE_SIDE::TILE_BACK;
}

Tile* Tile::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Tile* pTile = new Tile(_GRPDEV);

	if (FAILED(pTile->Ready_GameObject())) {
		MSG_BOX("Cannot Create Tile.");
		Safe_Release(pTile);
		return nullptr;
	}
	return pTile;
}
VOID Tile::Free() {
	for (auto& iter : m_vecImage)
		Safe_Delete(iter.wstr);

	GameObject::Free();
}