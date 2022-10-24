//
// Created by dryerem19 on 10/23/22.
//

#pragma once
#include "Graphics/Renderer.h"

namespace KitEngine::Graphics
{
    class Texture
    {
    private:
        unsigned int mTextureId;
        std::string mPath;
    public:
        explicit Texture(std::string  path);
        ~Texture();

        void Enable(unsigned int slotNumber = 0) const;
        static void Disable();
    };
}