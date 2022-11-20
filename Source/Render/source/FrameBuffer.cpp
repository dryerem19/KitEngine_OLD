//
// Created by piokxix on 14.11.22.
//

#include "RenderPch.h"
#include "FrameBuffer.h"

Render::FrameBuffer::~FrameBuffer() {
    this->Delete();
}

Render::FrameBuffer::FrameBuffer()
 {

}

void Render::FrameBuffer::Init(uint32_t width, uint32_t height)
{
    // Создание кадрового буфера
    GLCall(glCreateFramebuffers(1,&mFrameBufferId));

    // Привязка кадрового буфера
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId));

    // Создание текстуры
    GLCall(glGenTextures(1, &mTextureId));
    // Привязка текстуры
    GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
    // Установка текстуры
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
    // Установка параметров текстуры
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureId, 0));

    GLCall(glCreateTextures(GL_TEXTURE_2D, 1,  &mDepthId));
    GLCall(glBindTexture(GL_TEXTURE_2D, mDepthId));

    GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthId, 0));

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "not compiler" << std::endl;

    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Render::FrameBuffer::Delete()
{
    GLCall(glDeleteFramebuffers(1, &mFrameBufferId));
}

void Render::FrameBuffer::Bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId));
}

void Render::FrameBuffer::Unbind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

/*void Render::FrameBuffer::GetFlipTexture() {
    GLCall(glReadPixels(0,0,800,600,GL_RGB,GL_UNSIGNED_BYTE,));
}*/
