include "Dependencies.lua"

workspace "Aserai2D"
	architecture "x64"
	startproject "A2DEditor"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
	include "Dependencies/spdlog"
	include "Dependencies/glfw"
	include "Dependencies/glad"
	include "Dependencies/stb"
	include "Dependencies/imgui"
group ""

include "A2DEngine"
include "A2DEditor"
include "A2DSandbox"
