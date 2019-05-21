#include "BreakoutLayer.h"
#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>


BreakoutLayer::BreakoutLayer()
	: Layer("Breakout"), m_DeltaTime(0.0f), m_LastFrame(0.0f)
{
	breakout = Game(m_Width, m_Height);
}


BreakoutLayer::~BreakoutLayer()
{
}

void BreakoutLayer::OnAttach()
{
	////...////

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	////....////



	glViewport(0, 0, m_Width, m_Height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	breakout.Init();
	breakout.m_State = GAME_ACTIVE;
}

void BreakoutLayer::OnDetach()
{
	ResourceManager::Clear();
}

void BreakoutLayer::OnUpdate()
{
	float currentFrame = (float)glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
	breakout.ProcesInput(m_DeltaTime);
	breakout.Update(m_DeltaTime);

	glClearColor(0.1f, 0.2f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	breakout.Render();
}

void BreakoutLayer::OnImGuiRender()
{
}

void BreakoutLayer::OnEvent(SeetyDog::Event & event)
{
	breakout.EventInput(event);
}
