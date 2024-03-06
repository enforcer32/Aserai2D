#include "A2DEditorPCH.h"
#include "A2DEditor/Panels/ConsolePanel.h"

#include <A2DEngine/Core/Logger.h>

#include <imgui.h>

namespace Aserai2D
{
	void ConsolePanel::OnImGuiRender()
	{
		static bool autoScroll = true;
		static bool scrollToBottom = false;

		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Console"))
		{
			ImGui::End();
			return;
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &autoScroll);
			ImGui::EndPopup();
		}

		// Buttons
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
			Logger::Clear();
		ImGui::SameLine();
		bool copy_to_clipboard = ImGui::Button("Copy");

		ImGui::Separator();

		// Reserve enough left-over height for 1 separator + 1 input text
		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
		if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar))
		{
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::Selectable("Clear")) Logger::Clear();
				ImGui::EndPopup();
			}

			// - Split them into same height items would be simpler and facilitate random-seeking into your list.
			// - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
			if (copy_to_clipboard)
				ImGui::LogToClipboard();

			static const std::vector<std::string>& items = Logger::GetLogs();
			for (int i = 0; i < items.size(); i++)
			{
				const char* item = items[i].c_str();

				// Normally you would store more information in your item than just a string.
				// (e.g. make Items[] an array of structure, store color/type etc.)
				ImVec4 color;
				bool has_color = false;
				if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
				else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
				if (has_color)
					ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextUnformatted(item);
				if (has_color)
					ImGui::PopStyleColor();
			}
			if (copy_to_clipboard)
				ImGui::LogFinish();

			// Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
			// Using a scrollbar or mouse-wheel will take away from the bottom edge.
			if (scrollToBottom || (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
				ImGui::SetScrollHereY(1.0f);
			scrollToBottom = false;

			ImGui::PopStyleVar();
		}
		ImGui::EndChild();
		ImGui::Separator();

		ImGui::End();
	}
}
