#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entity.h"
#include "map.h"

class Player : public Entity
{
public:
	Player();

	int server_id = 0;
	bool op = false;
	std::string username = "player";
    Map* map;

	unsigned short xp = 0;
	unsigned short reputation = 0;
	unsigned short currency = 0;

	void give_xp(int amount);
	int xp_to_level();
};

#endif
