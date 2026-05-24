cmake_minimum_required(VERSION 3.20)

project(prettyscope
    VERSION 0.1.0
    DESCRIPTION "Modern OpenGL oscilloscope and signal visualizer"
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(prettyscope_glad STATIC
    Shared/glad/3.2/src/glad.c)

target_include_directories(prettyscope_glad PUBLIC
    Shared/glad/3.2/include)

add_library(prettyscope_core STATIC
    src/visual/beam_renderer.cpp
    src/visual/external_signal_source.cpp
    src/visual/gl_utils.cpp
    src/visual/overlay_renderer.cpp
    src/visual/persistence_buffer.cpp
    src/visual/screen_quad.cpp
    src/visual/scope_renderer.cpp
    src/visual/shaders.cpp
    src/visual/test_signal.cpp)

target_include_directories(prettyscope_core PUBLIC
    src)

target_link_libraries(prettyscope_core PUBLIC
    prettyscope_glad
    opengl32)

target_compile_definitions(prettyscope_core PUBLIC
    WIN32_LEAN_AND_MEAN
    NOMINMAX)

add_executable(prettyscope
    src/main.cpp
    src/app/preset_store.cpp
    src/app/standalone_app.cpp
    src/app/standalone_controls.cpp
    src/platform/win32_gl_window.cpp)

target_include_directories(prettyscope PRIVATE
    src)

target_link_libraries(prettyscope PRIVATE
    prettyscope_core
    gdi32
    user32)

if(MSVC)
    target_compile_options(prettyscope_core PRIVATE /W4 /permissive-)
    target_compile_options(prettyscope PRIVATE /W4 /permissive-)
else()
    target_compile_options(prettyscope_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(prettyscope PRIVATE -Wall -Wextra -Wpedantic)
endif()
