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
        float mShininess    { 32.0f };

        KitMaterial();

        KitMaterial(const std::string& filepath);
        std::shared_ptr<Shader> mShader;

        std::string mName;
        std::shared_ptr<KitTexture> mMainDiffuseTexture;


        std::shared_ptr<KitTexture> mDiffuseTex;
        std::shared_ptr<KitTexture> mSpecularTex;

        std::vector<std::shared_ptr<KitTexture>> mTextures;

        void Use()
        {
            mShader->Enable();
            if (mMainDiffuseTexture)
            {
                mShader->SetUniform1i("uTextureDiffuse", 0);
                mMainDiffuseTexture->Bind();
            }
        }

        inline void AssignShader(std::shared_ptr<Shader> shader)
        {
            assert(shader.get() && "Shader can not be nullptr");
            mShader = shader;
        }

        void Serialize(const std::string& filepath) override;
        void Deserialize(const std::string& filepath) override;

        void SetTexture(const std::string& blockName, const std::shared_ptr<KitTexture>& texture);

        void Bind();
        void Unbind();

        inline void SetShader(const std::shared_ptr<Shader>& shader) { mShader = shader; }
        inline std::shared_ptr<Shader>& GetShader() { return mShader; }
    };
}