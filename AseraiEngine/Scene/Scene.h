#pragma once

#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Renderer/Renderer2D.h"

#include <string>
#include <memory>

namespace Aserai
{
	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled");

		void OnRuntimeUpdate(DeltaTime dt);
		void OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D> renderer);

		void SetName(const std::string& name);
		const std::string& GetName() const;

	private:
		std::string m_Name;
	};

}
