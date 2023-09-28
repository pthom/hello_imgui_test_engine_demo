# Simple demo of imgui_test_engine in combination with hello_imgui


## Minimal code to run the test engine

When integrated with HelloImGui, it becomes extremely simple to run an app with the test engine.
See [demo_test_engine_himgui.cpp](demo_test_engine_himgui.cpp), which can be summarized as:

```cpp
#include "hello_imgui/hello_imgui.h"

#include "imgui_test_engine/imgui_te_engine.h"
#include "imgui_test_engine/imgui_te_context.h"
#include "imgui_test_engine/imgui_te_ui.h"


void MyRegisterTests()
{
    ImGuiTestEngine* engine = HelloImGui::GetImGuiTestEngine();

    // Capture entire Dear ImGui Demo window.
    ImGuiTest* t = IM_REGISTER_TEST(engine, "demo_tests", "capture_screenshot");
    t->TestFunc = [](ImGuiTestContext* ctx)
    {
        ctx->SetRef("Dear ImGui Demo");
        ctx->ItemOpen("Widgets");
        ctx->ItemOpenAll("Basic");
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

    runnerParams.callbacks.ShowGui = AppGui;
    runnerParams.callbacks.RegisterTests = MyRegisterTests;

    HelloImGui::Run(runnerParams);
    return 0;
}
```


## Build instructions

### Clone this repo (or replicate its content)

```bash
git clone https://github.com/pthom/hello_imgui_test_engine_demo.git
cd hello_imgui_test_engine_demo
```

### Clone hello_imgui (and optionally imgui + imgui_test_engine)
This repository does not provide any submodule, you need to clone them manually.

```bash
git clone https://github.com/pthom/hello_imgui.git -b with_imgui_test_engine # on branch with_imgui_test_engine

# Optional: 
# HelloImGui provides imgui / imgui_test_engine as submodules in hello_imgui/external/ but we can use our own versions
#
# git clone https://github.com/ocornut/imgui.git -b docking  # on branch docking
# git clone https://github.com/ocornut/imgui_test_engine.git
```

### invoke cmake and build

Optional: if you decided to use your own versions of imgui & imgui_test_engine, edit [CMakeLists.txt](CMakeLists.txt) and uncomment 
the lines
```cmake
# set(HELLOIMGUI_IMGUI_SOURCE_DIR             "${CMAKE_CURRENT_LIST_DIR}/imgui"             CACHE STRING "" FORCE)
# set(HELLOIMGUI_IMGUI_TEST_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui_test_engine" CACHE STRING "" FORCE)
```

Then build:
```
mkdir build 
cd build
cmake ..
cmake --build . # Or build via your IDE
```
