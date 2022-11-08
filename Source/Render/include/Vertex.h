//
// Created by dryerem19 on 10/31/22.
//

#ifndef LEVELEDITOR_VERTEX_H
#define LEVELEDITOR_VERTEX_H
#include "VertexBufferLayout.h"

namespace Render
{
    struct Vertex {
        glm::vec3 mPosition { };
        glm::vec2 mTexcoord { };
        glm::vec3 mNormal   { };

        static VertexBufferLayout mLayout;

        explicit Vertex(const glm::vec3& position);
        explicit Vertex(const glm::vec3& position, const glm::vec2& texcoord);
        explicit Vertex(const glm::vec3& position, const glm::vec2& texcoord, const glm::vec3& normal);

        bool operator==(const Vertex& other) const;
        bool operator!=(const Vertex& other) const;

        Vertex() = default;
        Vertex(const Vertex&) = default;
    };
}

#endif //LEVELEDITOR_VERTEX_H
