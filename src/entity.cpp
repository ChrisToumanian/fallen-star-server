#include "entity.h"

Entity::Entity()
{
}

void Entity::update()
{
}

void Entity::changeHealth(int amount)
{
    health += amount;
    if (health < 1)
    {
        health = 0;
        die();
    }
}

void Entity::die()
{
}