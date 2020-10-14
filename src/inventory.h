#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include "item.h"

class Inventory
{
public:
	Inventory();

	int currency = 0;
	unsigned char bag_slots = 12;
	
	std::vector<Item*> items;
};

#endif
