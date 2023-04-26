workspace "ProjectA"
	architecture "x64"
	startproject "ProjectA"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
project "AF"
	location "AF"
	kind "StaticLib"
	language "C++"
		
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/Manager/**.h",
		"%{prj.name}/src/Manager/**.cpp",
		"%{prj.name}/src/Objects/**.h",
		"%{prj.name}/src/Objects/**.cpp",
		"%{prj.name}/src/Utils/**.h",
		"%{prj.name}/src/Utils/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/include",
		"%{prj.name}/include/GLFW/include",
		"%{prj.name}/include/GLAD/include",
		"%{prj.name}/include/freetype",
		"%{prj.name}/include/Soloud",
		"%{prj.name}/include/spdlog/include",
	}

	libdirs
	{
		"%{prj.name}/lib/freetype",
		"%{prj.name}/lib/glfw",
		"%{prj.name}/lib/Soloud"
	}

	links
	{
		"opengl32.lib",
		"freetype",
		"glfw3",
		"soloud_static"
	}
	
	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
		
	filter "architecture:x64"
		targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
		objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")
		
		
project "Net"
	location "Net"
	kind "StaticLib"
	language "C++"
		
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs
	{
		"%{prj.name}/libs/asio/include"
	}

	libdirs
	{
		"%{prj.name}/lib/freetype",
		"%{prj.name}/lib/glfw",
		"%{prj.name}/lib/Soloud"
	}

	links
	{
		"opengl32.lib",
		"freetype",
		"glfw3",
		"soloud_static"
	}
	
	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
		
	filter "architecture:x64"
		targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
		objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")
		

project "PooQuest"
	location "PooQuest"
	kind "ConsoleApp"
	language "C++"
		
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/GameStates/**.h",
		"%{prj.name}/src/GameStates/**.cpp"
	}
	
	includedirs
	{
		"AF/src",
		"AF/include",
		"AF/include/GLFW/include",
		"AF/include/GLAD/include",
		"AF/include/freetype",
		"AF/include/Soloud",
		"AF/include/spdlog/include"
	}

	links
	{
		"AF"
	}	

	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
	
	filter "architecture:x64"
		targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
		objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")

project "ProjectA"
	location "ProjectA"
	kind "ConsoleApp"
	language "C++"
		
	files
	{
		"%{prj.name}/Client/**.h",
		"%{prj.name}/Client/**.cpp",
		"%{prj.name}/Server/**.h",
		"%{prj.name}/Server/**.cpp"
	}
	
	includedirs
	{
		"AF/src",
		"AF/include",
		"AF/include/GLFW/include",
		"AF/include/GLAD/include",
		"AF/include/freetype",
		"AF/include/Soloud",
		"AF/include/spdlog/include"
	}

	links
	{
		"AF"
	}	

	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
	
	filter "architecture:x64"
		targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
		objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")