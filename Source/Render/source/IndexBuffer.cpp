//
// Created by dryerem19 on 21.10.22.
//
#include "../pch/RenderPch.h"
#include "IndexBuffer.h"

//-------------------------------------------------------------------------------------------
// Конструтор индексного буфера
// const unsigned int* src - указатель на источник данных
// unsigned int count - количество индексов
//-------------------------------------------------------------------------------------------
Render::IndexBuffer::IndexBuffer(const uint32_t* src, uint32_t count)
    : mIndicesCount(count) {

    // TODO: Добавить проверку на то, что sizeof(unsigned int) == sizeof(GLuint)

    // Создать новый буфер
    GLCall(glGenBuffers(1, &mIndicesBufferId));

    // Использовать буфер
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId));

    // Скопировать данные в буфер
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), src, GL_STATIC_DRAW));

}

//-------------------------------------------------------------------------------------------
// Деструктор индексного буфера, уничтожает буфер
//-------------------------------------------------------------------------------------------
Render::IndexBuffer::~IndexBuffer() {

    // Cleanup
    GLCall(glDeleteBuffers(1, &mIndicesBufferId));

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