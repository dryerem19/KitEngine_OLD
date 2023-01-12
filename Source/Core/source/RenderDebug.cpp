/**
 * @file RenderDebug.cpp
 * @author Денис Еременко (mamayma8@gmail.com)
 * @brief Набор методов для отладочного рисования
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright Денис Еременко (c) 2023
 * 
 */
#include "pch.h"
#include "RenderDebug.h"

RenderDebug::DebugLine::DebugLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 color)
    : mStart(start), mEnd(end), mColor(color)
{
    mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/line.glsl");

    const float line[] = {
        start.x, start.y, start.z,
        end.x, end.y, end.z
    };          

    GLCall(glGenVertexArrays(1, &mVaoId));
    GLCall(glGenBuffers(1, &mVboId));
    GLCall(glBindVertexArray(mVboId));            

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVboId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW));     

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));       

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));                        
}

RenderDebug::DebugLine::~DebugLine()
{
    GLCall(glDeleteVertexArrays(1, &mVaoId));
    GLCall(glDeleteBuffers(1, &mVboId));
}

size_t RenderDebug::AddLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color)
{
    mLines.emplace_back(DebugLine(start, end, color));
    return mLines.size() - 1;
}

bool RenderDebug::RemoveLine(const size_t& id)
{
    if (id >= 0 && id < mLines.size()) {
        mLines.erase(mLines.begin() + id);
        return true;
    }

    return false;
}

void RenderDebug::ClearAllLines()
{
    mLines.clear();
}

void RenderDebug::Render()
{
    RenderAllLines();
}

void RenderDebug::RenderAllLines()
{
    for (auto& line : mLines)
    {
        if (!line.mShader) {
            DEBUG_MSG("%s", "Shader not found!");
            continue;
        }

        line.mShader->Enable();
        line.mShader->SetUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(mViewProjection));
        line.mShader->SetUniform3f("color", line.mColor.x, line.mColor.y, line.mColor.z);

        GLCall(glBindVertexArray(line.mVaoId));
        GLCall(glDrawArrays(GL_LINES, 0, 2));

        line.mShader->Disable();
        GLCall(glBindVertexArray(0));          
    }
}
