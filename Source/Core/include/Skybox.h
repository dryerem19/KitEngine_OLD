/**
 * @file Skybox.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Texture.h"
#include "Geometry.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "BaseCamera.h"
#include "RenderBackend.h"
#include "Interfaces/ISerialization.h"
#include "Interfaces/IDeserialization.h"

static const float mSkyboxVertices[] =
{
    //   Coordinates
    -1.0f, -1.0f,  1.0f,   //        7--------6
    1.0f, -1.0f,  1.0f,    //       /|       /|
    1.0f, -1.0f, -1.0f,    //      4--------5 |
    -1.0f, -1.0f, -1.0f,   //      | |      | |
    -1.0f,  1.0f,  1.0f,   //      | 3------|-2
    1.0f,  1.0f,  1.0f,    //      |/       |/
    1.0f,  1.0f, -1.0f,    //      0--------1
    -1.0f,  1.0f, -1.0f
};

static const unsigned int mSkyboxIndices[] =
{
    // Right
    1, 2, 6,
    6, 5, 1,
    // Left
    0, 4, 7,
    7, 3, 0,
    // Top
    4, 5, 6,
    6, 7, 4,
    // Bottom
    0, 3, 2,
    2, 1, 0,
    // Back
    0, 1, 5,
    5, 4, 0,
    // Front
    3, 7, 6,
    6, 2, 3
};


class SkyBox : public ISerialization, IDeserialization
{
private:
    Geometry geometry;
    Render::Texture mSkyBox;
    std::shared_ptr<Render::Shader> mShader;
public:
    SkyBox();
    void Serialize(const std::string& filepath) override final;
    void Deserialize(const std::string& filepath) override final;
    void Render(const Core::BaseCamera& camera);
};