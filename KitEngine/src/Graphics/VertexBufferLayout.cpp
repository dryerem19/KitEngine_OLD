//
// Created by dryerem19 on 10/25/22.
//

#include "Graphics/VertexBufferLayout.h"
#include "Graphics/GLTypeSize.h"

KitEngine::Graphics::VertexBufferLayout::VertexBufferLayout(
        std::vector<VertexBufferAttribute> attributes)
        : mAttributes(std::move(attributes)){

}

void KitEngine::Graphics::VertexBufferLayout::AddFloatElement(const unsigned int count,
                                                              const bool normalized /* = false */) {

    mAttributes.push_back({
       static_cast<GLsizei>(count), GL_FLOAT, normalized
    });
    mStride += count * GLTypeSize::Float;

}
