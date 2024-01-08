#include <raylib-cpp.hpp>
#include "entity.h"
#include "vector"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

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
    raylib::Window w(screenWidth, screenHeight, "Tamir gaming");
    
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
            Enemy* enemy = spawn_enemy();
            enemy->target = &player;
            enemies.push_back(enemy);
        }

        player.update(delta);
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
                enemy->update(delta);
                if(enemy->can_shoot_bullet){
                    Bullet* bullet = enemy->shoot_bullet();
                    bullets.push_back(bullet);
                }
                draw_entity(*enemy);
            }
        }

        for(int i = bullets.size() - 1; i >= 0; i--)
        {
            Bullet* bullet = bullets.at(i);
            Rectangle bullet_rect = bullet->get_rect();
            if(CheckCollisionRecs(bullet_rect, player_rect))
            {
                player.health -= 10;
                if(player.health <= 0)
                {
                    game_over = true;
                }
                bullets.erase(bullets.begin() + i); //todo - make bullets destroy health
                delete bullet;
            }
            else if(is_entity_out_of_screen(*bullet))
            {
                bullets.erase(bullets.begin() + i);
                delete bullet;
            }
            else
            {
                bullet->update(delta);
                draw_entity(*bullet);
            }
        }

        draw_entity(player);
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