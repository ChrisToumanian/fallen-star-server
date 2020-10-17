#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item 
{
public:
	Item();

	std::string name = "item";
	std::string type = "";
	std::string classes = "";
	std::string description = "";

	int tier = 0;
	int value = 10;
	int durability = 40;
	int duration = 0;
	int range = 0;
	int aoe = 0;
	int dot = 0;

	// appearance
	int sprite = 0;
	int animation = 0;

	// bonuses
	int damage = 0;
	int attack = 0;
	int defense = 0;
	int speed = 0;
	int hp = 0;
	int mp = 0;

	// bonuses
	int xp = 0;
	int vitality = 0;
	int strength = 0;
	int agility = 0;
	int intellect = 0;
	int wisdom = 0;
	int charm = 0;
	int reputation = 0;

	// afflictions
	int poison = 0;
	int burn = 0;
	int paralyze = 0;
	int electric = 0;
	int freeze = 0;
	int confuse = 0;
	int infatuate = 0;
	int leech = 0;
	int sleep = 0;
	int abv = 0;
	
	void use();
	void destroy();
};

#endif
