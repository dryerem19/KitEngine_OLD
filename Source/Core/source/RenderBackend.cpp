#include "RenderBackend.h"

RenderBackend::RenderBackend()
{
    mFrameBuffer.Init(100, 100);
}

void RenderBackend::BeginFrame()
{
    mFrameBuffer.Bind();
}

void RenderBackend::EndFrame()
{
    mFrameBuffer.Unbind();
}

void RenderBackend::Resize(const int &width, const int &height)
{
    glViewport(0, 0, width, height);
    mFrameBuffer.Delete();
    mFrameBuffer.Init(width, height);
}

void RenderBackend::Render(uint32_t count, uint32_t baseVertex, uint32_t baseIndex)
{   
    stat.render.calls++;
    stat.render.verts += count;
    stat.render.polys += count / 3;

    glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, 
        reinterpret_cast<const void*>(sizeof(unsigned int) * baseIndex), baseVertex);
}

void RenderBackend::Render()
{
    if (!m_pGeometry)
    {
        return;
    }

    SetVAO(m_pGeometry->vao.GetId());
    SetIBO(m_pGeometry->ibo.id());

    stat.render.calls++;
    stat.render.verts += m_pGeometry->ibo.GetCount();
    stat.render.polys += m_pGeometry->ibo.GetCount() / 3;

    glDrawElements(GL_TRIANGLES, m_pGeometry->ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}