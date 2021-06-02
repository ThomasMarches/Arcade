/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Event.hpp header
*/

#pragma once

#include "Types.hpp"
#include <unordered_map>
#include "Exceptions/CastException.hpp"

class Event
{
public:
	Event() : m_uType(-1) { };
	~Event()
	{
		// for (auto& it : m_vData)
		// 	delete it.second;
	}

	explicit Event(EventId type) : m_uType(type) { }

	template<typename T>
	void SetParam(EventId id, T& value)
	{
		// if (m_vData[id])
		// 	delete m_vData[id];
		// m_vData[id] = new T(value);
		m_vData[id] = &value;
	}

	template<typename T>
	T GetParam(EventId id)
	{
		T *p_Data = static_cast<T*>(m_vData[id]);

		if (!p_Data)
			throw CastException("Conversion failed.");
		return *p_Data;
	}

	EventId GetType() const
	{
		return m_uType;
	}

	void SetType(EventId iType)
	{
		m_uType = iType;
	}

private:
	EventId m_uType;
	std::unordered_map<EventId, void*> m_vData;
};