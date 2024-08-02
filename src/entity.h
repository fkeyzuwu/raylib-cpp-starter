#pragma once
#include <raylib-cpp.hpp>
#include "transform.h"
#include <typeinfo>

namespace fkeyz
{
    class Component;

    class Entity
    {
    public:
        std::vector<std::shared_ptr<Component>> components;

        virtual ~Entity(){}
        virtual void update(float delta) = 0;

        void AddComponent(std::shared_ptr<Component> component)
        {
            components.push_back(component);
            component->parent = this;
        }

        template<typename T>
        std::shared_ptr<T> GetComponent() const
        {
            for (auto& component : components) {
                std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                if (castedComponent) {
                    return castedComponent;
                }
            }

            return nullptr;
        }
    };

    
}