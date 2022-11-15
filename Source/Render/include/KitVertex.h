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
        glm::vec2 mTexcoord { };
        glm::vec3 mNormal   { };

        explicit KitVertex(const glm::vec3& position);
        explicit KitVertex(const glm::vec3& position, const glm::vec2& texcoord);
        explicit KitVertex(const glm::vec3& position, const glm::vec2& texcoord, const glm::vec3& normal);

        bool operator==(const KitVertex& other) const;
        bool operator!=(const KitVertex& other) const;

        KitVertex() = default;
        KitVertex(const KitVertex&) = default;
    };
}

#endif //LEVELEDITOR_VERTEX_H
