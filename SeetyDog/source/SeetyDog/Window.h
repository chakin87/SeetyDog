#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "sdpch.h"
#include "SeetyDog/Core.h"
#include "SeetyDog/Events/Event.h"

namespace SeetyDog {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "SeetyDog - Bytes that Build!",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class SEETYDOG_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		///virtual void* GetActiveWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}



#endif // _WINDOW_H_