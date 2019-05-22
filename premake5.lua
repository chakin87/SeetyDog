workspace "SeetyDog"
	architecture "x64"
	startproject "DogPark"

	configurations{
		"Debug",
		"Release",
		"Ship"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "SeetyDog/externlibs/GLFW/include"
IncludeDir["GLAD"] = "SeetyDog/externlibs/GLAD/include"
IncludeDir["ImGui"] = "SeetyDog/externlibs/ImGui"
IncludeDir["glm"] = "SeetyDog/externlibs/glm"
IncludeDir["irrKlang"] = "SeetyDog/externlibs/irrKlang"
IncludeDir["stb_image"] = "SeetyDog/externlibs/stb_image"
IncludeDir["FreeType"] = "SeetyDog/externlibs/FreeType/include"

include "SeetyDog/externlibs/GLFW"
include "SeetyDog/externlibs/GLAD"
include "SeetyDog/externlibs/ImGui"


project "SeetyDog"
	location "SeetyDog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "sdpch.h"
	pchsource "SeetyDog/source/sdpch.cpp"

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/externlibs/glm/glm/**.hpp",
		"%{prj.name}/externlibs/glm/glm/**.inl",
		"%{prj.name}/externlibs/irrKlang/**.h",
		"%{prj.name}/externlibs/stb_image/**.h",
		"%{prj.name}/externlibs/stb_image/**.cpp",
		"%{prj.name}/externlibs/FreeType/**.h",
		"%{prj.name}/externlibs/FreeType/**.cpp"
	}

		defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}


	includedirs
	{
		"%{prj.name}/source",
		"%{prj.name}/externlibs/spdlog/include",
		"%{prj.name}/externlibs/irrKlang/include",
		"%{prj.name}/externlibs/FreeType/include",
		"%{prj.name}/externlibs/FreeType/include/freetype",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

		links 
	{ 
		"GLFW",
		"GLAD",
		"ImGui",
		"C:/CPP/SeetyDog/SeetyDog/externlibs/irrKlang/lib/Winx64-visualStudio/irrKlang.lib",
		"C:/CPP/SeetyDog/SeetyDog/externlibs/FreeType/win64/freetype.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SD_PLATFORM_WINDOWS",
			"SD_BUILD_DLL",
			GLFW_INCLUDE_NONE
		}


	filter "configurations:Debug"
		defines "SD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Ship"
		defines "SD_SHIP"
		runtime "Release"
		optimize "on"

project "DogPark"
	location "DogPark"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp"
	}

	includedirs
	{
		"SeetyDog/externlibs/spdlog/include",
		"SeetyDog/source",
		"%{IncludeDir.glm}",
		"SeetyDog/externlibs",
		"SeetyDog/externlibs/FreeType/include/freetype",
		"SeetyDog/externlibs/FreeType/include"
	}

	links
	{
		"SeetyDog"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Ship"
		defines "SD_SHIP"
		runtime "Release"
		optimize "on"
