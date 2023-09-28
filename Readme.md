
```bash
git clone https://github.com/pthom/hello_imgui.git -b with_imgui_test_engine # on branch with_imgui_test_engine

# Optional: 
# HelloImGui provides imgui / imgui_test_engine as submodules in hello_imgui/external/ but we can use our own versions
#
# git clone https://github.com/ocornut/imgui.git -b docking  # on branch docking
# git clone https://github.com/ocornut/imgui_test_engine.git
```

CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.17)
project(himgui_test_engine)

set(CMAKE_CXX_STANDARD 17)

# Optional: tell HelloImGui to use our own versions of imgui and imgui_test_engine
# set(HELLOIMGUI_IMGUI_SOURCE_DIR             "${CMAKE_CURRENT_LIST_DIR}/imgui"             CACHE STRING "" FORCE)
# set(HELLOIMGUI_IMGUI_TEST_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui_test_engine" CACHE STRING "" FORCE)

# Configure HelloImGui to use the test engine
set(HELLOIMGUI_WITH_TEST_ENGINE ON CACHE BOOL "Build tests" FORCE)

# This will build HelloImGui, Dear ImGui and ImGui Test Engine
add_subdirectory(hello_imgui)

# Build a simple application and link it to HelloImGui
hello_imgui_add_app(demo_test_engine_himgui demo_test_engine_himgui.cpp)

```

demo_test_engine_himgui.cpp
```cpp
#include "hello_imgui/hello_imgui.h"

#include "imgui_test_engine/imgui_te_engine.h"
#include "imgui_test_engine/imgui_te_context.h"
#include "imgui_test_engine/imgui_te_ui.h"


void MyRegisterTests()
{
    ImGuiTestEngine* engine = HelloImGui::GetImGuiTestEngine();

    ImGuiTest* t = NULL;

    // ## Open Metrics window
    t = IM_REGISTER_TEST(engine, "demo_tests", "open_metrics");
    t->TestFunc = [](ImGuiTestContext* ctx)
    {
        ctx->SetRef("Dear ImGui Demo");
        ctx->MenuCheck("Tools/Metrics\\/Debugger");
    };

    // ## Capture entire Dear ImGui Demo window.
    t = IM_REGISTER_TEST(engine, "demo_tests", "capture_screenshot");
    t->TestFunc = [](ImGuiTestContext* ctx)
    {
        ctx->SetRef("Dear ImGui Demo");
        ctx->ItemOpen("Widgets");       // Open collapsing header
        ctx->ItemOpenAll("Basic");      // Open tree node and all its descendant
        ctx->CaptureScreenshotWindow("Dear ImGui Demo", ImGuiCaptureFlags_StitchAll | ImGuiCaptureFlags_HideMouseCursor);
    };
}


void AppGui()
{
    ImGui::ShowDemoWindow();
    ImGuiTestEngine_ShowTestEngineWindows(HelloImGui::GetImGuiTestEngine(), NULL);
}


int main(int, char *[])
{
    HelloImGui::RunnerParams runnerParams;
    runnerParams.useImGuiTestEngine = true;

    // Optional: settings to replicate ImGui's default behavior: remove the default full screen window provided by HelloImGui
    runnerParams.imGuiWindowParams.configWindowsMoveFromTitleBarOnly = false;
    runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::NoDefaultWindow;

    runnerParams.callbacks.ShowGui = AppGui;
    runnerParams.callbacks.RegisterTests = MyRegisterTests;

    HelloImGui::Run(runnerParams);
    return 0;
}
```

then

```
mkdir build 
cd build
cmake .. -A x64
cmake --build .
```
