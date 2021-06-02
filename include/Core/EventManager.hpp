/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** EventManager.hpp header
*/

#pragma once

#include "Event.hpp"
#include "Types.hpp"
#include <functional>
#include <list>
#include <unordered_map>

#define CELL_SIZE 20

class EventManager
{
public:
	void AddListener(EventId eventId, std::function<void(Event&)> const& listener)
	{
		m_vListeners[eventId].push_back(listener);
	}

	template <class A>
	void process_one_type(std::string& strEvent)
	{
		strEvent += typeid(A).name();
	}

	void SendEvent(Event& event)
	{
		uint32_t type = event.GetType();

		for (auto const& listener : m_vListeners[type])
		{
			listener(event);
		}
	}

	void SendEvent(EventId eventId)
	{
		Event event(eventId);

		for (auto const& listener : m_vListeners[eventId])
		{
			listener(event);
		}
	}

	void clear()
	{
		m_vListeners.clear();
	}

private:
	std::unordered_map<EventId, std::list<std::function<void(Event&)>>> m_vListeners;
};