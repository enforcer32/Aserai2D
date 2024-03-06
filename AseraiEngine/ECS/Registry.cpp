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

	void Entity::SetTag(const std::string& tag)
	{
		m_Registry->SetEntityTag(*this, tag);
	}

	const std::string& Entity::GetTag() const
	{
		return m_Registry->GetEntityTag(*this);
	}

	void Entity::SetGroup(const std::string& group)
	{
		m_Registry->SetEntityGroup(*this, group);
	}

	const std::string& Entity::GetGroup() const
	{
		return m_Registry->GetEntityGroup(*this);
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
		m_Entities.push_back(entity);
		ASERAI_LOG_DEBUG("Entity({}) Created!", entity.GetID());
		return entity;
	}

	void Registry::DestroyEntity(Entity entity)
	{
		m_EntityDeleteQueue.insert(entity);
		m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
		ASERAI_LOG_DEBUG("Entity({}) Destroyed!", entity.GetID());
	}

	const std::vector<Entity>& Registry::GetEntities()
	{
		return m_Entities;
	}

	void Registry::SetEntityTag(Entity entity, const std::string& tag)
	{
		if (!tag.empty())
		{
			m_TagToEntity[tag] = entity;
			m_EntityIDToTag[entity.GetID()] = tag;
		}
	}

	const std::string& Registry::GetEntityTag(Entity entity)
	{
		return m_EntityIDToTag[entity.GetID()];
	}

	Entity Registry::GetEntityByTag(const std::string& tag)
	{
		if (m_TagToEntity.find(tag) != m_TagToEntity.end())
			return m_TagToEntity[tag];
		return {};
	}
	
	void Registry::RemoveEntityTag(Entity entity)
	{
		if (m_EntityIDToTag.find(entity.GetID()) != m_EntityIDToTag.end())
		{
			m_TagToEntity.erase(m_EntityIDToTag[entity.GetID()]);
			m_EntityIDToTag.erase(entity.GetID());
		}
	}

	void Registry::SetEntityGroup(Entity entity, const std::string& group)
	{
		if (!group.empty())
		{
			m_GroupToEntities.emplace(group, std::set<Entity>());
			m_GroupToEntities[group].emplace(entity);
			m_EntityIDToGroup[entity.GetID()] = group;
		}
	}

	const std::string& Registry::GetEntityGroup(Entity entity)
	{
		return m_EntityIDToGroup[entity.GetID()];
	}
	
	std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& name)
	{
		auto& entities = m_GroupToEntities[name];
		return std::vector<Entity>(entities.begin(), entities.end());
	}

	std::unordered_map<uint32_t, std::string> m_EntityIDToGroup;
	std::unordered_map<std::string, std::set<Entity>> m_GroupToEntities;

	void Registry::RemoveEntityGroup(Entity entity)
	{
		auto group = m_EntityIDToGroup.find(entity.GetID());
		if (group != m_EntityIDToGroup.end())
		{
			auto groupSet = m_GroupToEntities.find(group->second);
			if (groupSet != m_GroupToEntities.end())
			{
				auto ent = groupSet->second.find(entity);
				if (ent != groupSet->second.end())
					groupSet->second.erase(ent);
			}
		}

		m_EntityIDToGroup.erase(entity.GetID());
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
