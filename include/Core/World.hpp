/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** World.hpp header
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
#include <typeindex>

#include "Types.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"

class World;

using SystemFn = std::function<void(Event&, World&, EntityId&)>;
using SystemFn2 = std::function<void(Event&, World&, EntityId&, const std::set<EntityId>&)>;

// @brief The System is used to perform the logic
class System
{
public:
	World& m_oWorld;
	std::string name;											// The name of the system, used to generate unique Id for the different Event Phases like OnAdd or OnRemove
	std::set<EntityId> m_Entities;								// List of all entities who match with the key signature of the System

	explicit System(World& oWorld) : m_oWorld(oWorld) {	}

	void each(SystemFn updateFunc);
	void each(SystemFn2 updateFunc);

	// @brief This function allows to add a listener to an event
	System& kind(EventId id, SystemFn func);
	System& kind(EventId id, SystemFn2 func);

private:
	void UpdatePhase(Event& event)
	{
		// m_Entities = m_oWorld.Get<arcade::Scene>().getEntity("");
		for (auto ent : m_Entities) {
			m_Func(event, m_oWorld, ent);
		}
	}

	void UpdatePhase2(Event& event)
	{
		// m_Entities = m_oWorld.Get<arcade::Scene>().getEntity("");
		for (auto ent : m_Entities) {
			m_Func2(event, m_oWorld, ent, m_Entities);
		}
	}

	void Phase(Event& event)
	{
		EntityId ent = event.GetParam<EntityId>(Ecs::System::ENTITY);
		m_Func(event, m_oWorld, ent);
	}

	SystemFn m_Func;
	SystemFn2 m_Func2;
};

// @brief This is the Manager of all System class
class SystemManager
{
public:
	// @brief This function allows to add a new System
	std::shared_ptr<System> RegisterSystem(World* pWorld, std::string& name)
	{
        if (name.empty())
            name = "System_" + std::to_string(m_vSystems.size());

		assert(m_vSystems.find(name.c_str()) == m_vSystems.end() && "Registering system more than once.");

		auto system = std::make_shared<System>(*pWorld);
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

	// @brief This function allows to delete a entity in the system list
	void EntityDestroyed(EntityId entity)
	{
		for (auto const& pair : m_vSystems)
		{
			auto const& system = pair.second;

			system->m_Entities.erase(entity);
		}
	}

	// @brief This function remove/add the entity, given in parameter, in the system list and it trigger a OnAdd/OnRemove event
	void EntitySignatureChanged(EntityId entity, Signature entitySignature);

private:
	std::unordered_map<std::string, Signature> m_vSignatures{};
	std::unordered_map<std::string, std::shared_ptr<System>> m_vSystems{};
};


class World
{
public:
	explicit World()
	{
		m_EventManager = std::make_unique<EventManager>();
		m_EntityManager = std::make_unique<EntityManager>();
		m_ComponentManager = std::make_unique<ComponentManager>();
		m_SystemManager = std::make_unique<SystemManager>();
	}

	class Entity {
        public:
            Entity(World& w, EntityId id) : m_oWld(w), m_iId(id) { }

            Entity(const Entity&) = default;

            bool operator==(const Entity& e) const
			{
				return m_iId == e.id() && &m_oWld == &e.m_oWld;
			}

            bool operator!=(const Entity& other) const
			{
				return !(*this == other);
			}

            void Remove()
			{
				m_oWld.DestroyEntity(m_iId);
			}

            template <typename T, typename... Args,
                typename = std::enable_if_t<std::is_object<T>::value
                    && std::is_constructible<T, Args...>::value>>
            T& AddComponent(Args&&... args)
            {
                return m_oWld.AddComponent<T>(
                    m_iId, std::forward<Args>(args)...);
            }

			template <typename T,
                typename = std::enable_if_t<std::is_object<T>::value>>
            T& GetComponent()
            {
                return m_oWld.GetComponent<T>(m_iId);
            }

            template <typename T,
                typename = std::enable_if_t<std::is_object<T>::value>>
            void RemoveComponent()
            {
                m_oWld.RemoveComponent<T>(m_iId);
            }

            EntityId id() const
            {
                return m_iId;
            }

        private:
            World& m_oWld;
            EntityId m_iId;
	};

	// @brief This function allows to create a new entity
	Entity CreateEntity()
	{
		return { *this, m_EntityManager->CreateEntity() };
	}

	// @brief This function allows to destroy the entity, given in parameter
	void DestroyEntity(EntityId entity)
	{
		m_EntityManager->DestroyEntity(entity);
		m_ComponentManager->EntityDestroyed(entity);
		m_SystemManager->EntityDestroyed(entity);
	}

	// @brief This function allows to register an new Component
	template<typename T>
	void RegisterComponent()
	{
		m_ComponentManager->RegisterComponent<T>();
	}

