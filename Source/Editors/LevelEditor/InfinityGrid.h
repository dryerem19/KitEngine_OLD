#pragma once
#include <Renderer.h>

namespace LevelEditor
{
    class InfinityGrid
    {
    private:
        Render::VertexArray  mVertexArray;
        Render::VertexBuffer mVertexBuffer;
        Render::IndexBuffer  mIndexBuffer;
        Render::Shader       mShader;
    public:
        InfinityGrid()
            : mShader("../../Resources/shaders/glsl/infinity_grid.glsl") { }

        void Init()
        {
            // Grid position are in xy clipped space
            std::vector<glm::vec3> gridPlane = {
                glm::vec3(-1.0f, -1.0f, 0.0f), 
                glm::vec3(1.0f, -1.0f, 0.0f),  
                glm::vec3(1.0f, 1.0f, 0.0f),
                glm::vec3(-1.0f, 1.0f, 0.0f)
            };
            mVertexBuffer.Init(gridPlane.data(), gridPlane.size() * sizeof(gridPlane[0]));

            Render::VertexBufferLayout bufferLayout;
            bufferLayout.AddFloatElement(3);
            mVertexArray.AddBuffer(mVertexBuffer, bufferLayout);

            std::vector<uint32_t> indices = {
                0, 1, 2,
                0, 2, 3
            };

            mIndexBuffer.Init(indices.data(), indices.size());
        }   

        void Draw(float* view, float* proj)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);   
            {
                mShader.Enable();
                mShader.SetUniformMatrix4fv("uView", 1, GL_FALSE, view);
                mShader.SetUniformMatrix4fv("uProj", 1, GL_FALSE, proj);
                Render::Renderer::Draw(mVertexArray, mIndexBuffer); 
                mShader.Disable();
            }
            glDisable(GL_BLEND);
        }     
    };
}