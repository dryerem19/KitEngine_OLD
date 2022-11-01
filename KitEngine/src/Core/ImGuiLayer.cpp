//
// Created by Denis on 01.11.2022.
//
#include "Core/ImGuiLayer.h"
#include "Core/Application.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

KitEngine::Core::ImGuiLayer::ImGuiLayer()
    : BaseLayer("ImGuiLayer") {

}

void KitEngine::Core::ImGuiLayer::OnStart() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Bold.ttf", 14, NULL,
                                 io.Fonts->GetGlyphRangesCyrillic());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    Application& app = Application::Instance();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(app.GetWindow()->GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

}

void KitEngine::Core::ImGuiLayer::OnFinish() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void KitEngine::Core::ImGuiLayer::BeginFrame() {

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void KitEngine::Core::ImGuiLayer::EndFrame() {

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
