#pragma once

#include "entity.h"
#include "bullet.h"

class Player : public Entity
{
public:
    using Entity::Entity;
    int health = 100;

    void update(float delta) override
    {
        int w = GetScreenWidth();
        int h = GetScreenHeight();

        raylib::Vector2 input = {0};

        if (IsKeyDown(KEY_A)) input.x -= 1;
        if (IsKeyDown(KEY_D)) input.x += 1;
        if (IsKeyDown(KEY_W)) input.y -= 1;
        if (IsKeyDown( KEY_S)) input.y += 1;
        
        raylib::Vector2 direction = input.Normalize();
        position += direction * speed * delta;
        position.x = Clamp(position.x, size.x / 2, w - size.x / 2);
        position.y = Clamp(position.y, size.y / 2, h - size.y / 2);
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