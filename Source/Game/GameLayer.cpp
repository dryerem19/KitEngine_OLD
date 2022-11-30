#include "GameLayer.h"

void GameLayer::OnStart()
{
    Core::MeshVisualImporter importer;
    importer.LoadVisual("../../Resources/models/nanosuit/nanosuit.obj");
    pRootEntity = importer.GetRootEntity();
}

void GameLayer::OnUpdate()
{

}

void GameLayer::OnRender(double dt)
{
    Render::Renderer::Clear();
    // if (pRootEntity)
    // {
    //     pRootEntity->DrawMesh();
    // }
}