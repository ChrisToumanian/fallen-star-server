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
	int level = 1;			// level
	int hp = 100;			// hit points (hp = stamina * 10)
	int mp = 0;				// magic points (mp = intellect * 10)
	
	// physical attributes
	int strength = 0;		// physical attack power
	int vitality = 0;		// hp regeneration
	int agility = 0;		// acrobatics, agility, stealth
	
	// mental attributes
	int intellect = 0;		// magic pool, magic regeneration, knowledge
	int wisdom = 0;			// magic power, perception 
	int charm = 0;			// persuasiveness, intimidation, bargaining, taming

	void update();
	void use_slot(int slot);
	void change_hp(int amount);
	void die();
};

#endif
