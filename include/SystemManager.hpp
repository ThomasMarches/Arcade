/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** SystemManager.hpp header
*/

#pragma once

#include <iostream>
#include <memory>
#include <set>
#include <functional>
#include <type_traits>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "Core/EventManager.hpp"
#include "Core/Types.hpp"
#include "IEntity.hpp"
#include "IScene.hpp"

namespace arcade {
    using SystemFn = std::function<void(Event&, arcade::IEntity&)>;
    using SystemFn2 = std::function<void(Event&, arcade::IEntity&, const arcade::EntityList&)>;

    // @brief The System is used to perform the logic
    class System
    {
    public:
        EventManager& m_oEventManager;
        arcade::IScene& m_oScene;
        std::string name;											// The name of the system, used to generate unique Id for the different Event Phases like OnAdd or OnRemove
        arcade::EntityList m_Entities;								// List of all entities who match with the key signature of the System

        explicit System(arcade::IScene& oScene, EventManager& oEventManager) : m_oScene(oScene), m_oEventManager(oEventManager) {	}

        // @brief This function store a function for this System that will be called on the OnUpdate Phase
        void each(SystemFn updateFunc);
        void each(SystemFn2 updateFunc);

        // @brief This function allows to add a listener to an event
        System& kind(EventId id, SystemFn func);
        System& kind(EventId id, SystemFn2 func);

    private:
        void UpdatePhase(Event& event)
        {
            m_oScene.forEach([&](arcade::IEntity& e) {
                m_Func(event, e);
            });
        }

        void UpdatePhase2(Event& event)
        {
            m_Entities.clear();
            m_oScene.forEach([&](arcade::IEntity& e) {
                m_Entities.push_back(e);
            });
            for (auto ent : m_Entities) {
                m_Func2(event, ent, m_Entities);
            }
        }

        SystemFn m_Func;
        SystemFn2 m_Func2;
    };

    // @brief This is the Manager of all System class
    class SystemManager
    {
    public:
        SystemManager() { }
        // @brief This function allows to add a new System
        std::shared_ptr<System> RegisterSystem(arcade::IScene& oScene, EventManager& pWorld, std::string& name)
        {
            if (name.empty())
                name = "System_" + std::to_string(m_vSystems.size());

            assert(m_vSystems.find(name.c_str()) == m_vSystems.end() && "Registering system more than once.");

            auto system = std::make_shared<System>(oScene, pWorld);
            system->name = name;
            m_vSystems.insert({name, system});
            return system;
        }

        // @brief This function allows to add a Signature to the System who match with the name given in parameter
        void SetSignature(Signature signature, std::string& name)
        {
            assert(m_vSystems.find(name.c_str()) != m_vSystems.end() && "System used before registered.");

            m_vSignatures.insert({name.c_str(), signature});
        }

        // @brief This function allows to get the Signature who match with the name given in parameter
        void GetSignature(std::string& name)
        {
            if (m_vSystems.find(name) != m_vSystems.end())
                m_vSignatures[name];
            else
                std::cerr << "The System '" << name << "' have no signature.";
        }

        std::shared_ptr<System> CreateSystem(arcade::IScene& oScene, EventManager& manager, std::string name = "")
        {
            auto system = RegisterSystem(oScene, manager, name);
            return system;
        }

        void clear()
        {
            m_vSignatures.clear();
            m_vSystems.clear();
        }

    private:

        std::unordered_map<std::string, Signature> m_vSignatures;
        std::unordered_map<std::string, std::shared_ptr<System>> m_vSystems;
    };

    // -----------------------------------
    // --       System Functions        --
    // -----------------------------------

    inline void System::each(SystemFn updateFunc)
    {
        kind(Ecs::System::OnUpdate, updateFunc);
    }

    inline System& System::kind(EventId id, SystemFn func)
    {
        m_oEventManager.AddListener(METHOD_LISTENER(id, System::UpdatePhase));
        m_Func = func;
        return *this;
    }

    inline void System::each(SystemFn2 updateFunc)
    {
        kind(Ecs::System::OnUpdate, updateFunc);
    }

    inline System& System::kind(EventId id, SystemFn2 func)
    {
        m_oEventManager.AddListener(METHOD_LISTENER(id, System::UpdatePhase2));
        m_Func2 = func;
        return *this;
    }
}