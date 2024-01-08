#pragma once
#include "entity.h"

class Bullet : public Entity
{
    using Entity::Entity;
public:
    raylib::Vector2 move_direction;

    void update(float delta) override
    {
        position += move_direction * speed * delta;
    }
};