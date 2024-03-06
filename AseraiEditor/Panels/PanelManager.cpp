#include "AseraiEditorPCH.h"
#include "AseraiEditor/Panels/PanelManager.h"

#include <AseraiEngine/Core/Logger.h>

namespace Aserai
{
	void PanelManager::AddPanel(const std::string& name, const std::shared_ptr<Panel>& panel)
	{
		if (m_Panels.find(name) == m_Panels.end())
			m_Panels[name] = panel;
	}

	std::shared_ptr<Panel> PanelManager::GetPanel(const std::string& name)
	{
		if (m_Panels.find(name) == m_Panels.end())
		{
			ASERAI_LOG_CRITICAL("GetPanel Not Found: {}", name);
			return nullptr;
		}

		return m_Panels[name];
	}

	void PanelManager::RenderAllPanels()
	{
		for (auto& panel : m_Panels)
			panel.second->OnImGuiRender();
	}
}
