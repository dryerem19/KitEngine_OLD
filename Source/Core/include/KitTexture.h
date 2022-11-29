#pragma once

namespace Render
{
    enum class KitTextureType
    {
        None        = aiTextureType_NONE        ,
        Diffuse     = aiTextureType_DIFFUSE     ,
        Specular    = aiTextureType_SPECULAR    ,
        Ambient     = aiTextureType_AMBIENT     ,
        Emissive    = aiTextureType_EMISSIVE    ,
        Height      = aiTextureType_HEIGHT      ,
        Normal      = aiTextureType_NORMALS     ,
        Shinines    = aiTextureType_SHININESS   ,
    };

    class KitTexture
    {
    private:
        uint32_t mTextureId;
        KitTextureType mType;
        std::string    mPath;
    public:
        KitTexture(const std::string& path, KitTextureType type);
        ~KitTexture();

        KitTextureType GetType() const;
        std::string GetPath() const;
        uint32_t GetId() const;

        void Bind(uint32_t slotNumber = 0) const;
        void Unbind();
    };
}