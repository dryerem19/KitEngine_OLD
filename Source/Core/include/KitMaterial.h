#pragma once
#include "KitMaterialFile.h"
#include "KitTexture.h"
#include "Shader.h"


#include "Interfaces/ISerialization.h"
#include "Interfaces/IDeserialization.h"

namespace Core 
{
    class ResourceManager;
}

namespace Render
{
    class KitMaterial : public ISerialization, public IDeserialization
    {
    private:
    public:
        KitMaterial(const std::string& filepath);
        std::shared_ptr<Shader> mShader;

        std::string mName;
        std::shared_ptr<KitTexture> mMainDiffuseTexture;

        void Use()
        {
            mShader->Enable();
            if (mMainDiffuseTexture)
            {
                mShader->SetUniform1i("uTextureDiffuse", 0);
                mMainDiffuseTexture->Bind();
            }
        }

        std::shared_ptr<Shader> GetShader() const
        {
            return mShader;
        }

        inline void AssignShader(std::shared_ptr<Shader> shader)
        {
            assert(shader.get() && "Shader can not be nullptr");
            mShader = shader;
        }

        void Serialize(const std::string& filepath) override;
        void Deserialize(const std::string& filepath) override;
    };
}