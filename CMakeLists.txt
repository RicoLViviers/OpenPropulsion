cmake_minimum_required(VERSION 3.15)

project(OpenPropulsion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================
# GLFW
# ============================================================

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)

# Disable unnecessary GLFW components
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# ============================================================
# OpenGL
# ============================================================

find_package(OpenGL REQUIRED)

# ============================================================
# Source files
# ============================================================

set(SOURCES
    src/main.cpp
    src/app/Application.cpp
    src/gui/GUI.cpp
    src/simulation/Simulation.cpp
    src/performance/Performance.cpp

    # Dear ImGui
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_demo.cpp

    # ImGui backends
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_BINARY_DIR})

# ============================================================
# Executable
# ============================================================

add_executable(${PROJECT_NAME} ${SOURCES})

# ============================================================
# Include directories
# ============================================================

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    external/imgui
    external/imgui/backends
)

# ============================================================
# Libraries
# ============================================================

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
)