//
// Created by dryerem19 on 21.10.22.
//

#pragma once
#include "KitEnginePch.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace KitEngine::Graphics
{
    class Renderer
    {
    public:
        Renderer(const Renderer&) = delete;
        Renderer& operator=(Renderer&) = delete;

        static Renderer& Instance();

        void Clear();
        void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
    private:
        Renderer() = default;
        ~Renderer() = default;
    };
}