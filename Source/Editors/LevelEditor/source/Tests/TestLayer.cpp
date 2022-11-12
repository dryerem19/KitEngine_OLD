//
// Created by Denis on 01.11.2022.
//
#include "Tests/TestLayer.h"

#include <Core/Input.h>
#include <Core/Application.h>

#include <OS/FileDialog.h>

void LevelEditor::Tests::TestLayer::OnStart() {

    /*kitModelLoader::Loader loader;
    loader.Import("../../Resources/models/nanosuit/nanosuit.obj");
    std::cout << std::filesystem::current_path() << std::endl;

    // TODO: Текстур может и не быть вовсе, это стоит учесть и в таком случае грузить текстуру по умолчанию
    // или назначить материал по умолчанию

    // Выводим путь до текстуры и создаём текстуру
     *//*for (auto& material : loader.mMaterials) {
         for (auto& texture : material.mTextures) {
             if (texture.TextureType == kitModelLoader::kitTextureType::Diffuse) {
                 mTextures.emplace_back(texture.Path);
                 std::cout << texture.Path << std::endl;
             }
         }
     }*//*


    mTextures.emplace_back("../../Resources/models/nanosuit/body_dif.png");


     mVertexArray  = std::make_unique<Render::VertexArray>();
     mVertexBuffer = std::make_unique<Render::VertexBuffer>
             (loader.mVertices.data(), static_cast<unsigned int>(loader.mVertices.size() *
             sizeof(Render::Vertex)));

     mVertexArray->AddBuffer(*mVertexBuffer, Render::Vertex::mLayout);

     mIndexBuffer = std::make_unique<Render::IndexBuffer>(loader.mIndices.data(),
                                                                       loader.mIndices.size());

    // mModel = std::make_unique<KitEngine::Graphics::Components::ModelComponent>(*mVertexArray, *mIndexBuffer,
    //                                                                            loader.mMeshes);

    mShader = std::make_unique<Render::Shader>("../../Resources/shaders/glsl/transform_test.glsl");
    mShader->Enable();
    mShader->SetUniform4f("uColor", 0.3, 0.8, 0.8f, 1.0f);

    mModel = std::make_unique<ModelComponent>(
            *mVertexArray, *mIndexBuffer, loader.mMeshes
    );


    // DEPRECATED
    //    mTexture = std::make_unique<KitEngine::Graphics::Texture>("res/textures/no_texture.png");
    //    mTexture->Enable();

    //testTexture.Enable();

   //mTextures[0].Enable();

    mShader->SetUniform1i("uTexture", 0);

    mTransform = glm::mat4(1.0f);*/

}

void LevelEditor::Tests::TestLayer::OnUpdate() {

    // Camera
    DoMovement();

    mTransform = glm::rotate(mTransform, 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(cameraPos,cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(45.0f, (GLfloat)Application::Instance().GetWindow()->GetProps().Width /
                                         (GLfloat)Application::Instance().GetWindow()->GetProps().Height, 0.1f, 100.0f);

    if(isModelLoaded == true){
        mShader->SetUniformMatrix4fv("uView"      , 1, GL_FALSE, glm::value_ptr(view));
        mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, glm::value_ptr(projection));


        mShader->SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                                     glm::value_ptr(mTransform));
    }

}

void LevelEditor::Tests::TestLayer::OnRender(double dt) {
    Render::Renderer::Clear();
    if(isModelLoaded == true){

        mTextures[0].Enable();
        mModel->mVertexArray.Bind();
        for (auto& mesh : mModel->mMeshes) {
            //mTextures[mesh.MaterialIndex].Enable();
            Render::Renderer::DrawIndexed(mesh.NumIndices, mesh.BaseIndex, mesh.BaseVertex);
            //mTextures[mesh.MaterialIndex].Disable();
        }
        mModel->mVertexArray.Unbind();
    }
}

