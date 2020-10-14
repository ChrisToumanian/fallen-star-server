#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include "transform.h"
#include "inventory.h"
#include "item.h"

class Entity
{
public:
	Entity();

	int id = 1;
	unsigned char color = 1;
	std::string name = "entity";
	std::string race = "human";
	std::string game_class = "warrior";
	std::string profession = "blacksmith";
	Transform transform;
	
	Inventory inventory;
	Item* primary_slot;
	Item* secondary_slot;
	Item* head_slot;
	Item* shoulders_slot;
	Item* chest_slot;
	Item* hands_slot;
	Item* legs_slot;

	int xp = 0;
	int reputation = 0;
	int hp = 100;
	int max_hp = 100;
	int mp = 20;
	int max_mp = 20;
	int att = 70;
	int max_att = 70;
	int def = 100;
	int max_def = 100;
	int spd = 40;
	int max_spd = 40;
	int dxt = 20;
	int max_dxt = 20;
	int vit = 50;
	int max_vit = 50;
	int wis = 50;
	int max_wis = 50;

	void update();
	void changeHP(int amount);
	void die();
};

#endif
