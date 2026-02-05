#pragma once
#include "pStandState.h"
#include "pRunningState.h"

class Player;

enum class pState
{
	STATE_STANDING,
	STATE_RUN,
	STATE_DASH,
	STATE_HANDUP,
	STATE_LANDING_DOWN,
	STATE_LANDING_UP,

	STATE_SHOTING,
	STATE_TARGETING,
	STATE_CHARGE_ATTACK,

	STATE_VICTORY,
	STATE_DEAD,

	End
};

class PlayerState
{
public:
	virtual ~PlayerState() {}
	virtual void handleInput(Player& player) {}
	virtual void update(Player& player) {}

public:
	static pStandState			standing;
	static pRunningState		running;
};
