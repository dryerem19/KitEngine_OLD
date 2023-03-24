/**
 * @file ScriptSystem.cpp
 * @author Denis Eremenko (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-16
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "ScriptSystem.h"

#include "Entity.h"

ScriptSystem::ScriptSystem()
{
    // Создание объекта Lua
    _pLuaState = luaL_newstate();
    luaL_openlibs(_pLuaState);
}

ScriptSystem::~ScriptSystem()
{
    lua_close(_pLuaState);
}

void ScriptSystem::update(entt::registry &registry, float deltaTime)
{
    // Получаем все сущности с компонентом ScriptComponent
    auto view = registry.view<ScriptComponent>();

    // Обновляем каждую сущность
    for (auto entity : view) {
        auto& script_component = view.get<ScriptComponent>(entity);

        // Загружаем скрипт, если он ещё не загружен
        if (script_component.object.isNil()) {
            script_component.object = luabridge::getGlobal(_pLuaState, script_component.script.c_str());
        }
    }
}
