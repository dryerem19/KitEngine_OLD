//
// Created by dryerem19 on 10/24/22.
//

#pragma once

#include "KitEnginePch.h"
#include "Renderer.h"
#include "VertexBufferAttribute.h"

namespace KitEngine::Graphics
{
    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferAttribute> mAttributes;
        unsigned int mStride{};

    public:
        explicit VertexBufferLayout() = default;
        VertexBufferLayout(const VertexBufferLayout&) = default;
        explicit VertexBufferLayout(std::vector<VertexBufferAttribute>  attributes);
        ~VertexBufferLayout() = default;

        void AddFloatElement(unsigned int count, bool normalized = false);

        [[nodiscard]] inline unsigned int GetStride() const { return mStride; }
        [[nodiscard]] inline const std::vector<VertexBufferAttribute>& GetAttributes() const { return mAttributes; }

    };
}