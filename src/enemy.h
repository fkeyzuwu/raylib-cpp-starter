#pragma once

#include "entity.h"
#include "bullet.h"

class Enemy : public Entity
{
public:
    using Entity::Entity;
    Entity* target;

    float shoot_timer = 0;
    float shoot_interval = 1;
    bool can_shoot_bullet = false;

    void update(float delta) override
    {
        shoot_timer += delta;
        if(shoot_timer > shoot_interval)
        {
            can_shoot_bullet = true;
            shoot_timer = 0;
        }

        raylib::Vector2 direction_to_target = (target->position - position).Normalize();
        position += direction_to_target * speed * delta;
    }

    Bullet* shoot_bullet()
    {
        Bullet* bullet = new Bullet
        (
            position,
            Vector2{8, 5},
            400,
            PURPLE
        );
        bullet->move_direction = (target->position - position).Normalize();
        bullet->collision_mask = "Player";
        can_shoot_bullet = false;
        return bullet;
    }
};