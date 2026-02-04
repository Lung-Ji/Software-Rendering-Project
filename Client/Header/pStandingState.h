#pragma once
#include "PlayerState.h"
class pStandingState : public PlayerState
{
public:
	pStandingState() {}

	virtual void handleInput(Player& player);

	virtual void update(Player& player);
};

