//
// Created by dryerem19 on 10/31/22.
//

#ifndef LEVELEDITOR_VERTEX_H
#define LEVELEDITOR_VERTEX_H
#include "VertexBufferLayout.h"

namespace Render
{
    struct KitVertex {
        glm::vec3 mPosition { };
        glm::vec3 mNormal   { };
        glm::vec2 mTexcoord { };

        explicit KitVertex(const glm::vec3& position);
        explicit KitVertex(const glm::vec3& position, const glm::vec3& normal);
        explicit KitVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texcoord);

        bool operator==(const KitVertex& other) const;
        bool operator!=(const KitVertex& other) const;

        KitVertex() = default;
        KitVertex(const KitVertex&) = default;
    };
}

#endif //LEVELEDITOR_VERTEX_H
