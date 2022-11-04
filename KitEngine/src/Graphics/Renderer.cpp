//
// Created by dryerem19 on 21.10.22.
//

#include "Graphics/Renderer.h"
#include "Graphics/GlHelpers.h"

void KitEngine::Graphics::Renderer::Clear() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void KitEngine::Graphics::Renderer::Draw(const KitEngine::Graphics::VertexArray &vertexArray,
                                         const KitEngine::Graphics::IndexBuffer &indexBuffer,
                                         const KitEngine::Graphics::Shader &shader) const {

    vertexArray.Bind();
    //indexBuffer.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(),
                          GL_UNSIGNED_INT, nullptr));

}

void KitEngine::Graphics::Renderer::DrawModel(const KitEngine::Graphics::Components::ModelComponent &model,
                                              const KitEngine::Graphics::Shader &shader) {

    model.mVertexArray.Bind();
    for (auto& mesh : model.mMeshes) {
        GLCall(glDrawElementsBaseVertex(GL_TRIANGLES,
                                        mesh.NumIndices,
                                        GL_UNSIGNED_INT,
                                        reinterpret_cast<const void *>(sizeof(unsigned int) *
                                                                       mesh.BaseIndex),
                                        mesh.BaseVertex));
    }
    KitEngine::Graphics::VertexArray::Unbind();

}
