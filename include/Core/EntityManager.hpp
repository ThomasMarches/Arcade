/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** EntityManager.hpp header
*/

#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <queue>


class EntityManager
{
public:
	EntityManager()
	{
		for (EntityId entity = 0; entity < MAX_ENTITIES; ++entity)
			m_vAvailableEntities.push(entity);
	}

	EntityId CreateEntity()
	{
		// assert(m_uLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		EntityId id = m_vAvailableEntities.front();
		m_vAvailableEntities.pop();
		++m_uLivingEntityCount;

		return id;
	}

	void DestroyEntity(EntityId entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		m_vSignatures[entity].reset();
		m_vAvailableEntities.push(entity);
		--m_uLivingEntityCount;
	}

	void SetSignature(EntityId entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		m_vSignatures[entity] = signature;
	}

	Signature GetSignature(EntityId entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		return m_vSignatures[entity];
	}

private:
	std::queue<EntityId> m_vAvailableEntities;
	std::array<Signature, MAX_ENTITIES> m_vSignatures;
	uint32_t m_uLivingEntityCount;
};