workspace "Elements"
	architecture "x86_64"
	startproject "Playground"
	
	configurations {
		"Debug",
		"Release"
	}
	
IncludeDir = {}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Elements"
	location "Elements"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")
	
	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}
	
	includedirs {
		"%{prj.name}/src"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "ELMT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ELMT_RELEASE"
		runtime "Release"
		optimize "on"

project "Playground"
	location "Playground"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")
	
	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}
	
	includedirs {
		"Elements/src"
	}
	
	links {
		"Elements"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "ELMT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ELMT_RELEASE"
		runtime "Release"
		optimize "on"
