#include "AseraiEnginePCH.h"
#include "AseraiEngine/ImGui/AImGui.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace Aserai
{
	AImGui::AImGui()
		: m_Initialized(false)
	{
	}

	bool AImGui::Init(const std::unique_ptr<Window>& window)
	{
		ImGui::CreateContext();
		ImGui::GetIO().DisplaySize = { (float)window->GetWidth(), (float)window->GetHeight()};
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//ImGui::GetIO().Fonts->AddFontFromFileTTF("../Assets/Fonts/arial.ttf", 16);

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
		return m_Initialized = true;
	}

	void AImGui::Destroy()
	{
		if (m_Initialized)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	}

	void AImGui::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void AImGui::EngFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			auto* bakcc = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(bakcc);
		}
	}
}
