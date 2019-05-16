#ifndef _ENTRYPOINT_H_
#define _ENTRYPOINT_H_

	#ifdef SD_PLATFORM_WINDOWS
		
extern SeetyDog::Application* SeetyDog::CreateApplication();

int main(int argc, char** argv) {

	SeetyDog::Logger::Init();
	SD_SEETY_WARN("SeetyDog Logging Enabled!");
	SDOUT(SD_NEW_LOG_STRING);

	auto application = SeetyDog::CreateApplication();
	application->Run();
	delete application;
}
	
	#endif // SD_PLATFORM_WINDOWS
#endif // ENTRYPOINT_H