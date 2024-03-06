project "AseraiSandbox"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/Build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/Build/Intermediates/" .. outputdir .. "/%{prj.name}")

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
}

links
{
	"AseraiEngine"
}

filter "system:windows"
	systemversion "latest"

filter "configurations:Debug"
	defines "ASERAI_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "ASERAI_RELEASE"
	runtime "Release"
	optimize "On"