void LevelEditor::Tests::TestLayer::OnUIRender() {


    // Main Menu Bar
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Open Scene")){
                std::string filepath = Engine::OS::FileDialog::OpenFile();
                std::cout << "[OpenScene]FileDialog Check: " << filepath << std::endl;
            }
            if(ImGui::MenuItem("Save Scene")){

            }
            if(ImGui::MenuItem("Save Scene As..")){
                std::string filepath = Engine::OS::FileDialog::SaveFile();
                std::cout << "[SaveSceneAs ]FileDialog Check: " << filepath << std::endl;
            }
            ImGui::Separator();
            if(ImGui::MenuItem("New Project")){

            }
            if(ImGui::MenuItem("Open Project")){
                std::string filepath = Engine::OS::FileDialog::OpenFile();
                std::cout << "[OpenProject]FileDialog Check: " << filepath << std::endl;
            }
            if(ImGui::MenuItem("Save Project")){

            }
            ImGui::Separator();
            if(ImGui::BeginMenu("Import Model"))
            {
                if(ImGui::MenuItem("Нано-костюм")){
                    OnLoadModel("../../Resources/models/nanosuit/nanosuit.obj");
                }
                ImGui::Separator();
                if(ImGui::MenuItem("Open Model"))
                {
                    std::string filepath = Engine::OS::FileDialog::OpenFile();
                    OnLoadModel(filepath);
                }
                ImGui::EndMenu();
            }
            if(ImGui::MenuItem("Exit"))
            {
                Application::Instance().Close();
            }
            ImGui::EndMenu();
        }
        static bool open = false;
        {
            if(open)
                ShowAbout(&open);
            if(ImGui::MenuItem("About"))
                open = true;
        }

    }
    ImGui::EndMainMenuBar();

}

void LevelEditor::Tests::TestLayer::OnFinish() {

}

void LevelEditor::Tests::TestLayer::DoMovement() {

    // Camera controls
    GLfloat cameraSpeed = 0.30f;
    if (Input::GetKeyDown(KeyCode::W))
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (Input::GetKeyDown(KeyCode::S))
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (Input::GetKeyDown(KeyCode::A))
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (Input::GetKeyDown(KeyCode::D))
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if(Input::GetMouseDown(MouseButton::MouseButtonLeft))
    {
        Input::SetInputMode(CursorMode::Cursor, CursorState::CursorDisabled);

        GLfloat xoffset = Input::mousePosition.x - lastX;
        GLfloat yoffset = lastY - Input::mousePosition.y;
        lastX = Input::mousePosition.x;
        lastY = Input::mousePosition.y;


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
    if(Input::GetMouseUp(MouseButton::MouseButtonLeft)){
        Input::SetInputMode(CursorMode::Cursor, CursorState::CursorNormal);
    }

}

void LevelEditor::Tests::TestLayer::OnLoadModel(std::string filepath) {
    kitModelLoader::Loader loader;
    loader.Import(filepath);
    std::cout << std::filesystem::current_path() << std::endl;

    // TODO: Текстур может и не быть вовсе, это стоит учесть и в таком случае грузить текстуру по умолчанию
    // или назначить материал по умолчанию

    // Выводим путь до текстуры и создаём текстуру
    /*for (auto& material : loader.mMaterials) {
        for (auto& texture : material.mTextures) {
            if (texture.TextureType == kitModelLoader::kitTextureType::Diffuse) {
                mTextures.emplace_back(texture.Path);
                std::cout << texture.Path << std::endl;
            }
        }
    }*/


    mTextures.emplace_back("../../Resources/models/nanosuit/body_dif.png");


    mVertexArray  = std::make_unique<Render::VertexArray>();
    mVertexBuffer = std::make_unique<Render::VertexBuffer>
            (loader.mVertices.data(), static_cast<unsigned int>(loader.mVertices.size() *
                                                                sizeof(Render::Vertex)));

    Render::VertexBufferLayout layout;
    layout.AddFloatElement(3);
    layout.AddFloatElement(3);
    layout.AddFloatElement(2);

    mVertexArray->AddBuffer(*mVertexBuffer, layout);

    mIndexBuffer = std::make_unique<Render::IndexBuffer>(loader.mIndices.data(),
                                                         loader.mIndices.size());

    // mModel = std::make_unique<KitEngine::Graphics::Components::ModelComponent>(*mVertexArray, *mIndexBuffer,
    //                                                                            loader.mMeshes);

    mShader = std::make_unique<Render::Shader>("../../Resources/shaders/glsl/transform_test.glsl");
    mShader->Enable();
    mShader->SetUniform4f("uColor", 0.3, 0.8, 0.8f, 1.0f);

    mModel = std::make_unique<ModelComponent>(
            *mVertexArray, *mIndexBuffer, loader.mMeshes
    );


    // DEPRECATED
    //    mTexture = std::make_unique<KitEngine::Graphics::Texture>("res/textures/no_texture.png");
    //    mTexture->Enable();

    //testTexture.Enable();

    //mTextures[0].Enable();

    mShader->SetUniform1i("uTexture", 0);

    mTransform = glm::mat4(1.0f);

    isModelLoaded = true;
}

void LevelEditor::Tests::TestLayer::ShowAbout(bool* close) {

    if(close)
    {
        ImGui::SetNextWindowSize(ImVec2(250,250));
        ImGui::Begin("About", close, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Name Product: KitEngine");
        ImGui::Text("Develepers: dryerem19, EvgehaName");
        ImGui::End();
    }

}