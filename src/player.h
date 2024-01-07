#pragma once

#include "entity.h"
#include "bullet.h"

class Player : public Entity
{
public:
    using Entity::Entity;

    void update() override
    {

    }

    Bullet* shoot_bullet()
    {
        return new Bullet
        (
            position,
            Vector2{8, 5},
            400,
            PURPLE
        );
    }
};