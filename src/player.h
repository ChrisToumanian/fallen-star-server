#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entity.h"
#include "map.h"

class Player : public Entity
{
public:
	Player();

	int id = 0;
	int server_id = 0;
	bool op = false;
	std::string username = "player";
    Map* map;

	void quit();
};

#endif