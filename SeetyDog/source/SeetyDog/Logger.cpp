#include "sdpch.h"
#include "Logger.h"

namespace SeetyDog {

	std::shared_ptr<spdlog::logger> Logger::s_SeetyDogLog;
	std::shared_ptr<spdlog::logger> Logger::s_ClientDogLog;

	std::shared_ptr<spdlog::logger> Logger::s_SeetyDogFileLog;

	void Logger::Init()
	{
		s_SeetyDogFileLog = spdlog::basic_logger_mt("SeetyDogFileLog", "../Logs/SDLOG.txt");
		s_SeetyDogFileLog->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T][File:%s][Line:%#] %n: %v%$");
		s_SeetyDogLog = spdlog::stdout_color_mt("SEETYDOG");
		s_SeetyDogLog->set_level(spdlog::level::trace);
		s_ClientDogLog = spdlog::stdout_color_mt("CLIENTDOG");
		s_ClientDogLog->set_level(spdlog::level::trace); 
	}

}