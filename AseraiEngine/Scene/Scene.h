#pragma once

#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Renderer/Renderer2D.h"
#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/InputManager.h"

#include <string>
#include <memory>

namespace Aserai
{
	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled");

		void OnRuntimeUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager);
		void OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string& name = "");
		void DestroyEntity(Entity entity);
		Entity GetPrimaryCamera();

		void SetName(const std::string& name);
		const std::string& GetName() const;

	private:
		std::shared_ptr<Registry> m_Registry;
		std::string m_Name;
	};
}
