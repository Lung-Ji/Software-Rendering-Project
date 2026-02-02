#include "Tile.h"
#include "../Include/PCH.h"
Tile::Tile(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV), m_TileHeight(0.f), m_bTileCheck(true){}
Tile::Tile(const GameObject& _RHS) : GameObject(_RHS) {}
Tile::~Tile() {}

HRESULT Tile::Ready_GameObject() {

	if (FAILED(Component_Initialize())) return E_FAIL;

	return S_OK;
}
INT	Tile::Update_GameObject(const _float& _DT) {


	RenderManager::GetInstance()->Add_RenderGroup(RENDER_NONALPHA, this);
	return GameObject::Update_GameObject(_DT);

}
VOID Tile::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);
	Check_TilePoint();
}

VOID Tile::Render_GameObject()
{
	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRPDEV->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	
	m_pBuffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	GRPDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT Tile::Component_Initialize() {

	m_pBuffer    = ADD_COMPONENT_TILE; 
	m_pTransform = ADD_COMPONENT_TRANSFORM;

	return S_OK;
}
_bool Tile::Check_Bottom(_vec3* vOrigin)
{
	_vec3 vCheckVertex;
	_float fx,fz;
	Component* pTransform = SceneManager::GetInstance()->Get_GameObject(L"Terrain")->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TERRAIN);
	Buffer* pBuffer = dynamic_cast<Buffer*>(pTransform);
	
	for (auto& iter : TileManager::GetInstance()->Get_TileList())
	{
		
		_int iDst = dynamic_cast<CubeTile*>(iter)->Get_TileNumber(); //안겹치게 예외처리요 근데 정육면체 기준
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
			vCheckVertex = *(pBuffer->Get_BufferPos(dynamic_cast<CubeTile*>(iter)->Get_TileNumber()));

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
	_vec3 vPlayerPos, vRight, vLook, vOrigin, vDirection;
	POINT pt;
	GRPDEV->GetViewport(&vp);
	GRPDEV->GetTransform(D3DTS_PROJECTION, &proj);
	GRPDEV->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&InversView, 0, &matView);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	//픽킹 계산 :<
	D3DXMatrixIdentity(&vWorldInvese);
	memcpy(&vWorldInvese, m_pTransform->Get_World(), sizeof(_matrix));
	D3DXMatrixInverse(&vWorldInvese, 0, &vWorldInvese);

	Component* pTransform = SceneManager::GetInstance()->Get_GameObject(L"Terrain")->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TERRAIN);
	Buffer* pBuffer = dynamic_cast<Buffer*>(pTransform);

	vDirection.x = (((2.0f  * pt.x) / vp.Width)  - 1.0f) / proj(0, 0);
	vDirection.y = (((-2.0f * pt.y) / vp.Height) + 1.0f) / proj(1, 1);
	vDirection.z = 1.f;
	vOrigin = { 0.f, 0.f ,0.f };

	D3DXVec3TransformCoord(&vOrigin, &vOrigin, &InversView);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &InversView);
	D3DXVec3Normalize(&vDirection, &vDirection);


	//지형 전체기준으로 광선 쏴서 어느 위치에 놓을지 결정
	_vec3 vMouseCheck, vMouseBlockCheck{};
	_float fu(0), fv(0), ft(0);
	if (D3DXIntersectTri(pBuffer->Get_BufferPos(0),
		pBuffer->Get_BufferPos(128 * 129),
		pBuffer->Get_BufferPos(128 * 129 + 128)
		, &vOrigin, &vDirection, &fu, &fv, &ft))
	{
		vMouseCheck = vOrigin + vDirection * ft;
	}
	if (D3DXIntersectTri(pBuffer->Get_BufferPos(0),
		pBuffer->Get_BufferPos(128 * 129 + 128),
		pBuffer->Get_BufferPos(128)
		, &vOrigin, &vDirection, &fu, &fv, &ft))
	{
		vMouseCheck = vOrigin + vDirection * ft;
	}

	vMouseCheck.x = floor(vMouseCheck.x);
	vMouseCheck.y = floor(vMouseCheck.y);
	vMouseCheck.z = floor(vMouseCheck.z);
	_vec3 vPos, vTileLocalPos[4];
	_matrix InverseWorld, CheckWorld;
	//설치 되어있는 블럭 충돌 비교
		{
			for (auto iter : TileManager::GetInstance()->Get_TileList())
			{
				//어케 비교하지 싯팔
				dynamic_cast<Transform*>(iter->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Info(INFO_POS, &vPos);
				memcpy(&InverseWorld, dynamic_cast<Transform*>(iter->Get_Component(Engine::COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_World(), sizeof(_matrix));				
			
				//로컬 좌표 들고와서 월드좌표 변환후 광선으로 윗면 비교???
				vTileLocalPos[0] = { -1.f, 1.f, -1.f }; //좌하단
				vTileLocalPos[1] = {  1.f, 1.f, -1.f }; //우하단
				vTileLocalPos[2] = { -1.f, 1.f,  1.f }; //좌상단
				vTileLocalPos[3] = {  1.f, 1.f,  1.f }; //우상단
				
				for (int i = 0; i < 4; ++i)
					D3DXVec3TransformCoord(&vTileLocalPos[i], &vTileLocalPos[i], &InverseWorld);

					if (D3DXIntersectTri(&vTileLocalPos[0], &vTileLocalPos[1], &vTileLocalPos[2], &vOrigin, &vDirection, &fu, &fv, &ft) ||
						D3DXIntersectTri(&vTileLocalPos[3], &vTileLocalPos[2], &vTileLocalPos[1], &vOrigin, &vDirection, &fu, &fv, &ft))
						vMouseCheck = vOrigin + vDirection * ft;
				
					//현재 설치된 블록중에서 y축 제일큰놈으로 
					if (vMouseBlockCheck.y < vMouseCheck.y)
					{
						vMouseBlockCheck = vMouseCheck;
					}

					//블럭 이미 설치 되어있는곳에 하려고 하면 안되게 해야되는데
					
			}
		}
		// 보정
		vMouseCheck = vMouseBlockCheck;

		vMouseCheck.x = floor(vMouseCheck.x);
		vMouseCheck.y = floor(vMouseCheck.y);
		vMouseCheck.z = floor(vMouseCheck.z);

		if (vMouseCheck.y < 0)
			vMouseCheck.y = 0;

		if (vMouseCheck.x < 1)
			vMouseCheck.x = 1;

		if (vMouseCheck.z < 1)
			vMouseCheck.z = 1;
		//한칸 높이 올리기
		m_TileHeight = vMouseCheck.y + 1;
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
				GameObject* pCube = CubeTile::Create(GRPDEV);
				if (pCube != nullptr)
				{
					vMouseCheck.y = m_TileHeight;
					GRPDEV->AddRef();
					dynamic_cast<CubeTile*>(pCube)->Set_TileNumber((_int)vMouseCheck.z * VTXCNTX + (_int)vMouseCheck.x);
					TileManager::GetInstance()->Add_Tile(pCube, vMouseCheck); 
				}
				else
					Safe_Release(pCube);
			}
		}

		//우클릭 삭제
		if (KeyManager::GetInstance()->Get_MouseState(DIM_RB) & 0x80)
			TileManager::GetInstance()->Delete_Tile(vMouseCheck, vOrigin, vDirection);
		
		m_bTileCheck= true;
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
	GameObject::Free();
}