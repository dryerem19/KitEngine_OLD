#include "RenderBackend.h"

void RenderBackend::Render(uint32_t count, uint32_t baseVertex, uint32_t baseIndex)
{   
    stat.render.calls++;
    stat.render.verts += count;
    stat.render.polys += count / 3;

    glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, 
        reinterpret_cast<const void*>(sizeof(unsigned int) * baseIndex), baseVertex);
}

void RenderBackend::Render(uint32_t count)
{
    stat.render.calls++;
    stat.render.verts += count;
    stat.render.polys += count / 3;

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}