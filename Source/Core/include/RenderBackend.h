#pragma once
#include <GL/glew.h>

class RenderBackend final
{
private:
    RenderBackend() = default;
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
    } stat;

    inline static RenderBackend& Get()
    {
        static RenderBackend instance;
        return instance;
    }

    void Render(uint32_t count, uint32_t baseVertex, uint32_t baseIndex);
    void Render(uint32_t count);
};