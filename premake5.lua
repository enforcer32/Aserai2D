include "Dependencies.lua"

workspace "Aserai"
	architecture "x64"
	startproject "AseraiEditor"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
	include "Dependencies/spdlog"
	include "Dependencies/glfw"
	include "Dependencies/glad"
	include "Dependencies/stb"
	include "Dependencies/imgui"
group ""

include "AseraiEngine"
include "AseraiEditor"
include "AseraiSandbox"
