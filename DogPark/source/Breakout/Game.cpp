#include "Game.h"
//#include "SeetyDog/Input.h"
#include "SeetyDog/MouseButtonCodes.h"
#include "SeetyDog/KeyCodes.h"
#include "SeetyDog/Events/ApplicationEvent.h"
#include "SeetyDog/Events/KeyEvent.h"
#include "SeetyDog/Events/MouseEvent.h"
#include "Platform/Windows/WindowsInput.h"
//./#include "Platform/Windows/WindowsWindow.h"

#include "SeetyDog/Application.h"
#include "glm/glm/glm.hpp"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <GLFW/include/GLFW/glfw3.h>

// Game-related State data
SpriteRenderer  *Renderer;

Game::Game(unsigned int width, unsigned int height)
	:m_State(GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height)
{
}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader((std::string)"DogPark/source/Breakout/Resources/Shaders/shader.basic", (std::string)"sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->m_Width), static_cast<GLfloat>(this->m_Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("C:/CPP/SeetyDog/DogPark/source/Breakout/Resources/Textures/awesomefaceo.png", GL_TRUE, "face");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Game::EventInput(SeetyDog::Event& event)
{
	if (event.GetEventType() == SeetyDog::EventType::KeyPressed) {
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_ESCAPE)) {
			SD_INFO("Escape key hit");
			auto* window = static_cast<GLFWwindow*>(SeetyDog::Application::Get().GetWindow().GetNativeWindow());
			///SeetyDog::EventDispatcher d(event);
			//d.Dispatch(SeetyDog::WindowCloseEvent());
			//glfwSetWindowShouldClose(window, true);
			SeetyDog::WindowCloseEvent();
		}
	}
}

void Game::ProcesInput(float dt)
{
	if (SeetyDog::Input::IsKeyPressed(SD_KEY_TAB)) {
    	SD_INFO("Tab key was press by you (Polled Event - OnUpdate())");
    }
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

