//
// Created by Denis on 01.11.2022.
//
#include "Tests/TestLayer.h"

#include <imgui.h>

#include <Graphics/Renderer.h>

void LevelEditor::Tests::TestLayer::OnStart() {

    float vertices[] = {
        // x, y, tu, tv
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };


    mVertexArray  = std::make_unique<KitEngine::Graphics::VertexArray>();
    mVertexBuffer = std::make_unique<KitEngine::Graphics::VertexBuffer>
            (vertices, 16 * sizeof(float));

    KitEngine::Graphics::VertexBufferLayout layout;
    layout.AddFloatElement(2);
    layout.AddFloatElement(2);
    mVertexArray->AddBuffer(*mVertexBuffer, layout);

    mIndexBuffer = std::make_unique<KitEngine::Graphics::IndexBuffer>(indices, 6);

    mShader = std::make_unique<KitEngine::Graphics::Shader>("res/shaders/glsl/transform_test.glsl");
    mShader->Enable();
    mShader->SetUniform4f("uColor", 0.3, 0.8, 0.8f, 1.0f);

    mTexture = std::make_unique<KitEngine::Graphics::Texture>("res/textures/no_texture.png");
    mTexture->Enable();
    mShader->SetUniform1i("uTexture", 0);

    mTransform = glm::mat4(1.0f);

}

void LevelEditor::Tests::TestLayer::OnUpdate() {

    mTransform = glm::rotate(mTransform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));
    mShader->SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                               glm::value_ptr(mTransform));

}

void LevelEditor::Tests::TestLayer::OnRender(double dt) {

    KitEngine::Graphics::Renderer::Instance().Clear();

    KitEngine::Graphics::Renderer& renderer = KitEngine::Graphics::Renderer::Instance();
    renderer.Draw(*mVertexArray, *mIndexBuffer, *mShader);
}

void LevelEditor::Tests::TestLayer::OnUIRender() {

    // Show demo window
    ImGui::Begin("Window");
    ImGui::Text("Как дела ?");
    ImGui::End();

}

void LevelEditor::Tests::TestLayer::OnFinish() {

}
