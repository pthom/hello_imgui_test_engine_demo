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
