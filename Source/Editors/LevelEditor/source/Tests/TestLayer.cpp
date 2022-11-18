//
// Created by Denis on 01.11.2022.
//
#include "Tests/TestLayer.h"

#include <Input.h>
#include <Application.h>

#include "IconsFontAwesome6.h"

#include <fmt/format.h>
#include <Events/WindowResizeEvent.h>
#include <Events/FrameBufferResizeEvent.h>


void LevelEditor::Tests::TestLayer::OnStart() 
{
    mShader = std::make_unique<Render::Shader>("../../Resources/shaders/glsl/transform_test.glsl");
    mShader->Enable();
    mTransform = glm::mat4(1.0f);
}

void LevelEditor::Tests::TestLayer::EventHandler(const Core::Event& event)
{
    const Core::EventType& type = event.GetType();
    if (type == Core::EventType::FrameBufferResizeEvent)
    {
        auto& e = (Core::FrameBufferResizeEvent&)event;
        projection = glm::perspective(45.0f, (float)e.GetWidth() / e.GetHeight(), 0.1f, 100.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());   
    }

    std::cout << event.ToString() << std::endl;
}

void LevelEditor::Tests::TestLayer::OnUpdate() {

    // Camera
    DoMovement();

    mTransform = glm::rotate(mTransform, 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(cameraPos,cameraPos + cameraFront, cameraUp);

    if(isModelLoaded == true){
        mShader->SetUniformMatrix4fv("uView"      , 1, GL_FALSE, glm::value_ptr(view));
        mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, glm::value_ptr(projection));

    }

}

void LevelEditor::Tests::TestLayer::OnRender(double dt) 
{
    frameBuffer.Bind();
    Render::Renderer::Clear();

    if(isModelLoaded == true)
    {
        for (auto& mesh : mNanoModel)
        {
            if(!mesh->mMaterial.diffuseTextures.empty()){
                mesh->mMaterial.diffuseTextures[0]->Bind();
            }
            
            mShader->SetUniform1i("uTextureDiffuse", 0);
            mShader->SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                    glm::value_ptr(mesh->mTransform.GetTransform()));
            Render::Renderer::Draw(mesh->mVertexArray, mesh->mIndexBuffer);
            
            if(!mesh->mMaterial.diffuseTextures.empty()){
                mesh->mMaterial.diffuseTextures[0]->Unbind();
            }
        }
    }

    frameBuffer.Unbind();
    Render::Renderer::Clear();
}

void LevelEditor::Tests::TestLayer::OnUIRender() {
    // Docking Window
    Docking();
    Viewport();
    ImGui::Begin("Scene Tree");
    {
        SceneTree();
    }
    ImGui::End();
    // Main Menu Bar
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu(ICON_FA_FILE " File"))
        {
            if(ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open Scene")){

            }
            if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Scene")){

            }
            if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Scene As..")){
                
            }
            ImGui::Separator();
            if(ImGui::MenuItem(ICON_FA_SQUARE_PLUS " New Project")){

            }
            if(ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open Project")){
                
            }
            if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Project")){

            }
            ImGui::Separator();
            if(ImGui::BeginMenu("Import Model"))
            {
                if(ImGui::MenuItem("Нано-костюм")){
                    OnLoadModel("../../Resources/models/nanosuit/nanosuit.obj");
                }
                ImGui::Separator();
                if(ImGui::MenuItem(ICON_FA_FILE_IMPORT " Open Model"))
                {
                    isCheckFileDialog = true;
                }
                                
                ImGui::EndMenu();
            }
            if(ImGui::MenuItem(ICON_FA_RIGHT_FROM_BRACKET " Exit"))
            {
                Core::Application::Instance().Close();
            }
            ImGui::EndMenu();
        }
        static bool open = false;
        {
            if(open)
                ShowAbout(&open);
            if(ImGui::MenuItem(ICON_FA_ADDRESS_CARD " About"))
                open = true;
        }

    }
    ImGui::EndMainMenuBar();

    // Create FileDialog
    if(isCheckFileDialog){
        std::string filepath = FileDialog();
        if(!filepath.empty()){
            OnLoadModel(filepath);
        }
    }

}

void LevelEditor::Tests::TestLayer::OnFinish() {

}

void LevelEditor::Tests::TestLayer::DoMovement() {

    // Camera controls
    GLfloat cameraSpeed = 0.30f;
    if (Core::Input::GetKey(Core::KeyCode::W))
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (Core::Input::GetKey(Core::KeyCode::S))
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (Core::Input::GetKey(Core::KeyCode::A))
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (Core::Input::GetKey(Core::KeyCode::D))
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if(Core::Input::GetMouseButton(Core::MouseButton::MouseButtonRight))
    {
        Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorDisabled);
        
        GLfloat xoffset = Core::Input::mousePosition.x - lastX;
        GLfloat yoffset = lastY - Core::Input::mousePosition.y;

        // Установка курсора на последнее подложение камеры
        if(isCheckMouse)
        {
            Core::Input::SetCursorPos(lastX, lastY);
            isCheckMouse = false;
        }

        lastX = Core::Input::mousePosition.x;
        lastY = Core::Input::mousePosition.y;
        
        GLfloat sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

    }
    if(Core::Input::GetMouseUp(Core::MouseButton::MouseButtonRight)){
        Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorNormal);
        isCheckMouse = true;
        // Установка последних координт камеры на позицию мыши
        Core::Input::mousePosition.x = lastX;
        Core::Input::mousePosition.y = lastY;
    }

}

