workspace "Elements"
	architecture "x86_64"
	startproject "Playground"
	
	configurations {
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["GLFW"] = "Elements/vendor/GLFW/include"
IncludeDir["Vulkan"] = path.getrelative(".", "C:/VulkanSdk/1.2.141.2")
IncludeDir["GLM"] = "Elements/vendor/GLM/"
IncludeDir["DearImGui"] = "Elements/vendor/Dear_ImGui"

group "Dependencies"
	include "Elements/vendor/GLFW"
	include "Elements/vendor/Dear_ImGui"
group ""

project "Elements"
	location "Elements"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "elmtpch.h"
	pchsource "Elements/src/elmtpch.cpp"
	
	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	libdirs {
		"%{IncludeDir.Vulkan}/Lib"
	}
	
	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Vulkan}/Include",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.DearImGui}"
	}
	
	forceincludes { "elmtpch.h" }
		
	links {
		"GLFW",
		"vulkan-1.lib",
		"Dear_ImGui"
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
		"Elements/src",
		"Elements/vendor/spdlog/include",
		"Elements/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Vulkan}/Include",
		"%{IncludeDir.GLM}"
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
