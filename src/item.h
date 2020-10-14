#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item 
{
public:
	Item();

	std::string name = "sword";
	std::string type = "weapon";

	int tier = 0;
	int dmg = 10;
	int armor = 0;
	int durability = 40;
	int max_durability = 40;
	int price = 10;

	int bonus_xp = 0;
	int bonus_hp = 0;
	int bonus_mp = 0;
	int bonus_att = 0;
	int bonus_def = 0;
	int bonus_spd = 0;
	int bonus_dxt = 0;
	int bonus_vit = 0;
	int bonus_wis = 0;

	void use();
	void destroy();
};

#endif
