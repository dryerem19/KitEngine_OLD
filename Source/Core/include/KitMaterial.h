#pragma once
#include "KitTexture.h"
#include "Shader.h"
#include "ResourceManager.h"

namespace Render
{
    class KitMaterial
    {
    private:
    public:
        KitMaterial();
        std::shared_ptr<Shader> mShader;

        std::string mName;
        std::shared_ptr<KitTexture> mMainDiffuseTexture;

        void Use()
        {
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

        // inline void UseMaterial() const
        // {
        //     mShader.get()->Enable();

        //     mShader->SetUniform1i("uTextureDiffuse", 0);
        //     if(!diffuseTextures.empty()) {
        //         diffuseTextures[0]->Bind();
        //     }            
        // }

        // inline void UnuseMaterial() const
        // {
        //     mShader.get()->Disable();
        // }

        // inline void SetShaderFromFile(const std::string& filepath)
        // {
        //     assert(filepath.empty());

        //     mShader = std::make_shared<Shader>(filepath);
        // }

        // inline std::shared_ptr<Shader> GetShader() const
        // {
        //     return mShader;
        // }
    };
}