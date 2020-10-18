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

	// appearance
	short sprite = 0;
	short animation = 0;

	// stats
	short tier = 0;
	short hp = 0;
	short mp = 0;
	short attack = 0;
	short defense = 0;
	short speed = 0;
	short value = 0;
	short durability = 0;
	short duration = 0;
	short range = 0;
	short aoe = 0;
	short dot = 0;
	
	// bonuses
	short xp = 0;
	short vitality = 0;
	short strength = 0;
	short agility = 0;
	short shortellect = 0;
	short wisdom = 0;
	short charm = 0;
	short reputation = 0;

	// afflictions
	short poison = 0;
	short burn = 0;
	short paralyze = 0;
	short electric = 0;
	short freeze = 0;
	short confuse = 0;
	short infatuate = 0;
	short leech = 0;
	short sleep = 0;
	short abv = 0;
	
	void use();
	void destroy();
};

#endif
