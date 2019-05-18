#include "sdpch.h"
#include "Application.h"

#include "Logger.h"

#include <glad/glad.h>

#include "Input.h"

namespace SeetyDog {


	///Application::Application()
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SD_SEETY_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//copied2gllayer./lGenVertexArrays(1, &m_VertexArray);
		//copied2gllayer./glBindVertexArray(m_VertexArray);
		//copied2gllayer./
		//copied2gllayer./glGenBuffers(1, &m_VertexBuffer);
		//copied2gllayer./glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		//copied2gllayer./
		//copied2gllayer./float vertices[3 * 3] = {
		//copied2gllayer./	-0.5f, -0.5f, 0.0f,
		//copied2gllayer./	 0.5f, -0.5f, 0.0f,
		//copied2gllayer./	 0.0f,  0.5f, 0.0f
		//copied2gllayer./};
		//copied2gllayer./
		//copied2gllayer./glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//copied2gllayer./
		//copied2gllayer./glEnableVertexAttribArray(0);
		//copied2gllayer./glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		//copied2gllayer./
		//copied2gllayer./glGenBuffers(1, &m_IndexBuffer);
		//copied2gllayer./glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		//copied2gllayer./
		//copied2gllayer./unsigned int indices[3] = { 0, 1, 2 };
		//copied2gllayer./glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{

		while (m_Running) {
			//copied2gllayer./glClearColor(0.1f, 0.8f, 0.7f, 1);
			//copied2gllayer./glClear(GL_COLOR_BUFFER_BIT);
			//copied2gllayer./
			//copied2gllayer./glBindVertexArray(m_VertexArray);
			//copied2gllayer./glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}