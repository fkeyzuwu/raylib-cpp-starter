#pragma once
#include "component.h"

using namespace fkeyz;

namespace fkeyz
{
    class Physics: public Component
    {
    public:
        raylib::Vector2 collision_size;
        int collision_mask;
        float speed; // normal speed

        Physics(raylib::Vector2 _collision_size, int _collision_mask, float _speed):
            collision_size(_collision_size), collision_mask(_collision_mask), speed(_speed){};
    };
}