/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Types.hpp header
*/

#pragma once

#include <bitset>
#include <cstdint>
#include <cstring>

constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
{
	return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
}

constexpr std::uint32_t operator ""_hash(char const* s, std::size_t count)
{
	return fnv1a_32(s, count);
}

inline std::uint32_t CreateEventId(char const* s)
{
	return fnv1a_32(s, strlen(s));
}


// ECS
using EntityId = std::uint32_t;
const EntityId MAX_ENTITIES = 5000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;


// Events
using EventId = std::uint32_t;
using ParamId = std::uint32_t;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

namespace Ecs
{
	namespace System
	{
		const ParamId DT = "Ecs::System::DT"_hash;
		const ParamId SYSTEM = "Ecs::System::SYSTEM"_hash;
		const ParamId ENTITY = "Ecs::System::ENTITY"_hash;
		const EventId OnAdd = "Ecs::System::OnAdd"_hash;
		const EventId OnRemove = "Ecs::System::OnRemove"_hash;
		const EventId OnSet = "Ecs::System::OnSet"_hash;
		const EventId OnUpdate = "Ecs::System::OnUpdate"_hash;
	}
}