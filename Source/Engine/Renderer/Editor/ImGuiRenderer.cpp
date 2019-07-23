#include "ImGuiRenderer.h"


#include "GLFW/glfw3.h"
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"




void ImGuiRenderer::Init()
{
	m_Window = glfwGetCurrentContext();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 130");



	Subsystem::Init();
}

void ImGuiRenderer::Tick(float /*DeltaTime*/)
{
	if (IsInitialized()) 
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool bShow = true;

		ImGui::ShowDemoWindow(&bShow);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
}

void ImGuiRenderer::Deinit()
{

	Subsystem::Deinit();
}
