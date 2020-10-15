#include "entity.h"

Entity::Entity()
{
}

void Entity::update()
{
}

void Entity::use_slot(int slot)
{
}

void Entity::change_hp(int amount)
{
    hp += amount;
    if (hp < 1)
    {
        hp = 0;
        die();
    }
}

void Entity::die()
{
}
