#pragma once

#include "AseraiEngine/ECS/Types.h"
#include "AseraiEngine/ECS/ComponentPool.h"
#include "AseraiEngine/Core/Logger.h"
#include "AseraiEngine/Core/Assertion.h"

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <set>
#include <memory>
#include <deque>

namespace Aserai
{
	class Registry;

	// Entity
	class Entity
	{
	public:
		Entity();
		Entity(uint32_t id, Registry* registry);
		Entity(const Entity& entity) = default;

		uint32_t GetID();
		void Destroy();

		Entity& operator=(const Entity& rhs) = default;

		bool operator==(const Entity& rhs) const
		{
			return m_ID == rhs.m_ID;
		}

		bool operator!=(const Entity& rhs) const
		{
			return m_ID != rhs.m_ID;
		}

		bool operator>(const Entity& rhs) const
		{
			return m_ID > rhs.m_ID;
		}

		bool operator<(const Entity& rhs) const
		{
			return m_ID < rhs.m_ID;
		}

		template<typename T, typename ...Args>
		void AddComponent(Args&& ...args);

		template<typename T>
		void RemoveComponent();

		template<typename T>
		bool HasComponent() const;

		template<typename T>
		T& GetComponent();

		operator bool() const { return !m_NULL; }

	private:
		uint32_t m_ID;
		Registry* m_Registry;
		bool m_NULL;
	};

	// System
	class System
	{
	public:
		virtual ~System() = default;

		void AddEntity(Entity entity);
		void RemoveEntity(Entity entity);
		bool HasEntity(Entity entity);
		std::vector<Entity> GetEntities() const;
		const Signature& GetComponentSignature() const;

		template<typename T>
		void RegisterComponent()
		{
			uint32_t componentID = Component<T>::GetID();
			m_ComponentSignature.set(componentID);
		}

	private:
		Signature m_ComponentSignature;
		std::vector<Entity> m_Entities;
	};

	// SystemManager
	class SystemManager
	{
	public:
		void AddEntityToSystems(Entity entity, Signature entitySignature);
		void RemoveEntityFromSystems(Entity entity);
		void EntityComponentRemoved(Entity entity, Signature entitySignature, int componentID);

		template<typename T, typename ...Args>
		void AddSystem(Args&& ...args)
		{
			m_Systems[std::type_index(typeid(T))] = std::make_shared<T>(std::forward<Args>(args)...);
			ASERAI_LOG_DEBUG("System({}) Added!", (typeid(T).name()));
		}

		template<typename T>
		void RemoveSystem()
		{
			m_Systems.erase(m_Systems.find(std::type_index(typeid(T))));
			ASERAI_LOG_DEBUG("System({}) Removed!", typeid(T).name());
		}

		template<typename T>
		bool HasSystem() const
		{
			return m_Systems.find(std::type_index(typeid(T))) != m_Systems.end();
		}

		template<typename T>
		T& GetSystem()
		{
			ASERAI_ASSERT((m_Systems.find(std::type_index(typeid(T))) != m_Systems.end()), "");
			auto it = m_Systems.find(std::type_index(typeid(T)));
			return *(std::static_pointer_cast<T>(it->second));
		}

	private:
		std::unordered_map<std::type_index, std::shared_ptr<System>> m_Systems;
	};

	// Registry
	class Registry
	{
	public:
		Registry();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void Sync();

		// Components
		template<typename T, typename ...Args>
		void AddComponent(Entity entity, Args&& ...args)
		{
			auto entityID = entity.GetID();
			auto componentID = Component<T>::GetID();

			if (componentID >= m_ComponentPools.size())
				m_ComponentPools.resize(componentID + 1);

			if (!m_ComponentPools[componentID])
				m_ComponentPools[componentID] = std::make_shared<ComponentPool<T>>();

			std::shared_ptr<ComponentPool<T>> componentPool = std::static_pointer_cast<ComponentPool<T>>(m_ComponentPools[componentID]);

			T component(std::forward<Args>(args)...);
			componentPool->Set(entityID, component);

			m_EntityComponentSignatures[entityID].set(componentID);
			m_EntityComponentAddedQueue.insert(entity);
			ASERAI_LOG_DEBUG("Entity({}) Added Component({})", entityID, componentID);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			auto entityID = entity.GetID();
			auto componentID = Component<T>::GetID();
			if (componentID >= m_ComponentPools.size())
				return;
			std::shared_ptr<ComponentPool<T>> componentPool = std::static_pointer_cast<ComponentPool<T>>(m_ComponentPools[componentID]);
			componentPool->Remove(entityID);
			m_EntityComponentSignatures[entityID].set(componentID, false);
			m_SystemManager->EntityComponentRemoved(entity, m_EntityComponentSignatures[entity.GetID()], componentID);
			ASERAI_LOG_DEBUG("Entity({}) Removed Component({})", entityID, componentID);
		}

		template<typename T>
		bool HasComponent(Entity entity)
		{
			auto entityID = entity.GetID();
			auto componentID = Component<T>::GetID();
			return m_EntityComponentSignatures[entityID].test(componentID);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			auto entityID = entity.GetID();
			auto componentID = Component<T>::GetID();
			auto pool = std::static_pointer_cast<ComponentPool<T>>(m_ComponentPools[componentID]);
			return pool->Get(entityID);
		}

		// Systems
		template<typename T, typename ...Args>
		void AddSystem(Args&& ...args)
		{
			m_SystemManager->AddSystem<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveSystem()
		{
			m_SystemManager->RemoveSystem<T>();
		}

		template<typename T>
		bool HasSystem() const
		{
			return m_SystemManager->HasSystem<T>();
		}

		template<typename T>
		T& GetSystem()
		{
			return m_SystemManager->GetSystem<T>();
		}

		template<typename T>
		std::vector<Entity> GetEntitiesWithComponent()
		{
			std::vector<Entity> entities;
			auto componentID = Component<T>::GetID();
			for (uint32_t i = 0; i < m_EntityComponentSignatures.size(); i++)
			{
				if (m_EntityComponentSignatures[i].test(componentID))
					entities.push_back({ i, this });
			}
			return entities;
		}

	private:
		uint32_t m_EntityCount;
		std::vector<Signature> m_EntityComponentSignatures;
		std::vector<std::shared_ptr<IPool>> m_ComponentPools;

		std::shared_ptr<SystemManager> m_SystemManager;

		std::set<Entity> m_EntityDeleteQueue;
		std::set<Entity> m_EntityComponentAddedQueue;

		std::deque<uint32_t> m_FreeIDs;
	};

	// Entity
	template<typename T, typename ...Args>
	void Entity::AddComponent(Args&& ...args)
	{
		m_Registry->AddComponent<T>(*this, std::forward<Args>(args)...);
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		m_Registry->RemoveComponent<T>(*this);
	}

	template<typename T>
	bool Entity::HasComponent() const
	{
		return m_Registry->HasComponent<T>(*this);
	}

	template<typename T>
	T& Entity::GetComponent()
	{
		return m_Registry->GetComponent<T>(*this);
	}
}
