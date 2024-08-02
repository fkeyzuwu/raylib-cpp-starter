#pragma once
#include <raylib-cpp.hpp>
#include <memory>

namespace fkeyz
{
    class Entity;

    class Component
    {
    public:
        fkeyz::Entity* parent;
        virtual ~Component() {}
    };
}
