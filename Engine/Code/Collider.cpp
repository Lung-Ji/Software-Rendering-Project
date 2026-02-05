#include "Collider.h"

Collider::Collider()							:						ColliderPos(nullptr)		 , Curr_ColState(FALSE), Prev_ColState(FALSE)	{}
Collider::Collider(LPDIRECT3DDEVICE9 _GRPDEV)	: Component(_GRPDEV),	ColliderPos(nullptr)		 , Curr_ColState(FALSE), Prev_ColState(FALSE)	{}
Collider::Collider(CONST Collider& _RHS)		: Component(_RHS),		ColliderPos(_RHS.ColliderPos), Curr_ColState(FALSE), Prev_ColState(FALSE),	
	matWorld(_RHS.matWorld), matView(_RHS.matView), matProj(_RHS.matProj)																			{}
Collider::~Collider()																																{}

HRESULT		Collider::Ready_Component() {
	MinPoint = { 0.f, 0.f, 0.f };
	MaxPoint = { 0.f, 0.f, 0.f };

	return S_OK;
}
INT			Collider::Update_Component(CONST FLOAT& _DT) {
	CenterPos = *ColliderPos->Get_Position();
	
	MinPoint = { CenterPos.x - Scale.x, CenterPos.y - Scale.y, CenterPos.z - Scale.z };
	MaxPoint = { CenterPos.x + Scale.x, CenterPos.y + Scale.y, CenterPos.z + Scale.z };
	// 1차 통합 테스트
	return 0;
}
VOID		Collider::LateUpdate_Component(CONST FLOAT& _DT) {
	
}
VOID		Collider::Render_Component() {
	ID3DXLine* pLine;
	D3DXCreateLine(GRPDEV, &pLine);

	D3DXVECTOR3 lineVertices[16] = { {MinPoint.x, MinPoint.y, MinPoint.z}, {MinPoint.x, MinPoint.y, MaxPoint.z}, {MinPoint.x, MaxPoint.y, MaxPoint.z},
									 {MinPoint.x, MaxPoint.y, MinPoint.z}, {MinPoint.x, MinPoint.y, MinPoint.z}, {MaxPoint.x, MinPoint.y, MinPoint.z},
									 {MaxPoint.x, MinPoint.y, MaxPoint.z}, {MinPoint.x, MinPoint.y, MaxPoint.z}, {MaxPoint.x, MinPoint.y, MaxPoint.z},
									 {MaxPoint.x, MaxPoint.y, MaxPoint.z}, {MinPoint.x, MaxPoint.y, MaxPoint.z}, {MaxPoint.x, MaxPoint.y, MaxPoint.z},
									 {MaxPoint.x, MaxPoint.y, MinPoint.z}, {MinPoint.x, MaxPoint.y, MinPoint.z}, {MaxPoint.x, MaxPoint.y, MinPoint.z},
									 {MaxPoint.x, MinPoint.y, MinPoint.z}, };
	GRPDEV->GetTransform(D3DTS_WORLD, &matWorld);
	GRPDEV->GetTransform(D3DTS_VIEW, &matView);
	GRPDEV->GetTransform(D3DTS_PROJECTION, &matProj);
	
	Sum = matView * matProj;

	pLine->SetWidth(0.75f);

	pLine->Begin();
	if (Curr_ColState) {
		pLine->DrawTransform(lineVertices, 16, &Sum, D3DXCOLOR(1, 0, 0, 1));
	}
	else {
		pLine->DrawTransform(lineVertices, 16, &Sum, D3DXCOLOR(0, 1, 0, 1));
	}
	
	pLine->End();
	pLine->Release();
}
Collider* Collider::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Collider* CLD = new Collider(_GRPDEV);
	if (FAILED(CLD->Ready_Component())) {
		MSG_BOX("Cannot Create Collider.");
		Safe_Release(CLD);
		return nullptr;
	}
	return CLD;
}
Component* Collider::Clone() {
	return new Collider(*this);
}
VOID		Collider::Free() {
	Component::Free();
}