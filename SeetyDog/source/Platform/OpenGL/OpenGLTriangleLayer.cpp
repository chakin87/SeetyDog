#include "sdpch.h"
#include "OpenGLTriangleLayer.h"
#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <gl/GL.h>
namespace SeetyDog {

	
	OpenGLTriangleLayer::OpenGLTriangleLayer()
		: Layer("OpenGLTriangleLayer")
	{
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

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	
	void OpenGLTriangleLayer::OnDetach()
	{
	
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
	
	}
	
}
