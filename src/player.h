#pragma once

#include "entity.h"
#include "sprite.h"
#include "physics.h"
#include "transform.h"
#include <memory>

using fkeyz::Sprite;
using fkeyz::Physics;

class Player : public Entity
{
public:
    // using Entity::Entity;
    int health = 100;

    Player()
    {
        Vector2 rect_size = raylib::Vector2(50, 50);
        auto transform = std::make_shared<fkeyz::Transform>(raylib::Vector2(100, 100), raylib::Vector2(1, 1), 0.0f);
        auto sprite = std::make_shared<Sprite>(rect_size, raylib::Color::Red(), 0);
        auto physics = std::make_shared<Physics>(rect_size, 1, 150);

        AddComponent(transform);
        AddComponent(sprite);
        AddComponent(physics);
    };

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
        auto transform = GetComponent<fkeyz::Transform>();
        auto physics = GetComponent<Physics>();
        raylib::Vector2 pos = transform->position;
        pos += direction * physics->speed * delta;
        pos.x = Clamp(pos.x, physics->collision_size.x / 2, w - physics->collision_size.x / 2);
        pos.y = Clamp(pos.y, physics->collision_size.y / 2, h - physics->collision_size.y / 2);
        transform->position = pos;
    }
};