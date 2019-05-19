#include "sdpch.h"
#include "OpenGLTriangleLayer.h"
#include <glad/glad.h>
#include "SeetyDog/Events/ApplicationEvent.h"
#include "SeetyDog/Events/MouseEvent.h"
#include "SeetyDog/Events/KeyEvent.h"
#include "SeetyDog/KeyCodes.h"
#include "SeetyDog/MouseButtonCodes.h"
#include "SeetyDog/Input.h"
namespace SeetyDog {

	
	OpenGLTriangleLayer::OpenGLTriangleLayer()
		: Layer("OpenGLTriangleLayer"), m_Speed(.009f)
	{
		//m_Vertices = float[3 * 3];
		m_Vertices[0] = -0.5f;
		m_Vertices[1] = -0.5f;
		m_Vertices[2] =  0.0f;
		m_Vertices[3] =  0.5f;
		m_Vertices[4] = -0.5f;
		m_Vertices[5] =  0.0f;
		m_Vertices[6] =  0.0f;
		m_Vertices[7] =  0.5f;
		m_Vertices[8] =  0.0f;
	}
	
	
	OpenGLTriangleLayer::~OpenGLTriangleLayer()
	{
	}
	
	void OpenGLTriangleLayer::OnAttach() 
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	
	void OpenGLTriangleLayer::OnDetach()
	{
		delete m_Vertices;
	}
	
	void OpenGLTriangleLayer::OnUpdate()
	{
		glClearColor(0.1f, 0.8f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}
	
	void OpenGLTriangleLayer::OnImGuiRender()
	{
	
	}
	
	void OpenGLTriangleLayer::OnEvent(Event& event)
	{
		if (event.GetEventType() == SeetyDog::EventType::KeyPressed) {
			SeetyDog::KeyPressedEvent& e = (SeetyDog::KeyPressedEvent&)event;
			//SD_TRACE("{0}", (char)e.GetKeyCode());
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_W)) {
				SD_INFO("'W' key was press by you (Natural Event - OnEvent())");
				m_Vertices[1] += m_Speed;
				m_Vertices[4] += m_Speed;
				m_Vertices[7] += m_Speed;
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_S)) {
				SD_INFO("'W' key was press by you (Natural Event - OnEvent())");
				m_Vertices[1] -= m_Speed;
				m_Vertices[4] -= m_Speed;
				m_Vertices[7] -= m_Speed;
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_A)) {
				SD_INFO("'W' key was press by you (Natural Event - OnEvent())");
				m_Vertices[0] -= m_Speed;
				m_Vertices[3] -= m_Speed;
				m_Vertices[6] -= m_Speed;
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_D)) {
				SD_INFO("'W' key was press by you (Natural Event - OnEvent())");
				m_Vertices[0] += m_Speed;
				m_Vertices[3] += m_Speed;
				m_Vertices[6] += m_Speed;
			}
				glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

				glGenBuffers(1, &m_IndexBuffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

				unsigned int indices[3] = { 0, 1, 2 };
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			
		}
	}
	
}
