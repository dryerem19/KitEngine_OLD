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
        out << YAML::Key << "Name";
        out << YAML::Value << mName;

        std::ofstream fout(mName + ".material");
        fout << out.c_str();
    }

    void KitMaterial::Deserialize(const std::string& filepath)
    {

    }
}