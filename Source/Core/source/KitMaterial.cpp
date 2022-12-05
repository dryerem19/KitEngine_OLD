#include "pch.h"
#include "KitMaterial.h"

namespace Render
{
    KitMaterial::KitMaterial()
    {
        mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/glsl/transform_test.glsl");
    }

    void KitMaterial::Serialize()
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Name" << YAML::Value << mName;
        out << YAML::Key << "Diffuse" << YAML::Value << mMainDiffuseTexture->GetPath();        
        out << YAML::EndMap;

        std::ofstream fout("data/" + mName + ".material");
        fout << out.c_str();
    }

    void KitMaterial::Deserialize(const std::string& filepath)
    {

    }
}