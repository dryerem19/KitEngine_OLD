//
// Created by dryerem19 on 21.10.22.
//

#pragma once
#include "KitEnginePch.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Components/ModelComponent.h"

namespace KitEngine::Graphics
{
    class Renderer
    {
    public:
        Renderer(const Renderer&) = delete;
        Renderer& operator=(Renderer&) = delete;

        static Renderer& Instance();
        static void Initialize();

        void Clear();
        void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
        void DrawModel(const Components::ModelComponent& model, const Shader& shader,
                       const std::vector<KitEngine::Graphics::Texture> &textures);
    private:
        Renderer() = default;
        ~Renderer() = default;

    };
}