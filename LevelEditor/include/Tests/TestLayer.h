//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_TESTLAYER_H
#define KITENGINE_TESTLAYER_H

#include <Core/BaseLayer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Texture.h>
#include <Graphics/Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LevelEditor::Tests
{
    class TestLayer : public KitEngine::Core::BaseLayer
    {
    private:
        std::unique_ptr<KitEngine::Graphics::VertexArray>  mVertexArray;
        std::unique_ptr<KitEngine::Graphics::VertexBuffer> mVertexBuffer;
        std::unique_ptr<KitEngine::Graphics::IndexBuffer>  mIndexBuffer;
        std::unique_ptr<KitEngine::Graphics::Shader>       mShader;
        std::unique_ptr<KitEngine::Graphics::Texture>      mTexture;
        glm::mat4                                          mTransform;
    public:
        TestLayer() = default;

        void OnStart() override;
        void OnUpdate() override;
        void OnFrameRender(double dt) override;
        void OnUIRender() override;
        void OnFinish() override;
    };
}

#endif //KITENGINE_TESTLAYER_H
