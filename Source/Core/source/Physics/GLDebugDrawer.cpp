/**
 * @file GLDebugDrawer.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Bullet Physics debug
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Denis Eremenko Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "Physics/GLDebugDrawer.h"

void GLDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
    Line line(glm::vec3(from.getX(), from.getY(), from.getZ()),
        glm::vec3(to.getX(), to.getY(), to.getZ()), glm::vec3(color.getX(), color.getY(), color.getZ()));
    line.SetMVP(mMvp);
    line.Draw();
}

void GLDebugDrawer::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{
}

void GLDebugDrawer::SetMVP(const glm::mat4 &mvp)
{
    mMvp = mvp;
}