#include "CatalystRenderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void WindowResizeCallback(GLFWwindow* /*window*/, int width, int height) 
{
	glViewport(0, 0, width, height);
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
		printf("Failed to create GLFW Window");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return;
	}

	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glfwSetFramebufferSizeCallback(m_Window, WindowResizeCallback);

	Subsystem::Init();
}

void CatalystRenderer::Tick(float)
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT);
}

void CatalystRenderer::Deinit()
{

	glfwTerminate();

	Subsystem::Deinit();
}
