include "Dependencies.lua"

workspace "Aserai"
	architecture "x64"
	startproject "AseraiSandbox"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
	include "Dependencies/spdlog"
group ""

include "AseraiEngine"
include "AseraiSandbox"
