#include <raylib-cpp.hpp>
#include "entity.h"
#include "vector"

Entity* spawn_enemy()
{
    return new Entity(
        Vector2{float(GetRandomValue(0, GetScreenWidth())), float(GetRandomValue(0, GetScreenHeight()))},
        Vector2{15, 15},
        50,
        GREEN
    );
}

void draw_entity(const Entity& entity)
{
    DrawRectangleRec(entity.get_rect(), entity.color);
}

int main() {
    
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");
    
    SetTargetFPS(60);

    Entity player (
        Vector2{float(screenWidth) / 2, float(screenHeight) / 2},
        Vector2{30, 30},
        150,
        RED
    );

    std::vector<Entity*> enemies;

    float spawn_timer = 0;
    float spawn_interval = 2;

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
        spawn_timer += delta;
        if(spawn_timer > spawn_interval)
        {
            spawn_timer = 0;
            enemies.push_back(spawn_enemy());
        }

        raylib::Vector2 input = {0};

        if (IsKeyDown(KEY_A)) input.x -= 1;
        if (IsKeyDown(KEY_D)) input.x += 1;
        if (IsKeyDown(KEY_W)) input.y -= 1;
        if (IsKeyDown(KEY_S)) input.y += 1;
        
        raylib::Vector2 direction = input.Normalize();
        player.position += direction * player.speed * delta;
        Rectangle player_rect = player.get_rect();

        BeginDrawing();

        for(int i = enemies.size() - 1; i >= 0; i--) 
        {
            Entity* enemy = enemies.at(i);
            Rectangle enemy_rect = enemy->get_rect();
            if(CheckCollisionRecs(enemy_rect, player_rect))
            {
                enemies.erase(enemies.begin() + i);
                player.speed += 10;
                delete enemy;
            }
            else
            {
                raylib::Vector2 direction_to_player = (player.position - enemy->position).Normalize();
                enemy->position += direction_to_player * enemy->speed * delta;
                draw_entity(*enemy);
            }
        }

        draw_entity(player);
        ClearBackground(RAYWHITE);
        
        textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);

        EndDrawing();
    }

    return 0;
}