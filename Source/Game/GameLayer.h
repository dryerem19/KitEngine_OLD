#pragma once
#include "BaseLayer.h"
#include "GameLevel.h"
#include "RenderSystem.h"
#include "Events/FrameBufferResizeEvent.h"
#include "Application.h"

#include "FPSCamera.h"

class GameLayer final : public Core::BaseLayer
{
private:
    FPSCamera camera;
public:
    GameLayer() = default;
    void OnStart() override final;
    void OnUpdate() override final;
    void EventHandler(const Core::Event& event) override final;
    void OnRender(double dt) override final;
    void OnUIRender() override final {};
    void OnFinish() override final {};
};