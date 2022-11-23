//
// Created by Denis on 01.11.2022.
//
#include "UILayer.h"

namespace LevelEditor
{
    void UILayer::OnStart()
    {
        uiViewport      = new UIViewport();
        uiTopBarTools   = new UITopBarTools();

        mUIController   = new UIController(uiTopBarTools, uiViewport);

        uiViewport->frameBuffer = &frameBuffer;
        uiTopMainMenu.uiSceneTree = &uiSceneTree;
        mShader = std::make_unique<Render::Shader>("../../Resources/shaders/glsl/transform_test.glsl");
        mShader->Enable();
        mTransform = glm::mat4(1.0f);

        auto& app = Core::Application::Instance();
        frameBuffer.Init(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());

        auto& scene_manager = Render::SceneManager::Instance();
        scene_manager.CreateScene("test");

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
            glViewport(0, 0, e.GetWidth(), e.GetHeight());
        }

        std::cout << event.ToString() << std::endl;
    }

    void UILayer::OnUpdate()
    {
        auto& scene_manager = Render::SceneManager::Instance();

        // Camera
        EditorCamera::Instance().Update();
        
        if(uiSceneTree.isModelLoaded == true)
        {
            mShader->SetUniformMatrix4fv("uView"      , 1, GL_FALSE, EditorCamera::Instance().GetView());
            mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, EditorCamera::Instance().GetPerspective());
        }

        auto view = scene_manager.GetCurrentScene()->View<Render::KitTransform>();
        for (auto [entity, transform] : view.each())
        {
            transform.UpdateWorldTransform();
        }
    }

    void UILayer::OnRender(double dt) 
    {
        frameBuffer.Bind();
        Render::Renderer::Clear();

        auto& scene_manager = Render::SceneManager::Instance();

        auto view = scene_manager.GetCurrentScene()->View<Render::KitStaticMesh, Render::KitTransform>();
        for (auto [entity, mesh, transform] : view.each())
        {
            mShader->SetUniform1i("uTextureDiffuse", 0);
            mShader->SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                glm::value_ptr(transform.WorldTransformMatrix));      

            if(!mesh.mMaterial.diffuseTextures.empty()) {
                mesh.mMaterial.diffuseTextures[0]->Bind();
            }

            Render::Renderer::Draw(mesh.mVertexArray, mesh.mIndexBuffer); 

            if(!mesh.mMaterial.diffuseTextures.empty()){
                mesh.mMaterial.diffuseTextures[0]->Unbind();
            }             
        }

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

                ImGuiID object_inspector_id = ImGui::DockBuilderSplitNode(tools_tab_id, ImGuiDir_Down, 0.5f, nullptr, &tools_tab_id);

                ImGui::DockBuilderDockWindow("Scene Tree", scene_tree_id);
                ImGui::DockBuilderDockWindow("Viewport", viewport_id);
                ImGui::DockBuilderDockWindow("ToolsTab", tools_tab_id);
                ImGui::DockBuilderDockWindow("Object inspector", object_inspector_id);
                ImGui::DockBuilderFinish(dockspace_id);
            }
        }
        
        uiTopBarTools->Draw();
        
        ImGui::End();
    }
}