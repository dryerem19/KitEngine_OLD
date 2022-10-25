//
// Created by dryerem19 on 10/24/22.
//

#include "Graphics/VertexArray.h"
#include "Graphics/Renderer.h"

KitEngine::Graphics::VertexArray::VertexArray()
    : mVertexArrayId(0) {

    glGenVertexArrays(1, &mVertexArrayId);

}

KitEngine::Graphics::VertexArray::~VertexArray() {

    glDeleteVertexArrays(1, &mVertexArrayId);

}

void KitEngine::Graphics::VertexArray::AddBuffer(const KitEngine::Graphics::VertexBuffer &vertexBuffer,
                                     const KitEngine::Graphics::VertexBufferLayout &vertexBufferTemplate) const {

    this->Enable();
    vertexBuffer.Bind();

    unsigned int offset = 0;
    unsigned int iAttribute = 0;
    const auto& attributes = vertexBufferTemplate.GetAttributes();
    for (const auto& attribute : attributes) {
        glEnableVertexAttribArray(iAttribute);
        glVertexAttribPointer(iAttribute, attribute.Count, attribute.Type, attribute.Normalized,
                              static_cast<GLsizei>(vertexBufferTemplate.GetStride()),
                              reinterpret_cast<const void *>(offset));
        offset += attribute.Count * VertexBufferAttribute::GetSizeOfType(GLTypeSize::Float);
        iAttribute++;
    }

}

void KitEngine::Graphics::VertexArray::Enable() const {

    glBindVertexArray(mVertexArrayId);

}

void KitEngine::Graphics::VertexArray::Disable() {

    glBindVertexArray(0);

}
