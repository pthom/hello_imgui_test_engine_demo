# This file is not part of any repo, just to help global compilation for all project
cmake_minimum_required(VERSION 3.17)
project(himgui_test_engine)

set(CMAKE_CXX_STANDARD 17)

# Optional: tell HelloImGui to use our own versions of imgui and imgui_test_engine
# set(HELLOIMGUI_IMGUI_SOURCE_DIR             "${CMAKE_CURRENT_LIST_DIR}/imgui"             CACHE STRING "" FORCE)
# set(HELLOIMGUI_IMGUI_TEST_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui_test_engine" CACHE STRING "" FORCE)

# Tell HelloImGui to use the test engine
set(HELLOIMGUI_WITH_TEST_ENGINE ON CACHE BOOL "Build tests" FORCE)

# This will build HelloImGui, Dear ImGui and ImGui Test Engine
add_subdirectory(hello_imgui)

# Build a simple application and link it to HelloImGui
hello_imgui_add_app(demo_test_engine_himgui demo_test_engine_himgui.cpp)
