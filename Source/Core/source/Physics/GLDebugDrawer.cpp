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

GLDebugDrawer::GLDebugDrawer()
{
    glGenVertexArrays(1, &mVaoId);
    glGenBuffers(1, &mVboId);

    mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/line.glsl");    
}

void GLDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{        
    glBindVertexArray(mVboId); 
    if (mFromLine != from || mToLine != to)
    {
        mFromLine = from;
        mToLine = to;
        glBindBuffer(GL_ARRAY_BUFFER, mVboId);

        const float line[] = { from.getX(), from.getY(), from.getZ(), to.getX(), to.getY(), to.getZ() };         
        glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);   
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);                       
    }     

    mShader->Enable();
    mShader->SetUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(RenderBackend::Get().GetRenderCamera()->GetViewProjection()));
    mShader->SetUniform3f("color", color.getX(), color.getY(), color.getZ());    

    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    mShader->Disable();

    // RenderBackend::Get().DebugDrawLine(glm::vec3(from.getX(), from.getY(), from.getZ()), glm::vec3(to.getX(), to.getY(), to.getZ()), 
    //     glm::vec4(color.getX(), color.getY(), color.getZ(), 1.0f));
}

void GLDebugDrawer::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{
}