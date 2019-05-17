#include "sdpch.h"
#include "OpenGLContext.h"


namespace SeetyDog {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SD_SEETY_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SD_SEETY_ASSERT(status, "Failed to initialize Glad!");

		SD_SEETY_INFO("OpenGL Info:");
		SD_SEETY_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SD_SEETY_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SD_SEETY_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}