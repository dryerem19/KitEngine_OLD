#include "RenderBackend.h"

RenderBackend::RenderBackend()
{
    m_pRenderCamera = nullptr;
    mFrameBuffer.Init(100, 100);
}

void RenderBackend::SetRenderCamera(Core::BaseCamera *pRenderCamera)
{
    m_pRenderCamera = pRenderCamera;
}

void RenderBackend::BeginFrame()
{
    mFrameBuffer.Bind();
}

void RenderBackend::EndFrame()
{
    mFrameBuffer.Unbind();
}

void RenderBackend::Resize(const int &width, const int &height, const int& x /* = 0 */, const int& y /* = 0 */)
{
    glViewport(x, y, width, height);
    mFrameBuffer.Delete();
    mFrameBuffer.Init(width, height);
}

void RenderBackend::DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color)
{
    const float line[] = {
        start.x, start.y, start.z,
        end.x, end.y, end.z
    };

    unsigned int lineVAO, lineVBO;
    GLCall(glGenVertexArrays(1, &lineVAO));
    GLCall(glGenBuffers(1, &lineVBO));
    GLCall(glBindVertexArray(lineVAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, lineVBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW));

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    const auto& shader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/line.glsl");
    shader->Enable();
    shader->SetUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(m_pRenderCamera->GetViewProjection()));
    shader->SetUniform3f("color", color.x, color.y, color.z);

    GLCall(glDrawArrays(GL_LINE_STRIP, 0, 2));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
    shader->Disable();
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