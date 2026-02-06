#include "../Include/PCH.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
const _tchar* m_pTileName[128];
Tile::Tile(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_pTileState(nullptr),m_bTileCheck(true), m_pTexture(nullptr),m_pTileFront(nullptr),m_pTileLeft(nullptr),m_pTileRight(nullptr)
, m_eTileState(TILE_STATE::STATE_END),m_pTileBack(nullptr), m_fHeight(0.f), m_pTransform(nullptr), m_pBuffer(nullptr), m_pTileName(nullptr), m_bMouseClick(false), m_eMode(TILEMODE_CHANGE::MODE_END),m_eTile(Engine::TILE_SIDE::TILE_END)
{
	m_vOriginal = {};
}
Tile::Tile(const GameObject& _RHS) : GameObject(_RHS) {}
Tile::~Tile() {}
HRESULT Tile::Component_Initialize() {

	m_pBuffer = ADD_COMPONENT_TILE;
	m_pTileLeft = ADD_COMPONENT_TILELEFT;
	m_pTileRight = ADD_COMPONENT_TILERIGHT;
	m_pTileBack = ADD_COMPONENT_TILEBACK;
	m_pTileFront = ADD_COMPONENT_TILEFRONT;
	m_pTransform = ADD_COMPONENT_TRANSFORM;
	m_pTexture = ADD_COMPONENT_TEXTURE;

	m_pTexture->Import_TextureFromFolder(L"../../Tile/Stage1");
	m_pTexture->Import_TextureFromFolder(L"../../Tile/AnimationObject");
	m_vecName[TILE_STATE::STATE_NORMAL].push_back(L"../../Tile/Stage1");
	m_vecName[TILE_STATE::STATE_ANIMATION].push_back(L"../../Tile/AnimationObject");
  
	return S_OK;
}
HRESULT Tile::Ready_GameObject() {

	if (FAILED(Component_Initialize())) return E_FAIL;
	
	Load_Image(L"../../Tile/Stage1", TILE_STATE::STATE_NORMAL);
	Load_Image(L"../../Tile/AnimationObject", TILE_STATE::STATE_ANIMATION);

	for (size_t i = 0; i < TILE_STATE::STATE_END; ++i)
	{
		for (auto& iter : m_vecImage[i])
		{
			iter.vSize.x / 128;
			iter.vSize.y / 128;
		}
	}
	return S_OK;
}
INT	Tile::Update_GameObject(const _float& _DT) {

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_TILE, this);
	return GameObject::Update_GameObject(_DT);


}
VOID Tile::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
	if (KEY_DOWN(DIK_F8))
	{
		TileManager::GetInstance()->Save_Tile(hWnd);
	}
	if (KEY_DOWN(DIK_F7))
	{
		LoadFile();
	}

	Mode_Change();  //타일 큐브 스왑용 O : 큐브, P : 타일
	Imgui();
	auto& io = ImGui::GetIO(); //마우스 ui에서 사용중이면 리턴
	if (io.WantCaptureMouse) return;
	Check_TilePoint();
}

