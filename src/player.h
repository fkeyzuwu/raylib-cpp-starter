#pragma once

#include "entity.h"
#include "bullet.h"
#include <memory>

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

    std::shared_ptr<Bullet> shoot_bullet()
    {
        auto bullet = std::make_shared<Bullet>
        (
            position,
            Vector2{8, 5},
            400,
            BLUE
        );
        raylib::Vector2 mouse_pos = GetMousePosition();
        bullet->move_direction = (mouse_pos - position).Normalize();
        bullet->collision_mask = "Enemy";
        return bullet;
    }
};