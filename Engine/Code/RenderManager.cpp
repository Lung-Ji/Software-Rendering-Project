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
	for (auto& _OBJ : RenderGroup[RENDER_PRIORITY])
		_OBJ->Render_GameObject();
}
VOID RenderManager::Render_NonAlpha(LPDIRECT3DDEVICE9& _GRPDEV) {
	for (auto& _OBJ : RenderGroup[RENDER_NONALPHA])
		_OBJ->Render_GameObject();
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
	for (auto& _OBJ : RenderGroup[RENDER_ALPHA])
		_OBJ->Render_GameObject();
	
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
VOID RenderManager::Render_UI(LPDIRECT3DDEVICE9& _GRPDEV)	{
	for (auto& _OBJ : RenderGroup[RENDER_UI])
		_OBJ->Render_GameObject();
}
VOID RenderManager::Render_TILE(LPDIRECT3DDEVICE9& _GRPDEV)
{
	
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_GRPDEV->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_GRPDEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	TileManager::GetInstance()->Render_TileList();
	for (auto& _OBJ : RenderGroup[RENDER_TILE])
		_OBJ->Render_GameObject();

	_GRPDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	_GRPDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	return VOID();
}
VOID	RenderManager::Free() {
	Clear_RenderGroup();
}