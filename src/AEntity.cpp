/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** AEntity.cpp
*/

#include "AEntity.hpp"
#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/AsciiSprite.hpp"
#include "Components/Text.hpp"

namespace arcade {

    AEntity::AEntity(const World::Entity& e) : m_oEnt(e)
    {
    }

    AEntity::~AEntity() { m_oEnt.Remove(); }

    template <typename T>
    void AEntity::AddComponent(component::IComponent& comp)
    {
        if (typeid(comp) == typeid(T)) {
            auto as = static_cast<T&>(comp);
            m_oEnt.AddComponent<T>(as);
        }
    }

    template <typename T>
    void AEntity::RemoveComponent(component::IComponent& comp)
    {
        if (typeid(comp) == typeid(T)) {
            auto as = static_cast<T&>(comp);
            m_oEnt.RemoveComponent<T>();
        }
    }

    // add component to entity
    void AEntity::addComponent(const component::IComponent& component)
    {
        component::IComponent& comp = const_cast<component::IComponent&>(component);

        AddComponent<component::Sprite>(comp);
        AddComponent<component::Transform>(comp);
        AddComponent<component::Text>(comp);
        AddComponent<component::AsciiSprite>(comp);
    }

    // remove component from entity
    void AEntity::removeComponent(const component::IComponent& component)
    {
        component::IComponent& comp = const_cast<component::IComponent&>(component);
        RemoveComponent<component::Sprite>(comp);
        RemoveComponent<component::Transform>(comp);
        RemoveComponent<component::Text>(comp);
        RemoveComponent<component::AsciiSprite>(comp);
    }

    // for each components from entity, execute fun
    void AEntity::forEach(std::function<void(component::IComponent&)> fun)
    {
        try { fun(m_oEnt.GetComponent<component::Transform>()); } catch(...) {}
        try { fun(m_oEnt.GetComponent<component::Sprite>()); } catch(...) {}
        try { fun(m_oEnt.GetComponent<component::Text>()); } catch(...) {}
        try { fun(m_oEnt.GetComponent<component::AsciiSprite>()); } catch(...) {}
    }
}