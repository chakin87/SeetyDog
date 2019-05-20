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
		m_Vertices[0] = -0.1f;
		m_Vertices[1] = -0.1f;
		m_Vertices[2] =  0.0f;
		m_Vertices[3] =  0.1f;
		m_Vertices[4] = -0.1f;
		m_Vertices[5] =  0.0f;
		m_Vertices[6] =  0.0f;
		m_Vertices[7] =  0.1f;
		m_Vertices[8] =  0.0f;
	}
	
	
	OpenGLTriangleLayer::~OpenGLTriangleLayer()
	{
	}
	
	void OpenGLTriangleLayer::OnAttach()
	{
		InitOnAttach();
		//./DrawCircleInit();
	}
	
	void OpenGLTriangleLayer::OnDetach()
	{
		delete m_Vertices;
	}
	
	void OpenGLTriangleLayer::OnUpdate()
	{
		TriOneUpdate();
		//./glClearColor(0.1f, 0.8f, 0.7f, 1);
		//./glClear(GL_COLOR_BUFFER_BIT);
		//./DrawCircle(1280 / 2, 720 / 2, 0.0f, 120, 10);
		//./
	}
	
	void OpenGLTriangleLayer::OnImGuiRender()
	{
	
	}
	
	void OpenGLTriangleLayer::OnEvent(Event& event)
	{
		if (event.GetEventType() == SeetyDog::EventType::KeyPressed) {
			SeetyDog::KeyPressedEvent& e = (SeetyDog::KeyPressedEvent&)event;

			if (SeetyDog::Input::IsKeyPressed(SD_KEY_T)) {
				DrawCircle(1280 / 2, 720 / 2, 0.0f, 120, 10);
			}

		}
	}

	void OpenGLTriangleLayer::InitOnAttach()
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

	void OpenGLTriangleLayer::TriOneUpdate()
	{
		glClearColor(0.1f, 0.8f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


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

	void OpenGLTriangleLayer::DrawCircleInit()
	{

		glViewport(0.0f, 0.0f, 1280 , 720); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
		glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
		glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
		glOrtho(0, 1280, 0, 720, 0, 1); // essentially set coordinate system
		glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
		glLoadIdentity(); // same as above comment
	}

	void OpenGLTriangleLayer::DrawCircle(float x, float y, float z, float radius, int numberOfSides)
	{
		GLint numberOfVertices = numberOfSides + 1;

		GLfloat doublePi = 2.0f * 3.145926;

		// Work-around for char CircleVerticesX[numberOfVertices]; 
		// This is a stack allocated array with a non-predetermined size!
		GLfloat* CircleVerticesX = (GLfloat*)alloca(numberOfVertices * sizeof(GLfloat));
		GLfloat* CircleVerticesY = (GLfloat*)alloca(numberOfVertices * sizeof(GLfloat));
		GLfloat* CircleVerticesZ = (GLfloat*)alloca(numberOfVertices * sizeof(GLfloat));
		
		CircleVerticesX[0] = x;
		CircleVerticesY[0] = y;
		CircleVerticesZ[0] = z;

		for (int i = 1; i < numberOfVertices; ++i) {

			CircleVerticesX[i] = x + (radius * cos(i * doublePi / numberOfSides));
			CircleVerticesY[i] = y + (radius * cos(i * doublePi / numberOfSides));
			CircleVerticesZ[i] = z;
		}

		GLfloat* allCircleVertices = (GLfloat*)alloca(numberOfVertices * 3 * sizeof(GLfloat));
		
		for(int i = 0; i < numberOfVertices; ++i) {
			allCircleVertices[(i * 3)] = CircleVerticesX[i];
			allCircleVertices[(i * 3) + 1] = CircleVerticesY[i];
			allCircleVertices[(i * 3) + 2] = CircleVerticesZ[i];
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
		glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
		glDisableClientState(GL_VERTEX_ARRAY);



	}
	
}
