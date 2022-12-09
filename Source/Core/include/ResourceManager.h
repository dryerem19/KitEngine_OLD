#pragma once
#include "Shader.h"
#include "KitTexture.h"
#include "KitMaterial.h"

#include "Model.h"

namespace Core
{
    class ResourceManager
    {
    private:
        ResourceManager() = default;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
    private:
        std::unordered_map<std::string, std::shared_ptr<Render::Shader>> mShaders;
        std::unordered_map<std::string, std::shared_ptr<Render::KitMaterial>> mMaterials;
        std::unordered_map<std::string, std::shared_ptr<Render::KitTexture>> mTextures;

        std::unordered_map<std::string, std::shared_ptr<Model>> mModels;
 
    public:
        inline static ResourceManager& Instance()
        {
            static ResourceManager instance;
            return instance;
        }

        void LoadShader(const std::string& filepath);

        inline std::shared_ptr<Render::Shader> GetShader(const std::string& filepath)
        {
            assert(!filepath.empty() && "Filepath must not be empty!");

            bool isFind = mShaders.find(filepath) != mShaders.end(); 
            if ( !isFind )
            {
                this->LoadShader(filepath);
            }

            return mShaders.at(filepath);
        }

        /**
         * @brief Загрузка текстуры в кэш
         * 
         * @param filepath путь к текстуре
         * @return std::shared_ptr<Render::Texture> 
         */
        void LoadTexture(const std::string& filepath);

        /**
         * @brief Возвращает кэшированную текстуру, если она загружена, 
         * иначе загружает её 
         * * Вы должны рассмотреть возможность подгрузить текстуру в кэш до того, 
         * * как она фактически вам понадобится, это позволит повысить производительность
         * 
         * @param filepath путь к текстуре
         * @return std::shared_ptr<Render::Texture> 
         */
        inline std::shared_ptr<Render::KitTexture> GetTexture(const std::string& filepath)
        {
            assert(!filepath.empty() && "Filepath must not be empty!");

            bool isFind = mTextures.find( filepath ) != mTextures.end(); 
            if ( !isFind )
            {
                this->LoadTexture( filepath );
            }

            return mTextures.at( filepath );
        }

        std::shared_ptr<Render::KitMaterial> GetMaterial(const std::string& filepath);


        std::shared_ptr<Model> GetModel(const std::string& filepath)
        {
            std::shared_ptr<Model> model;
            if (mModels.find(filepath) != mModels.end())
            {
                model = mModels[filepath];
            }
            else
            {
                model = std::make_shared<Model>();
                model->Deserialize(filepath);
                mModels.insert({filepath, model});
            }

            return model;
        }
    };
}