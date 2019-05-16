#ifndef _LOGGER_H_
#define _LOGGER_H_


#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
    
namespace SeetyDog {


	class SEETYDOG_API Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetSeetyDogLog() { return s_SeetyDogLog; }
		inline static std::shared_ptr<spdlog::logger>& GetClientDogLog() { return s_ClientDogLog; }
		inline static std::shared_ptr<spdlog::logger>& GetSeetyDogFileLog() { return s_SeetyDogFileLog; }
	private:
		static std::shared_ptr<spdlog::logger> s_SeetyDogLog;
		static std::shared_ptr<spdlog::logger> s_ClientDogLog;


		// Create basic file logger (not rotated)
		static std::shared_ptr<spdlog::logger> s_SeetyDogFileLog;
		//my_logger->info("Some log message");
	};

}

// SeetyDog logger macros
#define SD_SEETY_TRACE(...)    ::SeetyDog::Logger::GetSeetyDogLog()->trace(__VA_ARGS__)
#define SD_SEETY_INFO(...)     ::SeetyDog::Logger::GetSeetyDogLog()->info(__VA_ARGS__)
#define SD_SEETY_WARN(...)     ::SeetyDog::Logger::GetSeetyDogLog()->warn(__VA_ARGS__)
#define SD_SEETY_ERROR(...)    ::SeetyDog::Logger::GetSeetyDogLog()->error(__VA_ARGS__)
#define SD_SEETY_FATAL(...)    ::SeetyDog::Logger::GetSeetyDogLog()->fatal(__VA_ARGS__)

// SeetyDog+File logger macros
#define SD_SEETYF_TRACE(...) {   ::SeetyDog::Logger::GetSeetyDogFileLog()->trace(__VA_ARGS__);  SD_SEETY_TRACE(__VA_ARGS__);}
#define SD_SEETYF_INFO(...)  {   ::SeetyDog::Logger::GetSeetyDogFileLog()->info(__VA_ARGS__) ;  SD_SEETY_INFO(__VA_ARGS__);}
#define SD_SEETYF_WARN(...)  {   ::SeetyDog::Logger::GetSeetyDogFileLog()->warn(__VA_ARGS__) ;  SD_SEETY_WARN(__VA_ARGS__);}
#define SD_SEETYF_ERROR(...) {   ::SeetyDog::Logger::GetSeetyDogFileLog()->error(__VA_ARGS__);  SD_SEETY_ERROR(__VA_ARGS__);}
#define SD_SEETYF_FATAL(...) {   ::SeetyDog::Logger::GetSeetyDogFileLog()->fatal(__VA_ARGS__);  SD_SEETY_FATAL(__VA_ARGS__);}

// SeetyDog+File logger shortcut macros
#define SDOUT(...) SD_SEETYF_TRACE(__VA_ARGS__)

// ClientDog logger macros
#define SD_TRACE(...)	      ::SeetyDog::Logger::GetClientDogLog()->trace(__VA_ARGS__)
#define SD_INFO(...)	      ::SeetyDog::Logger::GetClientDogLog()->info(__VA_ARGS__)
#define SD_WARN(...)	      ::SeetyDog::Logger::GetClientDogLog()->warn(__VA_ARGS__)
#define SD_ERROR(...)	      ::SeetyDog::Logger::GetClientDogLog()->error(__VA_ARGS__)
#define SD_FATAL(...)	      ::SeetyDog::Logger::GetClientDogLog()->fatal(__VA_ARGS__) 

#define SD_NEW_LOG_STRING "***************************************************************\n"\
"                                          |                     New Compile Log                         |\n"\
"                                          ***************************************************************\n"

#endif // !_LOGGER_H_
