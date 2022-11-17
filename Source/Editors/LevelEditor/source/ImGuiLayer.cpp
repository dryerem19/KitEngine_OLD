//
// Created by Denis on 01.11.2022.
//
#include "ImGuiLayer.h"
#include "IconsFontAwesome6.h"
#include "Core/Application.h"


LevelEditor::ImGuiLayer::ImGuiLayer()
    : KitEngine::Core::BaseLayer("ImGuiLayer") {
}

void LevelEditor::ImGuiLayer::OnStart() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Enable docking window
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    io.Fonts->AddFontFromFileTTF("../../Resources/fonts/Roboto-Bold.ttf", 14, nullptr,
                                 io.Fonts->GetGlyphRangesCyrillic());
    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF( "../../Resources/fonts/fa-solid-900.ttf", 14.0f, &icons_config, icons_ranges );


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    KitEngine::Core::Application& app = KitEngine::Core::Application::Instance();
    GLFWwindow* pWindow = app.GetWindow()->GetWindowPointer();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

}

void LevelEditor::ImGuiLayer::OnFinish() {

    // Уничтожаем контекст ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void LevelEditor::ImGuiLayer::OnBegin() {

    // Создаём новый ImGui кадр
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

}

void LevelEditor::ImGuiLayer::OnEnd() {

    // Рисуем кадр ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
