#include "pch.h"
#include "KitTexture.h"

Render::KitTexture::KitTexture(const std::string& path, KitTextureType type)
    : mPath(path), mType(type)
{
        if (mPath.empty()) {
        std::runtime_error("The path to the texture file cannot be empty");
    }

    // TODO: Проверять путь к текстуре!!!!!

    // Load image
    sail::image image;
    image.load(mPath);

    // Check on valid
    if (!image.is_valid()) {
        std::runtime_error("Error broken image");
    }

    // Convert to RGBA
    if (SAIL_OK != image.convert(SAIL_PIXEL_FORMAT_BPP32_RGBA)) {
        std::runtime_error("Cannot convert to rgba");
    }

    // Create new texture
    GLCall(glGenTextures(1, &mTextureId));

    // Use this texture now
    GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));

    // Setup filters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    // Load source image
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(image.width()),
                   static_cast<GLsizei>(image.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                   image.pixels()));

    // NOT use this texture now

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}   

Render::KitTexture::~KitTexture()
{
    GLCall(glDeleteTextures(1, &mTextureId));
}

Render::KitTextureType Render::KitTexture::GetType() const 
{
    return mType;
}

std::string Render::KitTexture::GetPath() const
{
    return mPath;
}

uint32_t Render::KitTexture::GetId() const
{
    return mTextureId;
}

void Render::KitTexture::Bind(uint32_t slotNumber) const 
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slotNumber));
    GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
}

void Render::KitTexture::Unbind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}