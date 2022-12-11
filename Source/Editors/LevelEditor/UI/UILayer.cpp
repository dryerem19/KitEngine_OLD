//
// Created by Denis on 01.11.2022.
//
#include "UILayer.h"

#include "ResourceManager.h"
#include "Texture.h"
#include "KitModelFile.h"


#include "RenderSystem.h"

namespace LevelEditor
{
    void UILayer::OnStart()
    {
        uiViewport      = new UIViewport();
        uiTopBarTools   = new UITopBarTools();

        mUIController   = new UIController(uiTopBarTools, uiViewport);

        uiViewport->frameBuffer = &frameBuffer;
        uiTopMainMenu.uiSceneTree = &uiSceneTree;
        
        auto& app = Core::Application::Instance();
        frameBuffer.Init(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());

        EditorCamera::Instance().SetPerspective(45.0f, app.GetWindow()->GetWidth()
             / app.GetWindow()->GetHeight(), 0.1f, 100.0f);
    }

    void UILayer::EventHandler(const Core::Event& event)
    {
        const Core::EventType& type = event.GetType();
        if (type == Core::EventType::FrameBufferResizeEvent)
        {
            auto& e = (Core::FrameBufferResizeEvent&)event;

            frameBuffer.Delete();
            frameBuffer.Init(e.GetWidth(), e.GetHeight());

            EditorCamera::Instance().SetPerspective(45.0f, (float)e.GetWidth() / e.GetHeight(), 0.1f, 100.0f);
        }

        std::cout << event.ToString() << std::endl;
    }

    void UILayer::OnUpdate()
    {
        // Camera
        EditorCamera::Instance().Update();
        //Render::GameLevel::Get().Update();
        
    }

    void UILayer::OnRender(double dt) 
    {
        frameBuffer.Bind();
        Render::Renderer::Clear();

        RenderSystem::Instance().Render(EditorCamera::Instance());

        //Render::GameLevel::Get().Draw(EditorCamera::Instance().GetView(), EditorCamera::Instance().GetPerspective());

        frameBuffer.Unbind();
        Render::Renderer::Clear();
    }

    void UILayer::OnUIRender()
    {
        Docking();
        uiViewport->Draw();
        uiSceneTree.Draw();
        uiTopMainMenu.Draw();
        mToolsTab.Draw();
        mInspector.Draw();
        mBottombar.Draw();
        mUIContentBrowser.Draw();
    }

    void UILayer::OnFinish()
    {

    }

    void UILayer::Docking()
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        static ImGuiDockNodeFlags dockspace_flags;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("MenuPanel", nullptr, window_flags);


        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("RootDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

        static bool first = true;
        if(first)
        {
            first = false;
            // Если файл настроек не существует, настраиваем макет по умолчанию
            if(!std::filesystem::exists(ImGui::GetIO().IniFilename))
            {
                ImGui::DockBuilderAddNode(dockspace_id);
                ImGui::DockBuilderSetNodePos(dockspace_id,  viewport->Pos);
                ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

                ImGuiID scene_tree_id = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, nullptr, &dockspace_id);
                
                ImGuiID tools_tab_id = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.5f, nullptr, &dockspace_id);

                ImGuiID viewport_id = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.5f, nullptr, &dockspace_id);

                ImGuiID content_browser_id = ImGui::DockBuilderSplitNode(scene_tree_id, ImGuiDir_Down, 0.5f, nullptr, &scene_tree_id);

                ImGuiID object_inspector_id = ImGui::DockBuilderSplitNode(tools_tab_id, ImGuiDir_Down, 0.5f, nullptr, &tools_tab_id);

                ImGui::DockBuilderDockWindow("Scene Tree", scene_tree_id);
                ImGui::DockBuilderDockWindow("Viewport", viewport_id);
                ImGui::DockBuilderDockWindow("ToolsTab", tools_tab_id);
                ImGui::DockBuilderDockWindow("Object inspector", object_inspector_id);
                ImGui::DockBuilderDockWindow("Content Browser", content_browser_id);
                ImGui::DockBuilderFinish(dockspace_id);
            }
        }
        
        uiTopBarTools->Draw();
        
        ImGui::End();
    }
}