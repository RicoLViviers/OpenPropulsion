cmake_minimum_required(VERSION 3.20)

project(OpenPropulsion)

# Add the imgui subdirectory
add_subdirectory(imgui)

# Define your main executable
add_executable(OpenPropulsion
    src/main.cpp
)

# Link against ImGui
target_link_libraries(OpenPropulsion PRIVATE imgui)