VOID Tile::Render_GameObject()
{
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	
	if (m_eMode == TILEMODE_CHANGE::MODE_END)
		m_pTexture->Set_Texture(nullptr);
	else
		m_pTexture->Set_Texture(m_pTileName);

	switch (m_eTile)
	{
	case TILE_SIDE::TILE_FRONT:
		m_pTileFront->Render_Buffer();
		break;
	case TILE_SIDE::TILE_RIGHT:
		m_pTileRight->Render_Buffer();
		break;
	case TILE_SIDE::TILE_LEFT:
		m_pTileLeft->Render_Buffer();
		break;
	case TILE_SIDE::TILE_OTHER:
		m_pBuffer->Render_Buffer();
		break;
	}
}
void Tile::Mode_Change()
{
	if (KeyManager::GetInstance()->Get_KeyState(DIK_F9)) m_eMode = TILEMODE_CHANGE::MODE_END;
}
void Tile::Imgui()
{
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

		ImGui::Begin("Mode Changer", NULL, ImGuiWindowFlags_MenuBar);

		ImGui::SetNextWindowSize({ 800,300 });

		Imgui_ModeChanger();
	ImGui::End();
}
void Tile::Imgui_Setting()
{
	_vec3 vScale = *m_pTransform->Get_Scale();
	_vec3 vRotation = *m_pTransform->Get_Rotation();
	_vec3 vPos = {};
	_float fMin(0.0f), fMax(100), fHeightMin(0.f), fHeightMax(10.f);
	_float fRotation(-180.f), fRotationMax(180);
	_vec3 vSca = { 1.f,1.f,1.f };
	_vec3 vRot = { 0.f,0.f,0.f };
	
	if (TILE_SIDE::TILE_OTHER != m_eTile) vRotation.x = 65.f;
	else vRotation.x = 0;
	if (!ImGui::CollapsingHeader("Setting"))
		return;
	else
	{
		ImGui::Text("Scale"); //텍스트 
		ImGui::SameLine(50.f, 0.f);//텍스트 오른쪽에
		ImGui::SliderFloat3("##1", vScale, fMin, fMax); //scale 출력 ##하면 글자 다음으로 출력됨
		m_pTransform->Set_Scale(vScale);


		ImGui::Text("Rotation");
		ImGui::SameLine(100.f, 0.f);
		ImGui::SliderFloat3("##2", vRotation, fRotation, fRotationMax);
		m_pTransform->Set_Rotation(vRotation);

		//ImGui::Text("vPos");
		//ImGui::SameLine(100.f, 0.f);

		//ImGui::SliderFloat3("##3", m_vOriginal, fHeightMin, fHeightMax);
		//if (ImGui::Button("Up"))
		//{
	
		ImGui::PushStyleColor(ImGuiCol_Button, D3DXCOLOR(0.0f, 0.f, 0.f, 1.f));
		//마우스 올라갔을때 버튼색
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
		//클릭했을 때 버튼 색
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5f, 0.7f, 0.7f));
		if (ImGui::Button("Reset Option"))
		{
			m_pTransform->Set_Scale(vSca);
			m_pTransform->Set_Rotation(vRot);
		}
		ImGui::PopStyleColor(3);
		
		Imgui_Image("Stage1_Tile",TILE_STATE::STATE_NORMAL);
		Imgui_Image("Stage1_AinmationObject", TILE_STATE::STATE_ANIMATION);
	}

}
void Tile::Imgui_Image(const char* tName, TILE_STATE eid)
{
	_bool bSetTexture = false;
	if (!ImGui::CollapsingHeader(tName)) //그냥 타이틀 이름
		return;

	_int nCount = 0;
	for (size_t i = 0; i < m_vecImage[eid].size(); i++)
	{
		_vec2 size = m_vecImage[eid][i].vSize;
		char scat[256] = "##";
		strncat_s(scat, (char*)m_vecImage[eid][i].wstr, sizeof(char) * 256);

		ImGui::PushID(i); //버튼 중복 방지용

		if (ImGui::ImageButton(scat,
			m_pTexture->Find_Texture((m_vecImage[eid][i].wstr)->c_str()),
			ImVec2(size.x * 0.1f, size.y * 0.1f), ImVec2(0.f, 0.f), ImVec2(1.f, 1.f)
			, ImVec4(0, 0, 0, 0))) //이미지 클릭 관련해서 true false 반환
		{
			m_pTileName = m_vecImage[eid][i].wstr->c_str();
			m_eTileState = eid;
			m_pPathName = m_vecName[eid].front();
			
		}
		ImGui::PopID();
		nCount++;
		if (nCount < 3)
			ImGui::SameLine();
		else nCount = 0;
	}
	
}
void Tile::Imgui_ModeChanger()
{
	_bool bSetTexture = false;
	_int  iChoice(0);
	static const char* cTile[] = { "TILE_FRONT","TILE_RIGHT","TILE_LEFT"};
	static const char* cTileStater[] = { "NORMAL", "COLLISION", "TRIGGER" };;
	static const char* cSelect_Tile = nullptr;
	static const char* cSelect_State = nullptr;
	if (!ImGui::CollapsingHeader("TILEMode"))
		return;
	else
	{
		//////////////////MODE_END////////////////////////
		{
			ImGui::PushStyleColor(ImGuiCol_Button, D3DXCOLOR(0.0f, 0.f, 0.f, 1.f));
			//마우스 올라갔을때 버튼색
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			//클릭했을 때 버튼 색
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5f, 0.7f, 0.7f));

			if (ImGui::Button("Mode_END"))
			{
				m_eMode = TILEMODE_CHANGE::MODE_END;
				m_eTile = TILE_SIDE::TILE_END;
			}
			ImGui::PopStyleColor(3);
		}

		//////////////////MODE_TILE////////////////////////
		{

			ImGui::PushStyleColor(ImGuiCol_Button, D3DXCOLOR(0.0f, 0.f, 0.f, 1.f));
			//마우스 올라갔을때 버튼색
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			//클릭했을 때 버튼 색
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5f, 0.7f, 0.7f));
			if (ImGui::Button("Mode_TileDefault"))
			{
				m_eMode = TILEMODE_CHANGE::MODE_TILE;
				m_eTile = TILE_SIDE::TILE_OTHER;
			}
			ImGui::PopStyleColor(3);
		}

		//////////////////MODE_CUBE////////////////////////
		{
			ImGui::PushStyleColor(ImGuiCol_Button, D3DXCOLOR(0.0f, 0.f, 0.f, 1.f));
			//마우스 올라갔을때 버튼색
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			//클릭했을 때 버튼 색
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5f, 0.7f, 0.7f));
			if (ImGui::Button("Mode_CUBE"))
				m_eMode = TILEMODE_CHANGE::MODE_CUBE;
			ImGui::PopStyleColor(3);
		}

		//////////////////MODE_OBJECT//////////////////////
		{
			ImGui::PushStyleColor(ImGuiCol_Button, D3DXCOLOR(0.0f, 0.f, 0.f, 1.f));
			//마우스 올라갔을때 버튼색
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			//클릭했을 때 버튼 색
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.5f, 0.7f, 0.7f));
			ImGui::Button("Mode_Object");
			ImGui::PopStyleColor(3);

			ImGui::Text("TileMode_TIle");
			ImGui::SameLine(140.0f, 0.f);

			if (ImGui::BeginCombo("##Choice", cSelect_Tile))
			{
				for (_int i = 0; i < IM_ARRAYSIZE(cTile); i++)
				{
					_bool bSelect = (cSelect_Tile == cTile[i]);
					if (ImGui::Selectable(cTile[i], bSelect))
					{
						cSelect_Tile = cTile[i];
						if (cSelect_Tile == cTile[0]) m_eTile = TILE_SIDE::TILE_FRONT;
						else if (cSelect_Tile == cTile[1]) m_eTile = TILE_SIDE::TILE_RIGHT;
						else if (cSelect_Tile == cTile[2]) m_eTile = TILE_SIDE::TILE_LEFT;

						m_eMode = TILEMODE_CHANGE::MODE_OBJECT;
					}
					if (bSelect)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
		}

		//////////////////TILE_STATE///////////////////////
		{
			ImGui::Text("TileState");
			ImGui::SameLine(140.0f, 0.f);

			if (ImGui::BeginCombo("##State", cSelect_State))
			{
				for (_int i = 0; i < IM_ARRAYSIZE(cTileStater); i++)
				{
					_bool bSelect = (cSelect_State == cTileStater[i]);
					if (ImGui::Selectable(cTileStater[i], bSelect))
					{
						cSelect_State = cTileStater[i];
						if (cSelect_State == cTileStater[0])       m_eTileState = TILE_STATE::STATE_NORMAL;
						else if (cSelect_State == cTileStater[1])  m_eTileState = TILE_STATE::STATE_COLLISION;
						else if (cSelect_State == cTileStater[2])  m_eTileState = TILE_STATE::STATE_TRIGGER;
						
					}
					if (bSelect)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
		}
	}
}
HRESULT Tile::Load_Image(const _tchar* pName, TILE_STATE eid)
{
	wstring path = pName;
	BITMAPINFOHEADER InfoHeader{};
	BITMAPFILEHEADER fileHeader{};
	_wfinddata64_t Data;
	INT Result = 1;
	wstring STRUNI = path + L"/*.*";
	intptr_t Handle = _wfindfirst64(STRUNI.c_str(), &Data);
	if (Handle == -1)	return E_FAIL;
	while (Result != -1)
	{
		if (wcscmp(Data.name, L".") == 0 || wcscmp(Data.name, L"..") == 0)
		{
			Result = _wfindnext64(Handle, &Data);
			continue;
		}
		wstring WideRootPath = path + L"/" + Data.name;

		wstring* KEY = new wstring(Data.name);

		ifstream fa(WideRootPath, ios_base::binary);
		ImageFile imf = {};

		imf.wstr = KEY;
		fa.seekg(16, ios::beg);
		unsigned char sizeBuf[8];
		fa.read(reinterpret_cast<char*>(sizeBuf), 8);

		imf.vSize.x = (_float)(sizeBuf[0] << 24 | sizeBuf[1] << 16 |
			sizeBuf[2] << 8 | sizeBuf[3]);

		imf.vSize.y = (_float)(sizeBuf[0] << 24 | sizeBuf[1] << 16 |
			sizeBuf[2] << 8 | sizeBuf[3]);

		m_vecImage[eid].push_back(imf);
		Result = _wfindnext64(Handle, &Data);
		fa.close();
	}
	_findclose(Handle);
}
HRESULT Tile::LoadFile()
{
	HANDLE	hFile = CreateFile(L"../../Data/Tile.dat", // 파일 이름이 포함된 경로
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		OPEN_EXISTING,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MSG_BOX("로드 실패");
		return E_FAIL;
	}

	DWORD	dwByte(0);		// eof 역할
	_int             iTilenum = 0;
	TILE_SIDE        eTileSide = TILE_SIDE::TILE_END;
	TILE_STATE       eTileState = TILE_STATE::STATE_END;
	TILEMODE_CHANGE  eTileMode = TILEMODE_CHANGE::MODE_END;
	_tchar cTileName[128] = {};
	_vec3		     Info = {};
	_vec3			 Scale = {};
	_vec3			 Rotation = {};
	_tchar cPathName[128] = {};
	TileManager::GetInstance()->Render_TileList();
	while (true)
	{
		ReadFile(hFile, &Info,		 sizeof(_vec3),			  &dwByte, NULL);
		ReadFile(hFile, &iTilenum,   sizeof(_int),			  &dwByte, NULL);
		ReadFile(hFile, &eTileSide,  sizeof(TILE_SIDE),		  &dwByte, NULL);
		ReadFile(hFile, &eTileState, sizeof(TILE_STATE),	  &dwByte, NULL);
		ReadFile(hFile, &eTileMode,  sizeof(TILEMODE_CHANGE), &dwByte, NULL);
		ReadFile(hFile, &cTileName,  sizeof(_tchar) * 128,	  &dwByte, NULL);
		ReadFile(hFile, &Scale,		 sizeof(_vec3),			  &dwByte, NULL);
		ReadFile(hFile, &Rotation,   sizeof(_vec3),			  &dwByte, NULL);
		ReadFile(hFile, &cPathName, sizeof(_tchar) * 128,     &dwByte, NULL);

		if (0 == dwByte)
			break;

		GameObject* GOBJ = nullptr;
		GRPDEV->AddRef();
		GOBJ = CXZTile::Create(GRPDEV, eTileSide);
		GOBJ->Set_ObjectTag(L"CXZTile");

		dynamic_cast<TileInfo*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileAll(cPathName, cTileName, eTileSide, eTileState, eTileMode, iTilenum);
		dynamic_cast<Transform*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(Scale);
		dynamic_cast<Transform*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(Rotation);
		dynamic_cast<Transform*>(GOBJ->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Pos(Info);
		TileManager::GetInstance()->Load_TilePush(GOBJ, eTileMode);
	}

	MSG_BOX("로드 성공");
	CloseHandle(hFile);
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
			iDst = dynamic_cast<TileInfo*>(iter->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileNumber();
			break;
		case TILEMODE_CHANGE::MODE_CUBE:
			if(dynamic_cast<CubeTile*>(iter) != nullptr)
			iDst = dynamic_cast<CubeTile*>(iter)->Get_TileNumber();
			break;
		case  TILEMODE_CHANGE::MODE_OBJECT:
			if (dynamic_cast<CXZTile*>(iter) != nullptr)
			iDst = dynamic_cast<TileInfo*>(iter->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileNumber();
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
				vCheckVertex = *(pBuffer->Get_BufferPos(dynamic_cast<TileInfo*>(iter->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileNumber()));
				break;
			case TILEMODE_CHANGE::MODE_CUBE:
				vCheckVertex = *(pBuffer->Get_BufferPos(dynamic_cast<CubeTile*>(iter)->Get_TileNumber()));
				break;
			case TILEMODE_CHANGE::MODE_OBJECT:
				vCheckVertex = *(pBuffer->Get_BufferPos(dynamic_cast<TileInfo*>(iter->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Get_TileNumber()));
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
	//vMouseCheck.x = floor(vMouseCheck.x);
	//vMouseCheck.y = floor(vMouseCheck.y);
	//vMouseCheck.z = floor(vMouseCheck.z);
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
				vTileLocalPos[1] = { 1.f, 0.f, -1.f };  //우하단 y+ 기준
				vTileLocalPos[2] = { -1.f, 0.f,  1.f }; //좌상단 y+ 기준
				vTileLocalPos[3] = { 1.f, 0.f,  1.f };  //우상단 y+ 기준

				for (int i = 0; i < 4; ++i)
					D3DXVec3TransformCoord(&vTileLocalPos[i], &vTileLocalPos[i], &InverseWorld);

				if (D3DXIntersectTri(&vTileLocalPos[0], &vTileLocalPos[1], &vTileLocalPos[2], &vOrigin, &vDirection, &fu, &fv, &ft) ||
					D3DXIntersectTri(&vTileLocalPos[3], &vTileLocalPos[2], &vTileLocalPos[1], &vOrigin, &vDirection, &fu, &fv, &ft))
				{
					vMouseCheck = vOrigin + vDirection * ft;
					if (ftCheck > ft)
					{
						//Check_Distance(vMouseCheck); //5방향 평면 비교 잠시 폐기

						//m_eTile = TILE_SIDE::TILE_OTHER;
						vMouseBlockCheck = vMouseCheck;
						ftCheck = ft;
					}
				}
			}
		}
	}
		// 보정
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
		else m_bMouseClick = true;
		m_pTransform->Set_Pos(vMouseCheck.x, vMouseCheck.y, vMouseCheck.z);
	   //좌클릭시 블럭 설치

		if (m_bTileCheck && m_pTileName != nullptr)
		{
			if (KeyManager::GetInstance()->Get_MouseState(DIM_LB) & 0x80 && m_bMouseClick)
			{
				////정육면체말고 다른 타일 깔고싶으면 클래스 만들어서 바꾸면됨
				GameObject* pTile = nullptr;
				switch (m_eMode)
				{
				case TILEMODE_CHANGE::MODE_TILE:
					pTile = CXZTile::Create(GRPDEV,m_eTile);
					break;
				case TILEMODE_CHANGE::MODE_CUBE:
					pTile = CubeTile::Create(GRPDEV);
					break;
				case TILEMODE_CHANGE::MODE_OBJECT:
					pTile = CXZTile::Create(GRPDEV, m_eTile);
					break;
				}
				if (pTile != nullptr)
				{
					GRPDEV->AddRef();
					switch (m_eMode)
					{
					case TILEMODE_CHANGE::MODE_TILE:
						if (m_eTileState == STATE_ANIMATION)
						{
							wstring path;
							wstring pa = m_vecName[TILE_STATE::STATE_ANIMATION].front();
							if (wcscmp(m_pTileName, L"Spr_Deco_BushFlower01_0.png") == 0)
								m_pTileName = L"Spr_Deco_BushFlower01_0%d.png";
							if (wcscmp(m_pTileName, L"Spr_Deco_BushFlower02_0.png") == 0)
								m_pTileName = L"Spr_Deco_BushFlower02_0%d.png";
							path = pa + L"/Anmation/" + m_pTileName;
							dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileAnimaiton(path.c_str(), 6, m_eTile, m_eTileState, m_eMode, (_int)vMouseCheck.z * VTXCNTX + (_int)vMouseCheck.x);
						}else dynamic_cast<TileInfo*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TILEINFO))->Set_TileAll(m_pPathName, m_pTileName, m_eTile, m_eTileState, m_eMode, (_int)vMouseCheck.z * VTXCNTX + (_int)vMouseCheck.x);
						
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(*m_pTransform->Get_Scale());
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(*m_pTransform->Get_Rotation());
						TileManager::GetInstance()->Add_Tile(pTile, vMouseCheck, m_eMode, m_eTile);
						
						break;
					case TILEMODE_CHANGE::MODE_CUBE:
						dynamic_cast<CubeTile*>(pTile)->Set_TileNumber((_int)vMouseCheck.z * VTXCNTX + (_int)vMouseCheck.x);
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(*m_pTransform->Get_Scale());
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(*m_pTransform->Get_Rotation());
						TileManager::GetInstance()->Add_Tile(pTile, vMouseCheck, m_eMode);
						break;

					case TILEMODE_CHANGE::MODE_OBJECT:
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Scale(*m_pTransform->Get_Scale());
						dynamic_cast<Transform*>(pTile->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Set_Rotation(*m_pTransform->Get_Rotation());
						TileManager::GetInstance()->Add_Tile(pTile, vMouseCheck, m_eMode, m_eTile);
						break;

					}	
	
				}
			}
			m_bMouseClick = false;
		}
		//우클릭 삭제
		if (m_eMode != TILEMODE_CHANGE::MODE_END && KeyManager::GetInstance()->Get_MouseState(DIM_RB) & 0x80 && m_bMouseClick)
		{
			TileManager::GetInstance()->Delete_Tile(vMouseCheck, vOrigin, vDirection);
			m_bMouseClick = false;
		}
		
		m_pTransform->Set_Pos(vMouseCheck.x, vMouseCheck.y + 1.f + (pTransform->Get_Scale()->y) * 0.15, vMouseCheck.z);
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
	for (size_t i = 0; i < TILE_STATE::STATE_END; ++i)
	{
		for (auto& iter : m_vecImage[i])
			Safe_Delete(iter.wstr);

	}
	
	GameObject::Free();
}