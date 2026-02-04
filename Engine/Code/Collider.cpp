#include "Collider.h"

Collider::Collider()													{}
Collider::Collider(LPDIRECT3DDEVICE9 _GRPDEV)	: Component(_GRPDEV)	{}
Collider::Collider(CONST Collider& _RHS)		: Component(_RHS)		{}
Collider::~Collider()													{}

INT			Collider::Update_Component(CONST FLOAT& _DT) {

	return 0;
}
VOID		Collider::LateUpdate_Component(CONST FLOAT& _DT) {

}
VOID		Collider::Render_Component() {
	
}

BOOL Collider::OnCollisionEnter() {
	return 0;
}
BOOL Collider::OnCollisionStay() {
	return 0;
}
BOOL Collider::OnCollisionExit() {
	return 0;
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