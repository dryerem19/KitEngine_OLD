/**
 * @file ScriptSystem.h
 * @author Denis Eremenko(mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-16
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "Components.h"

/**
 * @brief Система Script System предназначена
 * для обновления скриптов сущностей
 */
class ScriptSystem
{
private:
    lua_State* _pLuaState;
public:
    ScriptSystem();
    ~ScriptSystem();
    void update(entt::registry& registry, float deltaTime);
};