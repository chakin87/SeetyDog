#include <SeetyDog.h>

#include "ImGui/imgui.h"
#include "Platform/OpenGL/OpenGLTriangleLayer.h"


class ExampleLayer : public SeetyDog::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//./if (SeetyDog::Input::IsKeyPressed(SD_KEY_TAB)) {
		//./	SD_INFO("Tab key was press by you (Polled Event - OnUpdate())");
		//./}
	
	}

	virtual void OnAttach() override {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		//./ImGuiIO& io = ImGui::GetIO();
		//./io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//./io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
		ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
		ImGui::SameLine(0.0f, 0.0f);
		if (ImGui::SmallButton("click here"))
			ImGui::Text("Lol you clicked the button!");

		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(SeetyDog::Event& event) override
	{
		
		//./if (event.GetEventType() == SeetyDog::EventType::KeyPressed) {
		//./	SeetyDog::KeyPressedEvent& e = (SeetyDog::KeyPressedEvent&)event;
		//./	SD_TRACE("{0}", (char)e.GetKeyCode());
		//./	if (SeetyDog::Input::IsKeyPressed(SD_KEY_TAB)) {
		//./		SD_INFO("Tab key was press by you (Natural Event - OnEvent())");
		//./	}
		//./}
	}

};



class DogPark : public SeetyDog::Application
{
public:
	DogPark() { 
		PushLayer(new ExampleLayer()); 
		PushLayer(new SeetyDog::OpenGLTriangleLayer());
	}
	~DogPark() {}

};

SeetyDog::Application* SeetyDog::CreateApplication() {
	return new DogPark();
}