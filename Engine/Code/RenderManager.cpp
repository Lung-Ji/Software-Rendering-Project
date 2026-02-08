#include "RenderManager.h"
#include "TileManager.h"
IMPLEMENT_SINGLETON(RenderManager)

RenderManager::RenderManager()	{			}
RenderManager::~RenderManager() {	Free();	}

VOID RenderManager::Add_RenderGroup(RENDERID _RID, GameObject* _GOBJ) {
	if (_GOBJ == nullptr)	return;
	RenderGroup[_RID].push_back(_GOBJ);
	_GOBJ->AddRef();
}
VOID RenderManager::Render_GameObject(LPDIRECT3DDEVICE9& _GRPDEV) {
	Render_Priority(_GRPDEV);
	Render_NonAlpha(_GRPDEV);
	Render_Alpha(_GRPDEV);
	Render_UI(_GRPDEV);
	Render_TILE(_GRPDEV);

	Clear_RenderGroup();
}
VOID RenderManager::Clear_RenderGroup()	{
	for (INT ID = 0; ID < (LONG)RENDERID::RENDER_END; ++ID) {
		for_each(RenderGroup[ID].begin(), RenderGroup[ID].end(), CDeleteObj());
		RenderGroup[ID].clear();
	}
}
VOID RenderManager::Render_Priority(LPDIRECT3DDEVICE9& _GRPDEV) {
	for (auto& _OBJ : RenderGroup[RENDER_PRIORITY]) {
		if(_OBJ->Get_ObjectDead() == FALSE)
			_OBJ->Render_GameObject();
	}
}
VOID RenderManager::Render_NonAlpha(LPDIRECT3DDEVICE9& _GRPDEV) {
	for (auto& _OBJ : RenderGroup[RENDER_NONALPHA]) {
		if (_OBJ->Get_ObjectDead() == FALSE)
			_OBJ->Render_GameObject();
	}
}
VOID RenderManager::Render_Alpha(LPDIRECT3DDEVICE9& _GRPDEV) {
	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_GRPDEV->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_GRPDEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	RenderGroup[RENDER_ALPHA].sort([](GameObject* DEST, GameObject* SRC)->bool
		{
			return DEST->Get_AlphaZValue() > SRC->Get_AlphaZValue();
		});
	for (auto& _OBJ : RenderGroup[RENDER_ALPHA]) {
		if(_OBJ->Get_ObjectDead() == FALSE)
			_OBJ->Render_GameObject();
	}
		
	
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
VOID RenderManager::Render_UI(LPDIRECT3DDEVICE9& _GRPDEV)	{
	for (auto& _OBJ : RenderGroup[RENDER_UI]){
		if (_OBJ->Get_ObjectDead() == FALSE)
			_OBJ->Render_GameObject();
	}
}
VOID RenderManager::Render_TILE(LPDIRECT3DDEVICE9& _GRPDEV)
{
	
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_GRPDEV->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_GRPDEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	TileManager::GetInstance()->Render_TileList();
	for (auto& _OBJ : RenderGroup[RENDER_TILE]){
		if (_OBJ->Get_ObjectDead() == FALSE)
			_OBJ->Render_GameObject();
	}

	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	return VOID();
}
VOID	RenderManager::Free() {
	Clear_RenderGroup();
}

VOID RenderManager::Make_BillBoard(Transform* Component_Transform, LPDIRECT3DDEVICE9 _GRPDEV)
{
	_matrix		matBill, matWorld, matView;

	matWorld = *Component_Transform->Get_World();
	_GRPDEV->GetTransform(D3DTS_VIEW, &matView);

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