void LevelEditor::Tests::TestLayer::OnLoadModel(std::string filepath) {

    mNanoModel.Init(filepath);
    isModelLoaded = true;
}

void LevelEditor::Tests::TestLayer::ShowAbout(bool* close) {

    if(close)
    {
        ImGui::SetNextWindowSize(ImVec2(250,250));
        ImGui::Begin("About", close, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);
        ImGui::Text("Name Product: KitEngine");
        ImGui::Text("Develepers: dryerem19, EvgehaName");
        ImGui::End();
    }

}

void LevelEditor::Tests::TestLayer::Docking() {

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

    ImGui::DockSpace(ImGui::GetID("DockSpace"), ImVec2(0.0f, 0.0f), dockspace_flags);

    if(ImGui::BeginMenuBar())
    {
        if(ImGui::MenuItem(ICON_FA_CIRCLE_ARROW_LEFT))
        {

        }
        if(ImGui::MenuItem(ICON_FA_CIRCLE_ARROW_RIGHT))
        {

        }
        if(ImGui::MenuItem(ICON_FA_ARROW_POINTER))
        {

        }
        if(ImGui::MenuItem(ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT))
        {

        }
        if(ImGui::MenuItem(ICON_FA_ROTATE))
        {

        }
        if(ImGui::MenuItem(ICON_FA_UP_RIGHT_FROM_SQUARE))
        {

        }
        ImGui::Separator();
        if(ImGui::BeginMenu(ICON_FA_DRAW_POLYGON))
        {
            if(ImGui::MenuItem(ICON_FA_CIRCLE " Vertices"))
            {
                Render::Renderer::Wireframe(Render::WireframeMode::Vertices);
            }
            if(ImGui::MenuItem(ICON_FA_SLASH " Edge"))
            {
                Render::Renderer::Wireframe(Render::WireframeMode::Edge);
            }
            if(ImGui::MenuItem(ICON_FA_SQUARE " Polygon"))
            {
                Render::Renderer::Wireframe(Render::WireframeMode::Polygon);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

}

void LevelEditor::Tests::TestLayer::Viewport() {
    uint32_t backTexture = frameBuffer.GetTextureRenderID();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    ImGui::Begin("Viewport");
    {
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();
        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;
        ImGui::GetWindowDrawList()->AddImage((ImTextureID)backTexture, vMin, vMax, ImVec2(0,1), ImVec2(1,0));

        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(vMin.x, vMin.y, ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);

        if (mSelectedObject)
        {
            auto& transform = mSelectedObject->mTransform;

            float translationComponent[3] = 
            { 
                transform.Translation.x,
                transform.Translation.y,
                transform.Translation.z
            };

            float rotationComponent[3] =
            { 
                transform.Rotation.x,
                transform.Rotation.y,
                transform.Rotation.z
            };

            float scaleComponent[3] =
            { 
                transform.Scale.x,
                transform.Scale.y,
                transform.Scale.z
            };

            /* Build transform matrix */
            float transformMatrix[16];
            ImGuizmo::RecomposeMatrixFromComponents(translationComponent, rotationComponent, scaleComponent, transformMatrix);
            ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::TRANSLATE, ImGuizmo::MODE::LOCAL, transformMatrix);

            /* If we moved the manipulator */
            if (ImGuizmo::IsUsing())
            {
                /* We get new transformed components */
                float translationComponent[3] = {}, rotationComponent[3] = {}, scaleComponent[3] = {};
                ImGuizmo::DecomposeMatrixToComponents(transformMatrix, translationComponent, rotationComponent, scaleComponent);

                /* Restore the new transformed components */
                transform.Translation = 
                {
                    translationComponent[0],
                    translationComponent[1],
                    translationComponent[2]
                };
                transform.Rotation =
                {
                    rotationComponent[0], 
                    rotationComponent[1], 
                    rotationComponent[2]
                };
                transform.Scale =
                {
                    scaleComponent[0],
                    scaleComponent[1],
                    scaleComponent[2]
                };
            }
        }
	} 
    ImGui::End();
    ImGui::PopStyleVar();
}

std::string LevelEditor::Tests::TestLayer::FileDialog(){
    std::string filepath;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".fbx,.obj,.stl,.*", ".");
    ImGui::SetNextWindowSizeConstraints(ImVec2(600,400), ImVec2(-1,-1));
    if(ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")){
        if(ImGuiFileDialog::Instance()->IsOk()){
            filepath = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
        isCheckFileDialog = false;
    }
    return filepath;
}

void LevelEditor::Tests::TestLayer::SceneTree()
{
    if(isModelLoaded)
    {
        if(ImGui::TreeNode(mNanoModel.mName.c_str()))
        {
            for(auto& mesh : mNanoModel)
            {
                ImGuiTreeNodeFlags flags = mesh->mChildren.empty() ? ImGuiTreeNodeFlags_Leaf : 0;
                if(ImGui::TreeNodeEx(fmt::format("{}\t{}", ICON_FA_CUBE, mesh->mName).c_str(), flags))
                {
                    ImGui::TreePop();
                }

                if (ImGui::IsItemClicked()) {
                    mSelectedObject = mesh;
                }                
            }
            ImGui::TreePop();
        }

        if (ImGui::IsItemClicked()) {
            mSelectedObject = static_cast<std::shared_ptr<Render::KitObject>>(&mNanoModel);
        }        
    }
}
