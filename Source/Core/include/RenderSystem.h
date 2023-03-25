/**
 * @file RenderSystem.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Render system interface
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "System.h"
#include "Renderer.h"
#include "Components.h"

class RenderSystem final: public System
{
public:
    RenderSystem(entt::registry& registry);
    void OnStart() override final;
    void OnUpdate() override final;
    void OnFinish() override final;
private:
    //void DrawModel(const )
};