/**
 * @file RigidBody.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once

namespace KitEngine::Physics
{
    class RigidBody
    {
    private:
        std::unique_ptr<btRigidBody> mbtRigidBody;
    public:
        void SetPosition(const glm::vec3& p);
    };
}