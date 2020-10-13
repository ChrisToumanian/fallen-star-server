#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "transform.h"

class Entity
{
public:
	Entity();

	// Chat
	std::string name = "entity";
	unsigned char color = 15;

	// Stats
	Transform transform;
	int health = 100;

	void update();
	void changeHealth(int amount);
	void die();
};

#endif