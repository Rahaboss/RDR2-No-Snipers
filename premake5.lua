workspace "RDR2-No-Snipers"
	architecture "x86_64"
	configurations {
		"Debug", -- Regular debug build
		"Release" -- Build with optimization
	}

	defines {
		"WIN32_LEAN_AND_MEAN" -- Exclude rarely used stuff
	}

	disablewarnings {
		"26812" -- Prefer "enum class"
	}

	-- Locations
	startproject "RDR2-No-Snipers"
	targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "bin/%{cfg.buildcfg}/%{prj.name}"

	-- Optimizations
	vectorextensions "SSE4.2"
	floatingpoint "Fast"
	staticruntime "Off" -- Sets Run-Time Library to MultiThreadedDLL
	flags {
		"MultiProcessorCompile",
		"NoManifest" -- Disable creation of Manifest XML file
	}

	-- Build configuration specifics
	filter "configurations:Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		symbols "On"
		optimize "Speed" -- All optimizations favoring speed
		flags {
			"LinkTimeOptimization"
		}

	project "RDR2-No-Snipers"
		kind "SharedLib" -- .dll
		language "C++"
		cppdialect "C++17"
		location "src" -- Project file location

		pchheader "pch.h"
		pchsource "src/pch.cpp" -- Must be defined relative to the script
		forceincludes "pch.h"

		-- Source files
		files {
			"src/**.h",
			"src/**.cpp"
		}

		-- .lib locations
		libdirs {
			"bin/lib/%{cfg.buildcfg}"
		}
		
		-- .lib links
		links {
			"minhook"
		}

		includedirs {
			"src",
			"lib/minhook/include"
		}

	project "minhook"
		kind "StaticLib" -- .lib
		language "C"
		location "src" -- Project file location

		files {
			"lib/minhook/src/**.c",
			"lib/minhook/src/**.h",
			"lib/minhook/src/include/*"
		}

		includedirs {
			"lib/%{prj.name}/include"
		}
