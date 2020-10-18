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
	std::string game_class = "";
	std::string profession = "";
	std::string backstory = "";
	std::string motto = "";
	Transform transform;
	
	Inventory inventory;
	Item *slots[12];
	// Slot #00: left-click
	// Slot #01: right-click
	// Slot #02: key 1
	// Slot #03: key 2
	// Slot #04: key 3
	// Slot #05: key 4
	// Slot #06: head
	// Slot #07: chest
	// Slot #08: legs
	// Slot #09: feet
	// Slot #10: hands
	// Slot #11: ring

	// stats
	unsigned short level = 1;
	short hp = 100;
	short max_hp = 100;
	short mp = 0;
	short max_mp = 0;
	
	// physical attributes
	unsigned short strength = 0;
	unsigned short vitality = 0;
	unsigned short agility = 0;

	// mental attributes
	unsigned short shortellect = 0;
	unsigned short wisdom = 0;
	unsigned short charm = 0;

	void update();
	void use_slot(int slot);
	void change_hp(int amount);
	void die();
};

#endif
