-- premake5.lua
include "dependencies.lua"

workspace "Jianjia"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RayTracing"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
group ""
include "Framework"
include "RayTracing"