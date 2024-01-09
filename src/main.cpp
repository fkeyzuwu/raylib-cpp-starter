#include <raylib-cpp.hpp>
#include "entity.h"
#include "vector"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include <memory>

bool game_over = false;

bool is_entity_out_of_screen(const Entity& entity)
{
    int h = GetScreenHeight(); 
    int w = GetScreenWidth();

    if(entity.position.x > w || entity.position.x < 0)
    {
        return true;
    }
    else if(entity.position.y > h || entity.position.y < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<Enemy> spawn_enemy()
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

    return std::make_shared<Enemy>(
        Vector2{x_pos, y_pos},
        Vector2{15, 15},
        50,
        GREEN
    );
}

void draw_crosshair()
{
    Vector2 mouse_position = GetMousePosition();
    DrawCircleV(mouse_position, 5, BLACK);
}

void draw_entity(const Entity& entity, raylib::Vector2 entity_direction = {0, 0})
{
    if(entity_direction != raylib::Vector2{0, 0})
    {
        float rotation = std::atan2(entity_direction.y, entity_direction.x) * (180.0f / PI);
        DrawRectanglePro(entity.get_rect(), Vector2{0, 0}, rotation, entity.color);
    }
    else
    {
        DrawRectangleRec(entity.get_rect(), entity.color);
    }
}

int main() {
    
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Tamir gaming");
    
    SetTargetFPS(60);
    DisableCursor();

    Player player (
        Vector2{float(screenWidth) / 2, float(screenHeight) / 2},
        Vector2{30, 30},
        150,
        RED
    );

    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Bullet>> bullets;

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
            auto enemy = spawn_enemy();
            enemy->target = &player;
            enemies.push_back(enemy);
        }

        player.update(delta);
        Rectangle player_rect = player.get_rect();
        
        if(IsMouseButtonPressed(0))
        {
            auto bullet = player.shoot_bullet();
            bullets.push_back(bullet);
        }

        BeginDrawing();

        for(int i = enemies.size() - 1; i >= 0; i--) 
        {
            auto enemy = enemies.at(i);
            Rectangle enemy_rect = enemy->get_rect();
            if(CheckCollisionRecs(enemy_rect, player_rect))
            {
                enemies.erase(enemies.begin() + i);
                player.speed += 10;
            }
            else
            {
                enemy->update(delta);
                if(enemy->can_shoot_bullet){
                    auto bullet = enemy->shoot_bullet();
                    bullets.push_back(bullet);
                }
                draw_entity(*enemy);
            }
        }

        draw_entity(player);

        for(int i = bullets.size() - 1; i >= 0; i--)
        {
            auto bullet = bullets.at(i);
            Rectangle bullet_rect = bullet->get_rect();
            if(bullet->collision_mask == "Player" && CheckCollisionRecs(bullet_rect, player_rect))
            {
                player.health -= 10;
                if(player.health <= 0)
                {
                    game_over = true;
                }
                bullets.erase(bullets.begin() + i);
            }
            else if(bullet->collision_mask == "Enemy")
            {
                 for(int j = enemies.size() - 1; j >= 0; j--)
                 {
                    auto enemy = enemies.at(j);
                    Rectangle enemy_rect = enemy->get_rect();
                    if (CheckCollisionRecs(bullet_rect, enemy_rect))
                    {
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        break;
                    }
                 }
            }

            if(bullet == nullptr)
            {
                continue;
            }
            else if(is_entity_out_of_screen(*bullet))
            {
                bullets.erase(bullets.begin() + i);
            }
            else
            {
                bullet->update(delta);
                draw_entity(*bullet, bullet->move_direction);
            }
        }

        draw_crosshair();
        ClearBackground(RAYWHITE);
        
        textColor.DrawText("Player Health: " + std::to_string(player.health), 20, 20, 20);

        if(game_over)
        {
            const char* game_over_text = "Game Over!";
            Vector2 text_size = MeasureTextEx(GetFontDefault(), game_over_text, 20, 1);
            textColor.DrawText(
                game_over_text, 
                screenWidth / 2 - text_size.x / 2,
                screenHeight / 2 - 100,
                20);
        }

        EndDrawing();
    }

    return 0;
}