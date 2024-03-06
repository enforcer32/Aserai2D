project "AseraiEngine"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/Build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/Build/Intermediates/" .. outputdir .. "/%{prj.name}")

pchheader "AseraiEnginePCH.h"
pchsource "AseraiEnginePCH.cpp"

files
{
	"**.h",
	"**.cpp",
}

excludes
{
}

defines
{
	"ASERAI_ENGINE",
}

includedirs
{
	"%{wks.location}/AseraiEngine",
	"%{IncludeDir.spdlog}",
}

links
{
	"spdlog",
}

filter "system:windows"
	systemversion "latest"

	defines
	{
		"ASERAI_PLATFORM_WINDOWS",
	}

	files
	{
	}

filter "configurations:Debug"
	defines "ASERAI_ENGINE_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "ASERAI_ENGINE_RELEASE"
	runtime "Release"
	optimize "On"
