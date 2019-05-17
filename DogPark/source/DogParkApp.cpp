#include <SeetyDog.h>

#include "ImGui/imgui.h"


class ExampleLayer : public SeetyDog::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_TAB)) {
			SD_INFO("Tab key was press by you (Polled Event - OnUpdate())");
		}
	
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(SeetyDog::Event& event) override
	{
		
		if (event.GetEventType() == SeetyDog::EventType::KeyPressed) {
			SeetyDog::KeyPressedEvent& e = (SeetyDog::KeyPressedEvent&)event;
			SD_TRACE("{0}", (char)e.GetKeyCode());
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_TAB)) {
				SD_INFO("Tab key was press by you (Natural Event - OnEvent())");
			}
		}
	}

};



class DogPark : public SeetyDog::Application
{
public:
	DogPark() { 
		PushLayer(new ExampleLayer()); 
		//PushOverlay(new SeetyDog::ImGuiLayer());
	}
	~DogPark() {}

};

SeetyDog::Application* SeetyDog::CreateApplication() {
	return new DogPark();
}