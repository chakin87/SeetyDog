#include "sdpch.h"
#include "WindowsInput.h"
#include "SeetyDog/Application.h"

#include <GLFW/glfw3.h>


namespace SeetyDog {

	Input* Input::s_Instance = new WindowsInput();

	WindowsInput::WindowsInput()
	{
	}


	WindowsInput::~WindowsInput()
	{
	}

	bool SeetyDog::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;

	}


	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		// c++ 17 feature for returning and nameing your pair
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		// c++ 17 feature for returning and nameing your pair
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}
 
