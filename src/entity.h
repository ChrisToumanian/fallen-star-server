#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity
{
public:
	Entity();

	// Chat
	std::string name = "entity";
	unsigned char color = 15;

	// Transform
	float posX = 0;
	float posY = 0;
	int rotation = 0;

	// Stats
	int health = 100;

	void update();
	void move(float x, float y);
	void changeHealth(int amount);
	void die();
};

#endif
