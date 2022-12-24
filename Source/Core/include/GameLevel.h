#pragma once
#include "Entity.h"

#include "Interfaces/IDeserialization.h"
#include "Interfaces/ISerialization.h"
#include "Skybox.h"
#include "KitLight.h"

#include "SoundBuffer.h"

#include <BulletDynamics/btBulletDynamicsCommon.h>


class GameLevel : public ISerialization, public IDeserialization
{
private:
    GameLevel();
    GameLevel(const GameLevel&) = delete;
    GameLevel& operator=(GameLevel&) = delete;
    ~GameLevel() = default;
private:
    std::unordered_map<std::string, std::unique_ptr<Entity>> mObjects;
    std::unordered_map<std::string, uint32_t> mRegistryNames;
    KitObject* mSelectedObject = nullptr; 
    SkyBox mSkyBox;
public:
    std::vector<std::unique_ptr<KitLight>> _lights;
    //std::vector<std::shared_ptr<Entity>> mEntities;
    std::vector<std::unique_ptr<Entity>> _objects; 

    std::vector<std::unique_ptr<SoundBuffer>> _soundsources; 

    static GameLevel& Get();

    void Clear();

    void Serialize(const std::string& filepath) override final;
    void Deserialize(const std::string& filepath) override final;


    void Draw(const float* view_matrix, float* proj_matrix);

    void InitSkybox(const std::string& filepath);

    SkyBox& GetSkybox() { return mSkyBox; }

    KitLight* CreateLigth();

    void DeleteLight();

    Entity* CreateEntity();

    SoundBuffer* CreateSound();

    inline void SetSelectedObject(KitObject* object)
    {
        mSelectedObject = object;
    }

    inline KitObject* GetSelectedObject() const
    {
        return mSelectedObject;
    }

    /**
     * @brief Поиск объекта по его имени
     * 
     * @param name имя объекта
     * @return Entity* 
     */
    inline Entity* FindObjectByName(const std::string& name)
    {
        Entity* pEntity = nullptr;
        for (auto& entity : _objects) {
            if (entity->GetName() == name) {
                pEntity = entity.get();
                break;
            }
        }

        return pEntity;
    }        
    
    // inline std::unordered_map<std::string, std::unique_ptr<Entity>>::iterator begin() noexcept
    // {
    //     return mObjects.begin();
    // }

    // inline std::unordered_map<std::string, std::unique_ptr<Entity>>::iterator end() noexcept
    // {
    //     return mObjects.end();
    // }  

    // inline std::unordered_map<std::string, std::unique_ptr<Entity>>::const_iterator cbegin() const noexcept
    // {
    //     return mObjects.cbegin();
    // }

    // inline std::unordered_map<std::string, std::unique_ptr<Entity>>::const_iterator cend() const noexcept
    // {
    //     return mObjects.cend();
    // }                
};