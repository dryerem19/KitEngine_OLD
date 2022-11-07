//
// Created by Denis on 01.11.2022.
//
#include "Tests/TestLayer.h"

#include <Loader.h> // from utils

#include <imgui.h>

#include <Core/Input.h>
#include <Core/Application.h>
#include <Graphics/Renderer.h>

void LevelEditor::Tests::TestLayer::OnStart() {

    kitModelLoader::Loader loader;
    loader.Import("res/models/nanosuit/nanosuit.obj");

    // TODO: Текстур может и не быть вовсе, это стоит учесть и в таком случае грузить текстуру по умолчанию
    // или назначить материал по умолчанию

    // Выводим путь до текстуры и создаём текстуру
     for (auto& material : loader.mMaterials) {
         for (auto& texture : material.mTextures) {
             if (texture.TextureType == kitModelLoader::kitTextureType::Diffuse) {
                 mTextures.emplace_back(texture.Path);
                 std::cout << texture.Path << std::endl;
             }
         }
     }


    //mTextures.emplace_back("res/models/nanosuit/body_dif.png");


     mVertexArray  = std::make_unique<KitEngine::Graphics::VertexArray>();
     mVertexBuffer = std::make_unique<KitEngine::Graphics::VertexBuffer>
             (loader.mVertices.data(), static_cast<unsigned int>(loader.mVertices.size() *
             sizeof(KitEngine::Graphics::Vertex)));

     mVertexArray->AddBuffer(*mVertexBuffer, KitEngine::Graphics::Vertex::mLayout);

     mIndexBuffer = std::make_unique<KitEngine::Graphics::IndexBuffer>(loader.mIndices.data(),
                                                                       loader.mIndices.size());

    // mModel = std::make_unique<KitEngine::Graphics::Components::ModelComponent>(*mVertexArray, *mIndexBuffer,
    //                                                                            loader.mMeshes);

    mShader = std::make_unique<KitEngine::Graphics::Shader>("res/shaders/glsl/transform_test.glsl");
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

}

void LevelEditor::Tests::TestLayer::OnUpdate() {

    // Camera
    DoMovement();

    mTransform = glm::rotate(mTransform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));
    view = glm::lookAt(cameraPos,cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(45.0f, (GLfloat)Application::Instance().GetWindow()->GetProps().Width /
                                         (GLfloat)Application::Instance().GetWindow()->GetProps().Height, 0.1f, 100.0f);

    mShader->SetUniformMatrix4fv("uView"      , 1, GL_FALSE, glm::value_ptr(view));
    mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, glm::value_ptr(projection));

    mTransform = glm::rotate(mTransform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));
    mShader->SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                               glm::value_ptr(mTransform));

}

void LevelEditor::Tests::TestLayer::OnRender(double dt) {

    KitEngine::Graphics::Renderer::Instance().Clear();

    KitEngine::Graphics::Renderer& renderer = KitEngine::Graphics::Renderer::Instance();
    renderer.DrawModel(*mModel, *mShader, mTextures);
}

void LevelEditor::Tests::TestLayer::OnUIRender() {

    // Show demo window
    ImGui::Begin("Window");
    ImGui::Text("Как дела ?");
    ImGui::End();

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
