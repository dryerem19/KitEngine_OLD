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
#include "Geometry.h"
//#include "Shader.h"

#include "FrameBuffer.h"
#include "Cursor3D.h"

#include "BaseCamera.h"
//#include "ResourceManager.h"

#include "RenderDebug.h"

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

    BaseCamera* m_pRenderCamera;

public:
    //RenderDebug mRenderDebug;


    inline static RenderBackend& Get()
    {
        static RenderBackend instance;
        return instance;
    }

    inline BaseCamera* GetRenderCamera() { return m_pRenderCamera; }
    void SetRenderCamera(BaseCamera* pRenderCamera);

    void BeginFrame();
    void EndFrame();
    void Resize(const int& width, const int& height, const int& x = 0, const int& y = 0);


    uint32_t* GetFrame() 
    {
        uintptr_t renderTargetId = mFrameBuffer.GetTextureRenderID();
        return reinterpret_cast<uint32_t*>(renderTargetId); 
    }  

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

    
    glm::vec3 dbg_st_line, dbg_en_line;
    glm::vec4 dbg_col_line;
    void SetDebugDrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
    {
        dbg_st_line = start;
        dbg_en_line = end;
        dbg_col_line = color;
    }
    
    void _DebugDrawLine()
    {
        DebugDrawLine(dbg_st_line, dbg_en_line, dbg_col_line);
    }

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