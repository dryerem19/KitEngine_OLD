//
// Created by dryerem19 on 10/31/22.
//
#include "pch.h"
#include "KitVertex.h"

Render::KitVertex::KitVertex(const glm::vec3 &position)
        : mPosition(position) {

}

Render::KitVertex::KitVertex(const glm::vec3 &position, const glm::vec3 &normal)
        : mPosition(position), mNormal(normal) {

}

Render::KitVertex::KitVertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texcoord)
    :  mPosition(position), mTexcoord(texcoord), mNormal(normal) {

}

bool Render::KitVertex::operator==(const Render::KitVertex &other) const {

    return this->mPosition == other.mPosition
        && this->mTexcoord == other.mTexcoord
        && this->mNormal   == other.mNormal;

}

bool Render::KitVertex::operator!=(const Render::KitVertex &other) const {

    return this->mPosition != other.mPosition
        && this->mTexcoord != other.mTexcoord
        && this->mNormal   != other.mNormal;

}
