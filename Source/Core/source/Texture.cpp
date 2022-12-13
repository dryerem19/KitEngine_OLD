//
// Created by dryerem19 on 10/23/22.
//
#include "pch.h"
#include "Texture.h"

Render::Texture::Texture(TextureType type) {
    mType = type;
}

Render::Texture::~Texture() {

    GLCall(glDeleteTextures(1, &mTextureId));

}

void Render::Texture::Init2D(const std::string& path)
{
    if (path.empty()) {
        std::runtime_error("The path to the texture file cannot be empty");
    }

    // Load image
    sail::image image;
    image.load(path);

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
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    // Load source image
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(image.width()),
                   static_cast<GLsizei>(image.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                   image.pixels()));

    // NOT use this texture now

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Render::Texture::InitCubeMap(std::string* pPath)
{
    mType = TextureType::TextureCubeMap;
    assert(pPath && "The path to the texture file cannot be empty");

    // Create new texture
    GLCall(glGenTextures(1, &mTextureId));

    // Use this texture now
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId));

    // Setup filters
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    
    std::string* path = pPath;

    // Load source image
    for(uint8_t i = 0; i < 6; i++)
    {
        // Load image
        sail::image image;
        image.load(*path);

        // Check on valid
        if (!image.is_valid()) {
            std::runtime_error("Error broken image");
        }

        // Convert to RGBA
        if (SAIL_OK != image.convert(SAIL_PIXEL_FORMAT_BPP32_RGBA)) {
            std::runtime_error("Cannot convert to rgba");
        }

        GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, static_cast<GLsizei>(image.width()),
                   static_cast<GLsizei>(image.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                   image.pixels()));
        path++;
    }

    // NOT use this texture now

    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void Render::Texture::Enable(uint32_t slotNumber /* = 0 */) const {

    uint32_t type = mType == TextureType::Texture2D ? GL_TEXTURE_2D :  GL_TEXTURE_CUBE_MAP;
    GLCall(glActiveTexture(GL_TEXTURE0 + slotNumber));
    GLCall(glBindTexture(type, mTextureId));

}

void Render::Texture::Disable() {

    uint32_t type = mType == TextureType::Texture2D ? GL_TEXTURE_2D :  GL_TEXTURE_CUBE_MAP;
    GLCall(glBindTexture(type, 0));

}