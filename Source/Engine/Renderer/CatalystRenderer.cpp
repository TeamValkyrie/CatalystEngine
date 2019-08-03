#include "CatalystRenderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Engine/CatalystEngine.h"
#include "Engine/Renderer/Editor/ImGuiRenderer.h"

#include <iostream>

void WindowResizeCallback(GLFWwindow* /*window*/, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void WindowCloseCallback(GLFWwindow* /*window*/) 
{
	printf("GLFW window: Close Callback triggered\n");
	CTEngine->RequestShutdown(0, nullptr);
}

CatalystRenderer::~CatalystRenderer()
{
	if (m_ImGuiRenderer) 
	{
		if (m_ImGuiRenderer->IsInitialized()) 
		{
			m_ImGuiRenderer->Deinit();
		}
		delete m_ImGuiRenderer;
	}
}

void CatalystRenderer::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(800, 600, "Catalyst Engine", NULL, NULL);
	if (!m_Window)
	{
		printf("Failed to create GLFW Window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return;
	}

	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	//GLFW Callbacks
	glfwSetFramebufferSizeCallback(m_Window, WindowResizeCallback);
	glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);

	m_ImGuiRenderer = new ImGuiRenderer();
	m_ImGuiRenderer->Init();

	Subsystem::Init();
}

void CatalystRenderer::Tick(float DeltaTime)
{
	if (IsInitialized()) 
	{

		m_ImGuiRenderer->Tick(DeltaTime);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void CatalystRenderer::Deinit()
{

	m_ImGuiRenderer->Deinit();

	glfwTerminate();

	Subsystem::Deinit();
}

ImGuiRenderer* CatalystRenderer::GetImguiRenderer()
{
	return m_ImGuiRenderer;
}
