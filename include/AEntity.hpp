/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** AEntity.hpp header
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <typeindex>
#include <unordered_map>
#include <iostream>
#include <memory>
#include "IEntity.hpp"
// #include "Core/ComponentManager.hpp"
#include "Core/World.hpp"

namespace arcade {

class AEntity : public IEntity {
public:
    AEntity(const World::Entity& e);
    // AEntity(Entity e);
    virtual ~AEntity();

    template <typename T>
    void AddComponent(component::IComponent& comp);
    template <typename T>
    void RemoveComponent(component::IComponent& comp);

    // add component to entity
    void addComponent(const component::IComponent& component) override;
    // remove component from entity
    void removeComponent(const component::IComponent& component) override;

    // for each components from entity, execute fun
    void forEach(
        std::function<void(component::IComponent&)> fun) override;

protected:
private:
    World::Entity m_oEnt;
};

}

#endif /* !IENTITY_HPP_ */