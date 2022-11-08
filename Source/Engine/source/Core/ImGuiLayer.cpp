//
// Created by Denis on 01.11.2022.
//
#include "Core/ImGuiLayer.h"
#include "Core/Application.h"

KitEngine::Core::ImGuiLayer::ImGuiLayer()
    : BaseLayer("ImGuiLayer") {
}

void KitEngine::Core::ImGuiLayer::OnStart() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->AddFontFromFileTTF("../../Resources/fonts/Roboto-Bold.ttf", 14, nullptr,
                                 io.Fonts->GetGlyphRangesCyrillic());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    Application& app = Application::Instance();
    GLFWwindow* pWindow = app.GetWindow()->GetWindowPointer();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");

}

void KitEngine::Core::ImGuiLayer::OnFinish() {

    // Уничтожаем контекст ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void KitEngine::Core::ImGuiLayer::BeginFrame() {

    // Создаём новый ImGui кадр
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void KitEngine::Core::ImGuiLayer::EndFrame() {

    // Рисуем кадр ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
