#pragma once
#include "SeetyDog/Layer.h"


namespace SeetyDog {

	class SEETYDOG_API OpenGLTriangleLayer : public Layer
	{
	public:
		OpenGLTriangleLayer();
		~OpenGLTriangleLayer();
	public://Methods
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
		
	
	public://Members
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private://Methods
		void InitOnAttach();
		void TriOneUpdate();
	
		void DrawCircleInit();
		void DrawCircle(float x, float y, float z, float radius, int numberOfSides);


	private://Members
		float m_Vertices[9];
		float m_Speed;
	};
	
}
