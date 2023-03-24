//
// Created by dryerem19 on 21.10.22.
//
#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *src, const uint32_t size)
{
    Init(src, size);
}

//-------------------------------------------------------------------------------------------
// Деструктор вершинного буфера, уничтожает буфер
//-------------------------------------------------------------------------------------------
VertexBuffer::~VertexBuffer() {

    // Cleanup
    GLCall(glDeleteBuffers(1, &mVertexBufferId));

}

void VertexBuffer::Init(const void* src, const uint32_t size)
{
    /* Создаём объект вершинного буфера, который будет хранить вершины в видеопамяти */
    GLCall(glGenBuffers(1, &mVertexBufferId));

    /* Выделяем место и загружаем данные вершин из CPU в GPU */
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, src, GL_STATIC_DRAW));
}

//-------------------------------------------------------------------------------------------
// Использовать буфер
//-------------------------------------------------------------------------------------------
void VertexBuffer::Bind() const {

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId));

}

//-------------------------------------------------------------------------------------------
// Не использовать буфер
//-------------------------------------------------------------------------------------------
void VertexBuffer::Unbind() const {

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}