#pragma once
#include "component.h"
#include <memory>
#include "transform.h"

namespace fkeyz
{
    class Sprite: public Component
    {
    public:
        raylib::Vector2 size;
        raylib::Color color;
        int render_order; // higher numbers are rendered first

        Sprite(raylib::Vector2 _size, raylib::Color _color, int _render_order):
            size(_size), color(_color), render_order(_render_order) {};
        
        Rectangle get_rect()
        {
            auto transform = parent->GetComponent<fkeyz::Transform>();
            return Rectangle
            {
                transform->position.x - size.x / 2,
                transform->position.y - size.y / 2, // might need to change it to + instead of -
                size.x,
                size.y
            };
        }
    };
}
