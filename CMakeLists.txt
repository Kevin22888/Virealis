# Set the minimum CMake version and project name
cmake_minimum_required(VERSION 3.10)
project(Virealis)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the CMAKE_BUILD_TYPE flag if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)  # Default to Debug mode if not set explicitly
endif()

# Custom flags for Debug and Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Add debugging symbols
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building in Release mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")  # Optimization flags for release
endif()

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/glad
    ${CMAKE_SOURCE_DIR}/include/imgui
)

# Find and link GLFW and OpenGL
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add GLAD library
add_library(glad src/glad/glad.c)

# Add ImGui library
add_library(imgui STATIC
    src/imgui/imgui.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/backends/imgui_impl_glfw.cpp
    src/imgui/backends/imgui_impl_opengl3.cpp
)

# Link the libraries
target_link_libraries(glad PUBLIC OpenGL::GL)
target_link_libraries(imgui PUBLIC glfw glad)

# Collect source files from project
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp" "main.cpp")

# Create the executable from sources
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link the libraries to the executable
target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL::GL glad imgui)

# Optional: Print the current build type to ensure you're building in Debug mode
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
