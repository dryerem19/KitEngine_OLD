//
// Created by dryerem19 on 10/23/22.
//

#pragma once

namespace Render
{
    class Texture
    {
    private:
        uint32_t mTextureId;
        std::string mPath;
    public:
        explicit Texture(std::string  path);
        ~Texture();

        void Enable(uint32_t slotNumber = 0) const;
        static void Disable();
    };
}