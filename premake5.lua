workspace "pathtracer"
    architecture "x64"
    location "build"
    configurations { "Release", "Debug" }  
    startproject "pathtracer"

project "pathtracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    location "build"
    staticruntime "on"
    
    files { "src/**.cpp", "src/**.hpp", "src/**.h", "libraries/include/ImGui/**.cpp" }

    includedirs "libraries/*"
    libdirs "libraries/lib"

    links { "SDL3", "SDL3_image", "winmm" }

    filter "configurations:Release"
        optimize "Full"
        defines "RELEASE"    

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "system:windows"
        postbuildcommands {
            "{COPY} %{wks.location}/../libraries/lib/SDL3.dll %{cfg.targetdir}",
            "{COPY} %{wks.location}/../libraries/lib/SDL3_image.dll %{cfg.targetdir}"
        }