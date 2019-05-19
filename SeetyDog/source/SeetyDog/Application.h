#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Core.h"

#include "Window.h"

#include "SeetyDog/LayerStack.h"
#include "SeetyDog/Events/Event.h"
#include "SeetyDog/Events/ApplicationEvent.h"

#include "SeetyDog/ImGui/ImGuiLayer.h"

namespace SeetyDog {


class SEETYDOG_API Application
{
public:
	Application();
	virtual ~Application();
	void Run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	inline Window& GetWindow() { return *m_Window; }

	inline static Application& Get() { return *s_Instance; }

private:
	bool OnWindowClose(WindowCloseEvent& e);

	std::unique_ptr<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	bool m_Running = true;

	LayerStack m_LayerStack;

private:
	static Application* s_Instance;
};

Application* CreateApplication();


} // End namespace SeetyDog

#endif // !APPLICATION_H
