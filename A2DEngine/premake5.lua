project "A2DEngine"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/Build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/Build/Intermediates/" .. outputdir .. "/%{prj.name}")

pchheader "A2DEnginePCH.h"
pchsource "A2DEnginePCH.cpp"

files
{
	"**.h",
	"**.cpp",
	"%{wks.location}/Dependencies/glm/glm/**.hpp",
	"%{wks.location}/Dependencies/glm/glm/**.inl",
	"%{wks.location}/Dependencies/fnv/fnv/**.h",
}

excludes
{
}

defines
{
	"ASERAI2D_ENGINE",
	"GLFW_INCLUDE_NONE",
}

includedirs
{
	"%{wks.location}",
	"%{wks.location}/A2DEngine",
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.glfw}",
	"%{IncludeDir.glad}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.stb}",
	"%{IncludeDir.fnv}",
	"%{IncludeDir.imgui}",
}

links
{
	"spdlog",
	"glfw",
	"glad",
	"stb",
	"imgui",
	"opengl32.lib",
}

filter "system:windows"
	systemversion "latest"

	defines
	{
		"ASERAI2D_PLATFORM_WINDOWS",
	}

	files
	{
		"A2DEngine/Platform/Win32/**.cpp"
	}

filter "configurations:Debug"
	defines "ASERAI2D_ENGINE_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "ASERAI2D_ENGINE_RELEASE"
	runtime "Release"
	optimize "On"
