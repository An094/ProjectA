workspace "ProjectA"
	architecture "x64"
	startproject "ProjectA"
	cppdialect "C++17"
	
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
		
		
project "ANet"
	location "ANet"
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

project "ProjectAClient"
	location "ProjectAClient"
	kind "ConsoleApp"
	language "C++"
		
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"ANet/libs/asio/include",
		"ANet/src",
		"AF/src",
		"AF/include",
		"AF/include/GLFW/include",
		"AF/include/GLAD/include",
		"AF/include/freetype",
		"AF/include/Soloud",
		"AF/include/spdlog/include",
		"ProjectAClient/src",
		"ProjectAServer/src"
	}

	links
	{
		"AF"
	}	
	
	postbuildcommands { "xcopy /i /y D:\\Objective\\bin\\%{cfg.buildcfg}-x64\\%{prj.name} D:\\Objective\\release" }
	
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
	
project "ProjectAServer"
	location "ProjectAServer"
	kind "ConsoleApp"
	language "C++"
		
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"ANet/libs/asio/include",
		"ANet/src",
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

	
	postbuildcommands { "xcopy /i /y D:\\Objective\\bin\\%{cfg.buildcfg}-x64\\%{prj.name} D:\\Objective\\release" }
	
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