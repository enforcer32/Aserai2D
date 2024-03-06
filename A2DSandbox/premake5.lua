project "A2DSandbox"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/Build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/Build/Intermediates/" .. outputdir .. "/%{prj.name}")

pchheader "A2DSandboxPCH.h"
pchsource "A2DSandboxPCH.cpp"

files
{
	"**.h",
	"**.cpp",
}

includedirs
{
	"%{wks.location}",
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.imgui}",
}

links
{
	"A2DEngine"
}

filter "system:windows"
	systemversion "latest"

	defines
	{
		"ASERAI2D_PLATFORM_WINDOWS",
	}

	files
	{
	}

filter "configurations:Debug"
	defines "ASERAI2D_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "ASERAI2D_RELEASE"
	runtime "Release"
	optimize "On"
