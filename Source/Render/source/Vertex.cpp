//
// Created by dryerem19 on 10/31/22.
//
#include "../pch/RenderPch.h"
#include "Vertex.h"

Render::VertexBufferLayout Render::Vertex::mLayout = []() constexpr {

   VertexBufferLayout mLayout;
   mLayout.AddFloatElement(3);
   mLayout.AddFloatElement(3);
   mLayout.AddFloatElement(2);
   return mLayout;

}();

Render::Vertex::Vertex(const glm::vec3 &position)
        : mPosition(position) {

}

Render::Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &texcoord)
        : mPosition(position), mTexcoord(texcoord) {

}

Render::Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &texcoord, const glm::vec3 &normal)
    :  mPosition(position), mTexcoord(texcoord), mNormal(normal) {

}

bool Render::Vertex::operator==(const Render::Vertex &other) const {

    return this->mPosition == other.mPosition
        && this->mTexcoord == other.mTexcoord
        && this->mNormal   == other.mNormal;

}

bool Render::Vertex::operator!=(const Render::Vertex &other) const {

    return this->mPosition != other.mPosition
        && this->mTexcoord != other.mTexcoord
        && this->mNormal   != other.mNormal;

}
