/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ComponentManager.hpp header
*/

#pragma once

#include <memory>
#include <unordered_map>
#include "ComponentArray.hpp"
#include "Types.hpp"
#include "Exceptions/AException.hpp"
#include "Exceptions/InitException.hpp"

// template <typename Component>
// struct ComponentArray {
// 	using Type = std::unordered_map<EntityId, Component>;
// };

class ComponentManager
{
public:
	template<typename T>
	inline void RegisterComponent()
	{
		if (ComponentIsRegistered<T>())
			throw AException("Registering component type more than once.");

		auto pArray = std::make_shared<ComponentArray<T>>();
		if (!pArray)
			throw InitException("Component Array allocation failed.");
		m_vComponentTypes.emplace(typeid(T).hash_code(), m_uNextComponentType);
		m_vComponentArrays.emplace(typeid(T).hash_code(), pArray);

		++m_uNextComponentType;
	}

	template<typename T>
	inline ComponentType GetComponentType()
	{
		if (!ComponentIsRegistered<T>())
			throw AException("Component '" + std::string(typeid(T).name()) + "' not registered before use.");

		return m_vComponentTypes[typeid(T).hash_code()];
	}

	template<typename T>
	inline bool ComponentIsRegistered()
	{
		return m_vComponentTypes.find(typeid(T).hash_code()) != m_vComponentTypes.end();
	}

	template<typename T>
	inline void AddComponent(EntityId entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template <typename T, typename... Args,
		typename = std::enable_if_t<std::is_object<T>::value
			&& std::is_constructible<T, Args...>::value>>
	inline void AddComponent(EntityId entity, Args&&... args)
	{
		GetComponentArray<T>()->InsertData(entity, T(std::forward<Args>(args)...));
	}

	template<typename T>
	inline void RemoveComponent(EntityId entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	inline T& GetComponent(EntityId entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	inline void EntityDestroyed(EntityId entity)
	{
		for (auto const& pair : m_vComponentArrays) {
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<std::size_t, ComponentType> m_vComponentTypes;
	std::unordered_map<std::size_t, std::shared_ptr<IComponentArray>> m_vComponentArrays;
	ComponentType m_uNextComponentType;


	template<typename T>
	inline std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		if (!ComponentIsRegistered<T>())
			throw AException("Component '" + std::string(typeid(T).name()) + "' not registered before use.");
		return std::static_pointer_cast<ComponentArray<T>>(m_vComponentArrays[typeid(T).hash_code()]);
	}
};