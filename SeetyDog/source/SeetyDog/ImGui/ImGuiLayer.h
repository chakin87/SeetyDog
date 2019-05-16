#ifndef _IMGUILAYER_H_
#define _IMGUILAYER_H_



#include "SeetyDog/Layer.h"


#include "SeetyDog/Events/ApplicationEvent.h"
#include "SeetyDog/Events/KeyEvent.h"
#include "SeetyDog/Events/MouseEvent.h"

namespace SeetyDog {

	class SEETYDOG_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};

}

#endif // !_IMGUILAYER_H_
