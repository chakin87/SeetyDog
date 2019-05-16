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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}

#endif // !_IMGUILAYER_H_
