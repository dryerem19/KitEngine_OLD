/**
 * @file Skybox.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Skybox.h"

SkyBox::SkyBox()
{
    geometry.vbo.Init(mSkyboxVertices, sizeof(mSkyboxVertices));

    Render::VertexBufferLayout vertexLayout;
    vertexLayout.AddFloatElement(3);

    geometry.vao.AddBuffer(geometry.vbo, vertexLayout);

    geometry.ibo.Init(mSkyboxIndices, sizeof(mSkyboxIndices));
}

void SkyBox::Serialize(const std::string& filepath)
{

}

void SkyBox::Deserialize(const std::string& filepath)
{
    YAML::Node skybox = YAML::LoadFile(filepath);

    std::string texturesPath[6] =
    {
        skybox["tex1"].as<std::string>(),
        skybox["tex2"].as<std::string>(),
        skybox["tex3"].as<std::string>(),
        skybox["tex4"].as<std::string>(),
        skybox["tex5"].as<std::string>(),
        skybox["tex6"].as<std::string>()
    };
    mShader = Core::ResourceManager::Instance().GetShader(skybox["shader"].as<std::string>());
    
    mSkyBox.InitCubeMap(texturesPath);
}

void SkyBox::Render(const Core::BaseCamera& camera)
{
    if(!mShader)
    {
        return;
    }
    glDepthFunc(GL_LEQUAL);
    auto& backend = RenderBackend::Get();
    backend.SetGeometry(&geometry);
    mShader->Enable();
    mShader->SetUniformMatrix4fv("uView", 1, GL_FALSE, camera.GetView());
    mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, camera.GetPerspective());

    mSkyBox.Enable();
    backend.Render();
    glDepthFunc(GL_LESS);
}