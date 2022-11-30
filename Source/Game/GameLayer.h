#pragma once
#include "BaseLayer.h"
#include "MeshVisualImporter.h"

class GameLayer : public Core::BaseLayer
{
private:
    Core::BaseEntity* pRootEntity;
public:
    GameLayer() = default;
    void OnStart() override;
    void OnUpdate() override;
    void EventHandler(const Core::Event& event) override = 0;
    void OnRender(double dt) override;
    void OnUIRender() override = 0;
    void OnFinish() override = 0;
};