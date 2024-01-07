#include <raylib-cpp.hpp>
#include "entity.h"
#include "vector"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

Enemy* spawn_enemy()
{
    int value = GetRandomValue(1, 4); // pick a random side to spawn from
    float x_pos;
    float y_pos;
    int h = GetScreenHeight(); 
    int w = GetScreenWidth();

    switch(value){ // Generate random Position
        case 1: // left
            x_pos = -50;
            y_pos = GetRandomValue(-(h/4), h + (h/4));
            break;
        case 2: // right
            x_pos = w + 50;
            y_pos = GetRandomValue(-(h/4), h + (h/4));
            break;
        case 3: // up
            x_pos = GetRandomValue(-(w/4), w + (w/4));
            y_pos = h + 50;
            break;  
        case 4: // down
            x_pos = GetRandomValue(-(w/4), w + (w/4));
            y_pos = -50;
            break;
    }

    return new Enemy(
        Vector2{x_pos, y_pos},
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

    Player player (
        Vector2{float(screenWidth) / 2, float(screenHeight) / 2},
        Vector2{30, 30},
        150,
        RED
    );

    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;

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
        player.position.x = Clamp(player.position.x, player.size.x / 2, screenWidth - player.size.x / 2);
        player.position.y = Clamp(player.position.y, player.size.y / 2, screenHeight - player.size.y / 2);
        Rectangle player_rect = player.get_rect();

        BeginDrawing();

        for(int i = enemies.size() - 1; i >= 0; i--) 
        {
            Enemy* enemy = enemies.at(i);
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

                Bullet* bullet = enemy->shoot_bullet();
            }
        }

        draw_entity(player);
        ClearBackground(RAYWHITE);
        
        textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);

        EndDrawing();
    }

    return 0;
}