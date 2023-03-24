/**
 * @file System.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief System interface
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once

class System
{
protected:
    entt::registry& mRegistry;
    System(entt::registry& registry);
public:
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnFinish() = 0;
};