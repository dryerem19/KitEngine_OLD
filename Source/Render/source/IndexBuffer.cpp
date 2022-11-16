//
// Created by dryerem19 on 21.10.22.
//
#include "../pch/RenderPch.h"
#include "IndexBuffer.h"

//-------------------------------------------------------------------------------------------
// Деструктор индексного буфера, уничтожает буфер
//-------------------------------------------------------------------------------------------
Render::IndexBuffer::~IndexBuffer() {

    // Cleanup
    GLCall(glDeleteBuffers(1, &mIndicesBufferId));

}

void Render::IndexBuffer::Init(const uint32_t* src, const uint32_t count)
{
    // TODO: Добавить проверку на то, что sizeof(unsigned int) == sizeof(GLuint)

    mIndicesCount = count;

    // Создать новый буфер
    GLCall(glGenBuffers(1, &mIndicesBufferId));

    // Использовать буфер
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId));

    // Скопировать данные в буфер
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), src, GL_STATIC_DRAW));
}

//-------------------------------------------------------------------------------------------
// Использовать буфер
//-------------------------------------------------------------------------------------------
void Render::IndexBuffer::Bind() const {

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId));

}

//-------------------------------------------------------------------------------------------
// Не использовать буфер
//-------------------------------------------------------------------------------------------
void Render::IndexBuffer::Unbind() const {

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}