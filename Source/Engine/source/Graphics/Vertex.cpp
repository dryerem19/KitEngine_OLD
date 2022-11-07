//
// Created by dryerem19 on 10/31/22.
//
#include "Graphics/Vertex.h"

KitEngine::Graphics::VertexBufferLayout KitEngine::Graphics::Vertex::mLayout = []() constexpr {

   VertexBufferLayout mLayout;
   mLayout.AddFloatElement(3);
   mLayout.AddFloatElement(3);
    mLayout.AddFloatElement(2);
   return mLayout;

}();

KitEngine::Graphics::Vertex::Vertex(const glm::vec3 &position)
        : mPosition(position) {

}

KitEngine::Graphics::Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &texcoord)
        : mPosition(position), mTexcoord(texcoord) {

}

KitEngine::Graphics::Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &texcoord, const glm::vec3 &normal)
    :  mPosition(position), mTexcoord(texcoord), mNormal(normal) {

}

bool KitEngine::Graphics::Vertex::operator==(const KitEngine::Graphics::Vertex &other) const {

    return this->mPosition == other.mPosition
        && this->mTexcoord == other.mTexcoord
        && this->mNormal   == other.mNormal;

}

bool KitEngine::Graphics::Vertex::operator!=(const KitEngine::Graphics::Vertex &other) const {

    return this->mPosition != other.mPosition
        && this->mTexcoord != other.mTexcoord
        && this->mNormal   != other.mNormal;

}
