//
// Created by dryerem19 on 10/24/22.
//
#include "Graphics/VertexArray.h"
#include "Graphics/GlHelpers.h"

KitEngine::Graphics::VertexArray::VertexArray()
    : mVertexArrayId(0) {

    GLCall(glGenVertexArrays(1, &mVertexArrayId));

}

KitEngine::Graphics::VertexArray::VertexArray(VertexBuffer vertexBuffer, VertexBufferLayout layout)
    : VertexArray() {

        this->AddBuffer(vertexBuffer, layout);

}

KitEngine::Graphics::VertexArray::~VertexArray() {

    GLCall(glDeleteVertexArrays(1, &mVertexArrayId));

}

void KitEngine::Graphics::VertexArray::AddBuffer(const VertexBuffer &vertexBuffer,
                                                 const VertexBufferLayout &layout) const {

    this->Bind();
    vertexBuffer.Bind();

    const auto& attributes = layout.GetAttributes();
    GLbyte* offset = nullptr;
    for (unsigned int iAttribute = 0; iAttribute < attributes.size(); iAttribute++) {
        const auto& attribute = attributes[iAttribute];
        GLCall(glEnableVertexAttribArray(iAttribute));
        GLCall(glVertexAttribPointer(iAttribute, attribute.Count, attribute.Type, attribute.Normalized,
                              layout.GetStride(), offset));
        offset += attribute.Count * attribute.TypeSize;
    }

}

void KitEngine::Graphics::VertexArray::Bind() const {

    GLCall(glBindVertexArray(mVertexArrayId));

}

void KitEngine::Graphics::VertexArray::Unbind() {

    GLCall(glBindVertexArray(0));

}
