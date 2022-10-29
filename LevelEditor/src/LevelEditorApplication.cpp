//
// Created by dryerem19 on 10/28/22.
//
#include "LevelEditorApplication.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

void LevelEditor::LevelEditorApplication::OnStart() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Bold.ttf", 14, NULL,
                                 io.Fonts->GetGlyphRangesCyrillic());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->GetWindow()->GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    Application::OnStart();
}

void LevelEditor::LevelEditorApplication::OnUpdate() {
    Application::OnUpdate();
}

void LevelEditor::LevelEditorApplication::OnRender(double dt) {


    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show demo window
    ImGui::Begin("Window");
    ImGui::Text("Как дела ?");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    Application::OnRender(dt);
}
