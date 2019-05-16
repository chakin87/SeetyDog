#ifndef _LAYER_H_
#define _LAYER_H_



#include "SeetyDog/Core.h"
#include "SeetyDog/Events/Event.h"

namespace SeetyDog {

	class SEETYDOG_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
#endif // !_LAYER_H_
