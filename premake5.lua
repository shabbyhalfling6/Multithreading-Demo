--
-- Premake 5.x build configuration script
-- Use this script to configure the project with Premake5.
--

--
-- Disable deprecation warnings for myself, so that older development
-- versions will still be able to regenerate the scripts.
--

premake.api.deprecations "off"

--
-- Define the project. Put the release configuration first so it will be the
-- default when folks build using the makefile. That way they don't have to
-- worry about the /scripts argument and all that.
--

solution "raytracer"
	configurations { "Release", "Debug" }
	platforms {"x32","x64"}

	project "raytracer"
		language    "C++"
		kind        "ConsoleApp"
		flags       { "ExtraWarnings", "NoMinimalRebuild", "WinMain" }
		includedirs { "raytracer", "raytracer/lua" }
		targetdir "$(SolutionDir)bin"
		objdir "$(SolutionDir)temp/"
		buildoptions  {"/bigobj", "/MP4"}
		location "raytracer"
		
		files
		{
			"**.cpp",
			"**.h",
			"kf/src/**.cpp",
			"kf/**.h",
			"lua/**.h"
		}
		configuration {"Debug", "x32"}
			targetname  "raytracer32_d"
			targetdir   "$(SolutionDir)bin/"
			defines     {"_DEBUG"}
			flags       { "Symbols" }
			links {"winmm.lib", "lua51_x86.lib"}
			debugdir "$(TargetDir)"

		configuration {"Release", "x32"}
			targetname  "raytracer32"
			targetdir   "$(SolutionDir)bin/"
			defines     {"NDEBUG"}
			flags       { "OptimizeSpeed" }
			links {"winmm.lib", "lua51_x86.lib"}
			debugdir "bin"

		configuration {"Debug", "x64"}
			targetname  "raytracer64_d"
			targetdir   "$(SolutionDir)bin/"
			defines     {"_DEBUG"}
			flags       { "Symbols" }
			links {"winmm.lib", "lua51_x64.lib"}
			debugdir "bin"

		configuration {"Release", "x64"}
			targetname  "raytracer64"
			targetdir   "$(SolutionDir)bin/"
			defines     {"NDEBUG"}
			flags       { "OptimizeSpeed" }
			links {"winmm.lib", "lua51_x64.lib"}
			debugdir "bin"

		configuration "vs*"
			defines     { "_CRT_SECURE_NO_WARNINGS" }
			
