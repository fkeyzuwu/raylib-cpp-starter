#pragma once
#include "component.h"

namespace fkeyz
{
    class Transform: public Component
    {
    public:
        raylib::Vector2 position;
        raylib::Vector2 scale;
        float rotation; // in degrees (?)

        Transform(raylib::Vector2 _position, raylib::Vector2 _scale, float _rotation):
            position(_position), scale(_scale), rotation(_rotation){};
    };
}
