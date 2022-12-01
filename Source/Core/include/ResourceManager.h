#pragma once
#include "Shader.h"
#include "Texture.h"

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
        std::unordered_map<std::string, std::shared_ptr<Render::Texture>> mTexturs;
    public:
        inline static ResourceManager& Instance()
        {
            static ResourceManager instance;
            return instance;
        }

        inline std::shared_ptr<Render::Shader> LoadShader(const std::string& filepath)
        {
            assert(!filepath.empty() && "Filepath must not be empty!");
            
            return mShaders.emplace(std::make_shared<Render::Shader>(filepath));
        }
        
        inline std::shared_ptr<Render::Shader> GetShader(const std::string& filepath) const
        {
            assert(!filepath.empty() && "Filepath must not be empty!")

            if (mShaders.find(filepath) != mShaders.end())
            {
                return mShaders[filepath];
            }
            else
            {
                return this->LoadSahder(filepath);
            }
        }

        /**
         * @brief Загрузка текстуры в кэш
         * 
         * @param filepath путь к текстуре
         * @return std::shared_ptr<Render::Texture> 
         */
        inline std::shared_ptr<Render::Texture> LoadTexture(const std::string& filepath)
        {
            assert(!filepath.empty() && "Filepath must not be empty!");

            std::shared_ptr<Render::Texture> texture = std::make_shared<Render::Texture>(filepath);
            return mTexturs.emplace(texture);
        }

        /**
         * @brief Возвращает кэшированную текстуру, если она загружена, 
         * иначе загружает её 
         * * Вы должны рассмотреть возможность подгрузить текстуру в кэш до того, 
         * * как она фактически вам понадобится, это позволит повысить производительность
         * 
         * @param filepath путь к текстуре
         * @return std::shared_ptr<Render::Texture> 
         */
        inline std::shared_ptr<Render::Texture> GetTexture(const std::string& filepath) const
        {
            assert(!filepath.empty() && "Filepath must not be empty!");

            if (mTexturs.find(filepath) != mTexturs.end())
            {
                return mTexturs[filepath];
            }
            else
            {
                return this->LoadTexture(filepath);
            }
        }
    };
}