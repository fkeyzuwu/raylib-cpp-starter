#pragma once
#include "entity.h"

class Bullet : public Entity
{
    using Entity::Entity;
public:
    raylib::Vector2 move_direction;
    std::string collision_mask;

    void update(float delta) override
    {
        position += move_direction * speed * delta;
    }
};