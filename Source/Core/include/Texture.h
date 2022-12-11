//
// Created by dryerem19 on 10/23/22.
//

#pragma once

namespace Render
{
    enum class TextureType
    {
        Texture2D,
        TextureCubeMap
    };
    class Texture
    {
    private:
        uint32_t mTextureId = 0;
        TextureType mType = TextureType::Texture2D;
    public:
        explicit Texture(TextureType type);
        Texture() = default;
        ~Texture();
        void Init2D(const std::string& path);
        void InitCubeMap(std::string* pPath);
        void Enable(uint32_t slotNumber = 0) const;
        void Disable();
    };
}