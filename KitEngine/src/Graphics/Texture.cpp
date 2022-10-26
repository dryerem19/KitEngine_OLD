//
// Created by dryerem19 on 10/23/22.
//

#include "Graphics/Texture.h"
#include <sail/sail-c++/sail-c++.h>

KitEngine::Graphics::Texture::Texture(std::string path)
    : mTextureId(0), mPath(std::move(path)) {

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
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    // Load source image
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(image.width()),
                   static_cast<GLsizei>(image.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                   image.pixels()));

    // NOT use this texture now
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

KitEngine::Graphics::Texture::~Texture() {

    GLCall(glDeleteTextures(1, &mTextureId));

}

void KitEngine::Graphics::Texture::Enable(unsigned int slotNumber /* = 0 */) const {

    GLCall(glActiveTexture(GL_TEXTURE0 + slotNumber));
    GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));

}

void KitEngine::Graphics::Texture::Disable() {

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}