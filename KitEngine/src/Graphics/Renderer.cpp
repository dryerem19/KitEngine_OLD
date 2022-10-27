//
// Created by dryerem19 on 21.10.22.
//

#include "Graphics/Renderer.h"
#include "Graphics/GlHelpers.h"

void KitEngine::Graphics::Renderer::Clear() {

    glClear(GL_COLOR_BUFFER_BIT);

}

void KitEngine::Graphics::Renderer::Draw(const KitEngine::Graphics::VertexArray &vertexArray,
                                         const KitEngine::Graphics::IndexBuffer &indexBuffer,
                                         const KitEngine::Graphics::Shader &shader) const {

    vertexArray.Bind();
    indexBuffer.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(),
                          GL_UNSIGNED_INT, nullptr));

}
