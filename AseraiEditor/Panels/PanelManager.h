#pragma once

#include "AseraiEditor/Panels/Panel.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Aserai
{
	class PanelManager
	{
	public:
		void AddPanel(const std::string& name, const std::shared_ptr<Panel>& panel);
		std::shared_ptr<Panel> GetPanel(const std::string& name);
		void RenderAllPanels();

		template<typename T>
		std::shared_ptr<T> GetPanel(const std::string& name)
		{
			return std::dynamic_pointer_cast<T>(GetPanel(name));
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<Panel>> m_Panels;
	};
}
