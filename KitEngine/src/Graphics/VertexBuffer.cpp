//
// Created by dryerem19 on 21.10.22.
//

#include "Graphics/VertexBuffer.h"
#include "Graphics/GlHelpers.h"

//-------------------------------------------------------------------------------------------
// Конструтор вершинного буфера
// const void* src - указатель на источник данных
// unsigned int size - размер копируемых данных
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::VertexBuffer::VertexBuffer(const void* src, unsigned int size) {

    // Создать новый буфер
    GLCall(glGenBuffers(1, &mVertexBufferId));

    // Использовать буфер
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId));

    // Скопировать данные в буфер
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, src, GL_STATIC_DRAW));

}

//-------------------------------------------------------------------------------------------
// Деструктор вершинного буфера, уничтожает буфер
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::VertexBuffer::~VertexBuffer() {

    // Cleanup
    GLCall(glDeleteBuffers(1, &mVertexBufferId));

}

//-------------------------------------------------------------------------------------------
// Использовать буфер
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::VertexBuffer::Bind() const {

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId));

}

//-------------------------------------------------------------------------------------------
// Не использовать буфер
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::VertexBuffer::Unbind() const {

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}