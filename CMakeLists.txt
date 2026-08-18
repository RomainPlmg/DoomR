cmake_minimum_required(VERSION 3.30.0)

project(DoomEngine
        VERSION 0.1.0
        DESCRIPTION "A Doom Engine clone"
        LANGUAGES C CXX)

include(FetchContent)

# ============================================================================
# C++ Configuration
# ============================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_command.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Define executable
# ============================================================================
add_executable(DoomEngine
    src/Main.cpp
    src/core/Log.cpp
    src/platform/Window.cpp
    src/render/Framebuffer.cpp
    src/wad/WadFile.cpp
    src/wad/WadDirectory.cpp
)

target_include_directories(DoomEngine PRIVATE ${PROJECT_SOURCE_DIR}/src/)

# ============================================================================
# Dependencies
# ============================================================================
# SDL3
FetchContent_Declare(
        sdl
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.14
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        SYSTEM
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(sdl)

# SpdLog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        SYSTEM
)
FetchContent_MakeAvailable(spdlog)

target_link_libraries(DoomEngine PRIVATE SDL3::SDL3 spdlog)