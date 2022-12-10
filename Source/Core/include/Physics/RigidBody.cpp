/**
 * @file RigidBody.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#include "../pch.h"
#include "RigidBody.h"

namespace KitEngine::Physics
{
    void RigidBody::SetPosition(const glm::vec3& p)
    {
        if (!mbtRigidBody)
            return;

        auto& transform = mbtRigidBody->getWorldTransform();
        transform.setOrigin(btVector3(p.x, p.y, p.z));
        mbtRigidBody->SetWorldTransform(transform);
    }
}