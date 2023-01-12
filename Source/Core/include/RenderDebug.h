/**
 * @file RenderDebug.h
 * @author Денис Еременко (mamayma8@gmail.com)
 * @brief Набор методов для отладочного рисования
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright Денис Еременко (c) 2023
 * 
 */
#pragma once
#include "ResourceManager.h"

class RenderDebug
{
private:
    class DebugLine
    {
    public:
        glm::vec3 mStart;
        glm::vec3 mEnd;
        glm::vec4 mColor;
        uint32_t mVaoId;
        uint32_t mVboId;
        std::shared_ptr<Render::Shader> mShader;

        DebugLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4 color);
        ~DebugLine();
    };
    glm::mat4 mViewProjection;
    std::vector<DebugLine> mLines;
public:
    RenderDebug() = default;
    inline void SetViewProjection(const glm::mat4& viewProjection) { mViewProjection = viewProjection; }
    size_t AddLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);
    bool RemoveLine(const size_t& id);
    void ClearAllLines();
    void Render();
private:
    void RenderAllLines();
};