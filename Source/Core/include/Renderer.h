//
// Created by dryerem19 on 08.11.22.
//

#ifndef KITENGINE_RENDERER_H
#define KITENGINE_RENDERER_H

#include "Shader.h"
#include "KitVertex.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "FrameBuffer.h"
#include "KitStaticMesh.h"

namespace Render
{
    enum class WireframeMode{
        Vertices    = GL_POINT,
        Edge        = GL_LINE,
        Polygon     = GL_FILL
    };
    class Renderer
    {
    private:
    public:
        static void Initialize()
        {
            glEnable(GL_DEPTH_TEST);

            if (glewInit() != GLEW_OK) 
            {

            }

            int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
            {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
                glDebugMessageCallback(OnDebugOutput, nullptr);  
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);         
            }            
        }

        static void OnDebugOutput(GLenum source, GLenum type, unsigned int id, 
            GLenum severity, GLsizei length, const char *message, const void *userParam)
        {
            // ignore non-significant error/warning codes
            if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

            std::cout << "---------------" << std::endl;
            std::cout << "Debug message (" << id << "): " <<  message << std::endl;

            switch (source)
            {
                case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
                case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
                case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
            } std::cout << std::endl;

            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
                case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
                case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
                case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
                case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
                case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
                case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
            } std::cout << std::endl;
            
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
                case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
                case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
            } std::cout << std::endl;
            std::cout << std::endl;    
        }       

        static void DrawIndexed(uint32_t count, uint32_t baseIndex, uint32_t baseVertex)
        {
            glDrawElementsBaseVertex(
                    GL_TRIANGLES,
                    count,
                    GL_UNSIGNED_INT,
                    reinterpret_cast<const void*>(sizeof(uint32_t) * baseIndex),
                    baseVertex);
        }

        static void Draw(const VertexArray& varray, const IndexBuffer& ibuffer)
        {
            GLCall(glBindVertexArray(0));

            varray.Bind();
            ibuffer.Bind();
            GLCall(glDrawElements(GL_TRIANGLES, ibuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
            varray.Unbind();
            ibuffer.Unbind();
        }

        static void Clear()
        {
            float color = 85.0f/255.0f;
            glClearColor(color, color, color, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        static void Wireframe(WireframeMode mode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
        }
    };
}

#endif //KITENGINE_RENDERER_H
