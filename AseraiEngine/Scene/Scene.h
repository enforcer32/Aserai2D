#pragma once

#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Renderer/Renderer2D.h"
#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/InputManager.h"
#include "AseraiEngine/Core/EventManager.h"
#include "AseraiEngine/Systems/RenderSystem.h"

#include <string>
#include <memory>

namespace Aserai
{
	const uint32_t MAX_SCENE_SYSTEMS = 1024;

	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled");

		void OnRuntimeUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager, const std::shared_ptr<EventManager>& eventManager);
		void OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer, const std::shared_ptr<InputManager>& inputManager);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string& name = "");
		void DestroyEntity(Entity entity);
		Entity GetPrimaryCamera();

		void SetName(const std::string& name);
		const std::string& GetName() const;

		template<typename T>
		void EnableSystem()
		{
			auto systemID = BaseSystem<T>::GetID();
			if (!m_SystemSignature.test(systemID))
			{
				m_Registry->AddSystem<T>();
				m_Systems[systemID] = &m_Registry->GetSystem<T>();
				m_SystemSignature.set(systemID);
			}
		}
		
		template<typename T>
		void DisableSystem()
		{
			auto systemID = BaseSystem<T>::GetID();
			if (systemID == BaseSystem<RenderSystem>::GetID())
			{
				ASERAI_LOG_ERROR("Cannot Disable RenderSystem");
				return;
			}

			if (m_SystemSignature.test(systemID))
			{
				m_Registry->RemoveSystem<T>();
				m_Systems[systemID] = nullptr;
				m_SystemSignature.set(systemID, false);
			}
		}

		template<typename T>
		bool IsSystemEnabled()
		{
			return m_SystemSignature.test(BaseSystem<T>::GetID());
		}

		template<typename T>
		T* GetSystem()
		{
			return static_cast<T*>(m_Systems[BaseSystem<T>::GetID()]);
		}

	private:
		std::shared_ptr<Registry> m_Registry;
		std::unordered_map<uint32_t, System*> m_Systems;
		std::bitset<MAX_SCENE_SYSTEMS> m_SystemSignature;
		std::string m_Name;
	};
}
