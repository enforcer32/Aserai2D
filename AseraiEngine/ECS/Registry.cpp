#include "AseraiEnginePCH.h"
#include "AseraiEngine/ECS/Registry.h"

namespace Aserai
{
	// Entity
	Entity::Entity()
		: m_ID(0), m_Registry(0), m_NULL(true)
	{
	}

	Entity::Entity(uint32_t id, Registry* registry)
		: m_ID(id), m_Registry(registry), m_NULL(false)
	{
	}

	uint32_t Entity::GetID()
	{
		return m_ID;
	}

	void Entity::Destroy()
	{
		m_Registry->DestroyEntity(*this);
	}

	// System
	void System::AddEntity(Entity entity)
	{
		m_Entities.push_back(entity);
	}

	void System::RemoveEntity(Entity entity)
	{
		m_Entities.erase(std::remove_if(m_Entities.begin(), m_Entities.end(), [&entity](Entity other)
			{
				return entity == other;
			}), m_Entities.end());
	}

	bool System::HasEntity(Entity entity)
	{
		return (std::find(m_Entities.begin(), m_Entities.end(), entity) != m_Entities.end());
	}

	std::vector<Entity> System::GetEntities() const
	{
		return m_Entities;
	}

	const Signature& System::GetComponentSignature() const
	{
		return m_ComponentSignature;
	}

	// System Manager
	void SystemManager::AddEntityToSystems(Entity entity, Signature entitySignature)
	{
		auto entityID = entity.GetID();

		for (auto& system : m_Systems)
		{
			auto& systemSignature = system.second->GetComponentSignature();
			if ((entitySignature & systemSignature) == systemSignature)
				system.second->AddEntity(entity);
		}
	}

	void SystemManager::RemoveEntityFromSystems(Entity entity)
	{
		for (auto& system : m_Systems)
			system.second->RemoveEntity(entity);
	}

	void SystemManager::EntityComponentRemoved(Entity entity, Signature entitySignature, int componentID)
	{
		auto entityID = entity.GetID();
		for (auto& system : m_Systems)
		{
			if (system.second->GetComponentSignature().test(componentID) && system.second->HasEntity(entity))
			{
				system.second->RemoveEntity(entity);
			}
		}
	}

	// Registry
	Registry::Registry()
		: m_EntityCount(0)
	{
		m_SystemManager = std::make_shared<SystemManager>();
	}

	Entity Registry::CreateEntity()
	{
		uint32_t id;
		if (!m_FreeIDs.empty())
		{
			id = m_FreeIDs.front();
			m_FreeIDs.pop_front();
		}
		else
		{
			id = m_EntityCount++;
			if (id >= m_EntityComponentSignatures.size())
				m_EntityComponentSignatures.resize(id + 1);
		}

		Entity entity(id, this);
		ASERAI_LOG_DEBUG("Entity({}) Created!", entity.GetID());
		return entity;
	}

	void Registry::DestroyEntity(Entity entity)
	{
		m_EntityDeleteQueue.insert(entity);
		ASERAI_LOG_DEBUG("Entity({}) Destroyed!", entity.GetID());
	}

	void Registry::Sync()
	{
		for (auto entity : m_EntityComponentAddedQueue)
			m_SystemManager->AddEntityToSystems(entity, m_EntityComponentSignatures[entity.GetID()]);
		m_EntityComponentAddedQueue.clear();

		for (auto entity : m_EntityDeleteQueue)
		{
			for (auto& pool : m_ComponentPools)
				if(pool)
					pool->RemoveEntity(entity.GetID());

			m_SystemManager->RemoveEntityFromSystems(entity);
			m_EntityComponentSignatures[entity.GetID()].reset();
			m_FreeIDs.push_back(entity.GetID());
		}
		m_EntityDeleteQueue.clear();
	}
}
