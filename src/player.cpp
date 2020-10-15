#include "player.h"

Player::Player()
{
}

void Player::give_xp(int amount)
{
	xp += amount;
	
	// level
	if (xp >= xp_to_level())
	{
		xp = 0;
		level++;
	}
}

int Player::xp_to_level()
{
	return (level + 1) * 1000/2;
}
