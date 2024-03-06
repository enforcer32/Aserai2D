#pragma once

#include "AseraiEngine/Core/Assertion.h"

#include <vector>
#include <unordered_map>

namespace Aserai
{
	class IPool
	{
	public:
		virtual ~IPool() = default;
		virtual void RemoveEntity(uint32_t entityID) = 0;
	};

	template<typename T>
	class ComponentPool : public IPool
	{
	public:
		ComponentPool(uint32_t size = 1024)
			: m_Size(0)
		{
			Resize(size);
		}

		virtual ~ComponentPool() = default;

		void Set(uint32_t entityID, T component)
		{
			if (m_EntityIDToIndex.find(entityID) == m_EntityIDToIndex.end())
			{
				uint32_t index = m_Size;
				m_EntityIDToIndex[entityID] = index;
				m_IndexToEntityID[index] = entityID;

				if (index >= m_Components.capacity())
					m_Components.resize(m_Size * 2);

				m_Components[index] = component;
				m_Size++;
			}
			else
			{
				m_Components[m_EntityIDToIndex[entityID]] = component;
			}
		}

		void Remove(uint32_t entityID)
		{
			if (m_EntityIDToIndex.find(entityID) == m_EntityIDToIndex.end()) return;

			uint32_t entityIndex = m_EntityIDToIndex[entityID];
			uint32_t lastIndex = m_Size - 1;
			m_Components[entityIndex] = m_Components[lastIndex];
			m_Size--;
	
			int lastEntityID = m_IndexToEntityID[lastIndex];
			m_EntityIDToIndex[lastEntityID] = entityIndex;
			m_IndexToEntityID[entityIndex] = lastEntityID;

			m_EntityIDToIndex.erase(entityID);
			m_IndexToEntityID.erase(lastIndex);
		}

		T& Get(uint32_t entityID)
		{
			ASERAI_ASSERT((m_EntityIDToIndex.find(entityID) != m_EntityIDToIndex.end()), "");
			return (T&)m_Components[m_EntityIDToIndex[entityID]];
		}

		void Resize(uint32_t n)
		{
			m_Components.resize(n);
		}

		uint32_t GetSize() const
		{
			return m_Size;
		}

		void Clear()
		{
			m_Components.clear();
			m_Size = 0;
		}

		bool IsEmpty() const
		{
			return m_Size == 0;
		}

		virtual void RemoveEntity(uint32_t entityID) override
		{
			if (m_EntityIDToIndex.find(entityID) != m_EntityIDToIndex.end())
				Remove(entityID);
		}

	private:
		std::vector<T> m_Components;
		uint32_t m_Size;
		std::unordered_map<uint32_t, uint32_t> m_EntityIDToIndex;
		std::unordered_map<uint32_t, uint32_t> m_IndexToEntityID;
	};
}
