/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ComponentArray.hpp header
*/

#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <unordered_map>
#include <exception>


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(EntityId entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	inline void InsertData(EntityId entity, T component)
	{
		if (m_vEntityToIndexMap.find(entity) != m_vEntityToIndexMap.end())
		{
			std::cerr << "Component added to same entity more than once." << std::endl;
			return;
		}

		// Put new entry at end
		size_t newIndex = m_lSize;
		m_vEntityToIndexMap[entity] = newIndex;
		m_vIndexToEntityMap[newIndex] = entity;
		// m_vComponents[newIndex] = component;
		m_vComponents.push_back(component);
		++m_lSize;
	}

	inline void RemoveData(EntityId entity)
	{
		if (m_vEntityToIndexMap.find(entity) == m_vEntityToIndexMap.end())
		{
			std::cerr << "'" << typeid(T).name() << "': Removing non-existent component." << std::endl;
			return;
		}

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = m_vEntityToIndexMap[entity];
		size_t indexOfLastElement = m_lSize - 1;
		m_vComponents[indexOfRemovedEntity] = m_vComponents[indexOfLastElement];

		// Update map to point to moved spot
		EntityId entityOfLastElement = m_vIndexToEntityMap[indexOfLastElement];
		m_vEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_vIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		m_vEntityToIndexMap.erase(entity);
		m_vIndexToEntityMap.erase(indexOfLastElement);
		m_vComponents.erase(m_vComponents.begin() + indexOfRemovedEntity);
		--m_lSize;
	}

	inline T& GetData(EntityId entity)
	{
		if(m_vEntityToIndexMap.find(entity) == m_vEntityToIndexMap.end())
			throw std::runtime_error("Retrieving non-existent component.");
		return m_vComponents[m_vEntityToIndexMap[entity]];
	}

	inline void EntityDestroyed(EntityId entity) override
	{
		if (m_vEntityToIndexMap.find(entity) != m_vEntityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::vector<T> m_vComponents;
	std::unordered_map<EntityId, size_t> m_vEntityToIndexMap;
	std::unordered_map<size_t, EntityId> m_vIndexToEntityMap;
	size_t m_lSize;
};