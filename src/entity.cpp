#include "entity.h"

Entity::Entity()
{
}

void Entity::update()
{
}

void Entity::changeHP(int amount)
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
