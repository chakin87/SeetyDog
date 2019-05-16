workspace "SeetyDog"
	architecture "x64"

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

include "SeetyDog/externlibs/GLFW"
include "SeetyDog/externlibs/GLAD"
include "SeetyDog/externlibs/ImGui"


project "SeetyDog"
	location "SeetyDog"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")


	pchheader "sdpch.h"
	pchsource "SeetyDog/source/sdpch.cpp"

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/externlibs/glm/glm/**.hpp",
		"%{prj.name}/externlibs/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/source",
		"%{prj.name}/externlibs/spdlog/include",
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
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"SD_PLATFORM_WINDOWS",
			"SD_BUILD_DLL",
			GLFW_INCLUDE_NONE
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/DogPark")
		}

	filter "configurations:Debug"
		defines "SD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SD_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Ship"
		defines "SD_SHIP"
		buildoptions "/MD"
		optimize "On"

project "DogPark"
	location "DogPark"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp"
	}

	includedirs
	{
		"SeetyDog/externlibs/spdlog/include",
		"SeetyDog/source",
		"%{IncludeDir.glm}"
	}

	links
	{
		"SeetyDog"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"SD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SD_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Ship"
		defines "SD_SHIP"
		buildoptions "/MD"
		optimize "On" 