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


        glm::vec4 mDiffuse;
        glm::vec4 mSpecular;
        glm::vec4 mAmbient;
        float mShininess;

        KitMaterial() = default;

        KitMaterial(const std::string& filepath);
        std::shared_ptr<Shader> mShader;

        std::string mName;
        std::shared_ptr<KitTexture> mMainDiffuseTexture;


        std::shared_ptr<KitTexture> mDiffuseTex;
        std::shared_ptr<KitTexture> mSpecularTex;

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
        
        inline void SetDiffuse(const glm::vec4& diffuse) { mDiffuse = diffuse; }
        inline const glm::vec4& GetDiffuse() const { return mDiffuse; }
        
        inline void SetSpecular(const glm::vec4& specular) { mSpecular = specular; }
        inline const glm::vec4& GetSpecular() const { return mSpecular; }
        
        inline void SetAmbient(const glm::vec4& ambient) { mAmbient = ambient; }
        inline const glm::vec4& GetAmbient() const { return mAmbient; }
        
        inline void SetShininess(const float& shininess) { mShininess = shininess; }
        inline float GetShininess() const { return mShininess; }
    };
}