	// @brief This function allows to add an Component in the entity
	template<typename T>
	T& AddComponent(EntityId entity, T component)
	{
		if (!m_ComponentManager->ComponentIsRegistered<T>())
			m_ComponentManager->RegisterComponent<T>();

		m_ComponentManager->AddComponent<T>(entity, component);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(GetComponentType<T>(), true);
		m_EntityManager->SetSignature(entity, signature);

		m_SystemManager->EntitySignatureChanged(entity, signature);
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template <typename T, typename... Args,
		typename = std::enable_if_t<std::is_object<T>::value
			&& std::is_constructible<T, Args...>::value>>
	T& AddComponent(EntityId entity, Args&&... args)
	{
		if (!m_ComponentManager->ComponentIsRegistered<T>())
			m_ComponentManager->RegisterComponent<T>();

		m_ComponentManager->AddComponent<T>(entity, std::forward<Args>(args)...);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(GetComponentType<T>(), true);
		m_EntityManager->SetSignature(entity, signature);

		m_SystemManager->EntitySignatureChanged(entity, signature);
		return m_ComponentManager->GetComponent<T>();
	}

	// @brief This function allows to remove an Component in the entity
	template<typename T>
	void RemoveComponent(EntityId ent)
	{
		m_ComponentManager->RemoveComponent<T>(ent);

		auto signature = m_EntityManager->GetSignature(ent);
		signature.set(GetComponentType<T>(), false);
		m_EntityManager->SetSignature(ent, signature);
		m_SystemManager->EntitySignatureChanged(ent, signature);
	}

	// @brief This function allows to get the Component in the entity
	template<typename T>
	T& GetComponent(EntityId entity)
	{
		// using Array = typename ComponentStorage<T>::Type;

		// return Get<Array>().AndThen(
		// 	[=](Array& array) { return Just(array.at(ent)); });
		return m_ComponentManager->GetComponent<T>(entity);
	}
	
	// @brief This function allows to register and create a new System
	// std::shared_ptr<System> CreateSystem(std::string name = "")
	// {
	// 	return m_SystemManager->CreateSystem(*this, name);
	// }

	// @brief This function allows to get the type of a Component
	template<typename T>
	ComponentType GetComponentType()
	{
		if (!m_ComponentManager->ComponentIsRegistered<T>())
			RegisterComponent<T>();

		return m_ComponentManager->GetComponentType<T>();
	}

	template <class A>
	void process_one_type(Signature& signature)
	{
		signature.set(GetComponentType<A>());
	}

	template<typename... Comps>
	std::shared_ptr<System> CreateSystem(std::string name = "")
	{
		auto system = m_SystemManager->RegisterSystem(this, name);

		Signature signature;
		int _[] = {0, (process_one_type<Comps>(signature), 0)...};
		m_SystemManager->SetSignature(signature, name);
		return system;
	}

	void AddListener(EventId eventId, std::function<void(Event&)> const& listener)
	{
		m_EventManager->AddListener(eventId, listener);
	}

	// @brief This function allows to trigger an event
	void SendEvent(Event& event)
	{
		m_EventManager->SendEvent(event);
	}

	// @brief This function allows to trigger an event
	void SendEvent(EventId eventId)
	{
		m_EventManager->SendEvent(eventId);
	}

private:

	std::unique_ptr<EventManager> m_EventManager;
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::unique_ptr<SystemManager> m_SystemManager;
};

// -----------------------------------
// --       System Functions        --
// -----------------------------------

inline void SystemManager::EntitySignatureChanged(EntityId entity, Signature entitySignature)
{
	for (auto const& pair : m_vSystems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = m_vSignatures[type];

		if ((entitySignature & systemSignature) == systemSignature)
		{
			bool bIsExist = system->m_Entities.find(entity) != system->m_Entities.end();
			system->m_Entities.insert(entity);

			// Si il n'existe pas, Envoyez l'event OnAdd
			if (!bIsExist)
			{
				Event event(fnv1a_32(system->name.c_str(), system->name.size()) + Ecs::System::OnAdd);
				event.SetParam<EntityId>(Ecs::System::ENTITY, entity);
				system->m_oWorld.SendEvent(event);
			}
		}
		else
		{
			bool bIsExist = system->m_Entities.find(entity) != system->m_Entities.end();
			if (bIsExist)
			{
				Event event(fnv1a_32(system->name.c_str(), system->name.size()) + Ecs::System::OnRemove);
				event.SetParam<EntityId>(Ecs::System::ENTITY, entity);
				system->m_oWorld.SendEvent(event);
			}
			system->m_Entities.erase(entity);
		}
	}
}

inline void System::each(SystemFn updateFunc)
{
	kind(Ecs::System::OnUpdate, updateFunc);
}

inline System& System::kind(EventId id, SystemFn func)
{
	m_oWorld.AddListener(METHOD_LISTENER(id, System::UpdatePhase));
	m_Func = func;
	return *this;
}

inline void System::each(SystemFn2 updateFunc)
{
	kind(Ecs::System::OnUpdate, updateFunc);
}

inline System& System::kind(EventId id, SystemFn2 func)
{
	m_oWorld.AddListener(METHOD_LISTENER(id, System::UpdatePhase2));
	m_Func2 = func;
	return *this;
}