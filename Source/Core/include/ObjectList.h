/**
 * @file ObjectList.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once

class GameObject;

class ObjectList final
{
private:
    std::unordered_map<std::string, std::unique_ptr<GameObject>> mObjects;
public:
    GameObject* Create(const std::string& name);
    inline GameObject* FindObjectByName(const std::string& name)
    {
        return mObjects.find(name) != mObjects.end() ? mObjects[name].get() : nullptr;
    }
};