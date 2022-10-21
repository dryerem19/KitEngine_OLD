//
// Created by dryerem19 on 21.10.22.
//

#include "Graphics/Renderer.h"
#include "Graphics/IndexBuffer.h"

//-------------------------------------------------------------------------------------------
// Конструтор индексного буфера
// const unsigned int* src - указатель на источник данных
// unsigned int count - количество индексов
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::IndexBuffer::IndexBuffer(const unsigned int* src, unsigned int count)
    : mIndicesCount(count) {

    // TODO: Добавить проверку на то, что sizeof(unsigned int) == sizeof(GLuint)

    // Создать новый буфер
    glGenBuffers(1, &mIndicesBufferId);

    // Использовать буфер
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId);

    // Скопировать данные в буфер
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), src, GL_STATIC_DRAW);

}

//-------------------------------------------------------------------------------------------
// Деструктор индексного буфера, уничтожает буфер
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::IndexBuffer::~IndexBuffer() {

    // Cleanup
    glDeleteBuffers(1, &mIndicesBufferId);

}

//-------------------------------------------------------------------------------------------
// Использовать буфер
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::IndexBuffer::Bind() const {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId);

}

//-------------------------------------------------------------------------------------------
// Не использовать буфер
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::IndexBuffer::Unbind() const {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

//-------------------------------------------------------------------------------------------
// Возвращает кол-во индексов
// return: unsigned int
//-------------------------------------------------------------------------------------------
inline unsigned int KitEngine::Graphics::IndexBuffer::GetCount() const {

    return mIndicesCount;

}