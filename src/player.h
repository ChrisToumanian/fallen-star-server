#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entity.h"

class Player : public Entity
{
public:
	Player();

	// User
	std::string username = "player";

	void quit();
};

#endif
