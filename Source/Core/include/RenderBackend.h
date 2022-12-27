/**
 * @file RenderBackend.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include <GL/glew.h>
#include "Geometry.h"
#include "Shader.h"

#include "FrameBuffer.h"
#include "Cursor3D.h"

#include "BaseCamera.h"
#include "ResourceManager.h"

class RenderBackend final
{
private:
    RenderBackend();
    RenderBackend(const RenderBackend&) = delete;
    RenderBackend& operator=(const RenderBackend&) = delete;
public:
    struct stats
    {
        struct
        {
            uint32_t calls;
            uint32_t verts;
            uint32_t polys;
        } render;
        uint32_t vao;
        uint32_t ibo;
    } stat;
private:
    Geometry* m_pGeometry = nullptr;

    Render::FrameBuffer mFrameBuffer;
    Cursor3D mCursor3d;

    Core::BaseCamera* m_pRenderCamera;

public:

    inline static RenderBackend& Get()
    {
        static RenderBackend instance;
        return instance;
    }

    void SetRenderCamera(Core::BaseCamera* pRenderCamera);

    void BeginFrame();
    void EndFrame();
    void Resize(const int& width, const int& height, const int& x = 0, const int& y = 0);
    void* GetFrame() const { return reinterpret_cast<void*>(mFrameBuffer.GetTextureRenderID()); }

    Cursor3D& GetCursor3d() { return mCursor3d; }

    /**
     * @brief Метод рисования линии.
     * Внимание! Этот метод очень медленный и использует GL_DYNAMIC_DRAW. 
     * Рассмотрите возможность использования класса Line с GL_STATIC_DRAW.
     * @param start Начало линии 
     * @param end Конец линии
     * @param color Цвет линии
     */
    void DebugDrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);

    inline void SetGeometry(Geometry* pGeometry)
    {
        m_pGeometry = pGeometry;
    }

    inline void SetVAO(uint32_t id)
    {
        glBindVertexArray(id);
        stat.vao++;
    }

    void Clear()
    {
        float color = 85.0f/255.0f;
        glClearColor(color, color, color, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void SetIBO(uint32_t id)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        stat.ibo++;
    }

    void Render(uint32_t count, uint32_t baseVertex, uint32_t baseIndex);
    void Render();
};