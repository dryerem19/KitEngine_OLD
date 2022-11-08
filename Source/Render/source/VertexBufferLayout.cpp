//
// Created by dryerem19 on 10/25/22.
//
#include "../pch/RenderPch.h"
#include "VertexBufferLayout.h"

Render::VertexBufferLayout::VertexBufferLayout(
        std::vector<VertexBufferAttribute> attributes)
        : mAttributes(std::move(attributes)){

}

void Render::VertexBufferLayout::AddFloatElement(const uint32_t count,
                                                              const bool normalized /* = false */) {

    mAttributes.push_back({
       static_cast<GLsizei>(count), GL_FLOAT, normalized, GLTypeSize::Float
    });
    mStride += count * GLTypeSize::Float;

}
