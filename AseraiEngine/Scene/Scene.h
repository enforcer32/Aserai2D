#pragma once

#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Renderer/Renderer2D.h"
#include "AseraiEngine/ECS/Registry.h"

#include <string>
#include <memory>

namespace Aserai
{
	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled");

		void OnRuntimeUpdate(DeltaTime dt);
		void OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer);

		Entity CreateEntity(const std::string& name = "");
		void DestroyEntity(Entity entity);

		void SetName(const std::string& name);
		const std::string& GetName() const;

	private:
		std::shared_ptr<Registry> m_Registry;
		std::string m_Name;
	};
}
