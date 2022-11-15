//
// Created by dryerem19 on 10/24/22.
//
#include "../pch/RenderPch.h"
#include "VertexArray.h"

Render::VertexArray::VertexArray()
    : mVertexArrayId(0) {

    GLCall(glGenVertexArrays(1, &mVertexArrayId));

}

Render::VertexArray::VertexArray(VertexBuffer vertexBuffer, VertexBufferLayout layout)
    : VertexArray() {

        this->AddBuffer(vertexBuffer, layout);

}

Render::VertexArray::~VertexArray() {

    GLCall(glDeleteVertexArrays(1, &mVertexArrayId));

     std::cout << "Удален ID: " << mVertexArrayId << std::endl;

}

void Render::VertexArray::AddBuffer(const VertexBuffer &vertexBuffer,
                                                 const VertexBufferLayout &layout) const {

    this->Bind();
    vertexBuffer.Bind();

    const auto& attributes = layout.GetAttributes();
    GLbyte* offset = nullptr;
    for (uint32_t iAttribute = 0; iAttribute < attributes.size(); iAttribute++) {
        const auto& attribute = attributes[iAttribute];
        GLCall(glEnableVertexAttribArray(iAttribute));
        GLCall(glVertexAttribPointer(iAttribute, attribute.Count, attribute.Type, attribute.Normalized,
                              layout.GetStride(), offset));
        offset += attribute.Count * attribute.TypeSize;
    }

}

void Render::VertexArray::Bind() const {

    GLCall(glBindVertexArray(mVertexArrayId));

}

void Render::VertexArray::Unbind() {

    

    GLCall(glBindVertexArray(0));

}
