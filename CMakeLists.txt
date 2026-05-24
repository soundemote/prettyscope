cmake_minimum_required(VERSION 3.20)

project(prettyscope
    VERSION 0.1.0
    DESCRIPTION "Modern OpenGL oscilloscope and signal visualizer"
    LANGUAGES C CXX)

include(CTest)

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
    src/visual/frame_stats.cpp
    src/visual/gl_utils.cpp
    src/visual/overlay_renderer.cpp
    src/visual/persistence_buffer.cpp
    src/visual/screen_quad.cpp
    src/visual/signal_snapshot.cpp
    src/visual/scope_engine.cpp
    src/visual/scope_renderer.cpp
    src/visual/shaders.cpp
    src/visual/test_signal.cpp
    src/visual/visual_parameters.cpp
    src/visual/visual_palettes.cpp)

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

add_executable(prettyscope_host_bridge_example
    examples/host_bridge_example.cpp)

target_link_libraries(prettyscope_host_bridge_example PRIVATE
    prettyscope_core)

if(MSVC)
    target_compile_options(prettyscope_core PRIVATE /W4 /permissive-)
    target_compile_options(prettyscope PRIVATE /W4 /permissive-)
    target_compile_options(prettyscope_host_bridge_example PRIVATE /W4 /permissive-)
else()
    target_compile_options(prettyscope_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(prettyscope PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(prettyscope_host_bridge_example PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    function(add_prettyscope_core_test test_name source_path)
        set(target_name "prettyscope_${test_name}_tests")
        add_executable(${target_name}
            ${source_path})

        target_link_libraries(${target_name} PRIVATE
            prettyscope_core)

        if(MSVC)
            target_compile_options(${target_name} PRIVATE /W4 /permissive-)
        else()
            target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
        endif()

        add_test(NAME ${test_name}
            COMMAND ${target_name})
    endfunction()

    add_prettyscope_core_test(external_signal_source tests/external_signal_source_tests.cpp)
    add_prettyscope_core_test(frame_stats tests/frame_stats_tests.cpp)
    add_prettyscope_core_test(visual_param_limits tests/visual_param_limits_tests.cpp)
    add_prettyscope_core_test(signal_buffer tests/signal_buffer_tests.cpp)
    add_prettyscope_core_test(signal_snapshot tests/signal_snapshot_tests.cpp)
    add_prettyscope_core_test(scope_engine tests/scope_engine_tests.cpp)
    add_prettyscope_core_test(public_header tests/public_header_tests.cpp)
    add_prettyscope_core_test(visual_parameters tests/visual_parameters_tests.cpp)
    add_prettyscope_core_test(visual_palettes tests/visual_palettes_tests.cpp)
    add_prettyscope_core_test(shader_source tests/shader_source_tests.cpp)
endif()
