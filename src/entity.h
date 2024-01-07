#pragma once
#include <raylib-cpp.hpp>

class Entity
{
public:
    raylib::Vector2 position;
    raylib::Vector2 size;
    float speed;
    raylib::Color color;

    Entity(raylib::Vector2 _position, raylib::Vector2 _size, float _speed, raylib::Color _color):
        position(_position), size(_size), speed(_speed), color(_color){};

    virtual ~Entity(){}
    virtual void update() = 0;

    Rectangle get_rect() const
    {
        return Rectangle
        {
            position.x - size.x / 2,
            position.y - size.y / 2, // might need to change it to + instead of -
            size.x,
            size.y
        };
    }
};