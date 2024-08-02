#include <raylib-cpp.hpp>
#include "entity.h"
#include "vector"
#include "player.h"
#include <memory>
#include <string>
#include <iostream>

static int screen_height = 450; 
static int screen_width = 800;

void render(const Entity& entity)
{
    auto sprite = entity.GetComponent<Sprite>();
    auto transform = entity.GetComponent<fkeyz::Transform>();
    // if(sprite && transform)
    // {
    //     DrawRectangle(transform->position.x, transform->position.y, sprite->size.x, sprite->size.y, sprite->color);
    // }
    if(sprite && transform)
    {
        DrawRectanglePro(sprite->get_rect(), transform->position, transform->rotation, sprite->color);
    }
}

int main()
{
    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screen_width, screen_height, "Tamir gaming");
    
    SetTargetFPS(60);
    DisableCursor();

    Player player;
    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        player.update(delta);
        float speed = player.GetComponent<Physics>()->speed;
        auto v = player.GetComponent<fkeyz::Transform>()->position;
        textColor.DrawText("Player pos: " + std::to_string(v.x) + " " + std::to_string(v.y), 190, 200, 20);
        render(player);
        EndDrawing();
    }

    return 0;
}