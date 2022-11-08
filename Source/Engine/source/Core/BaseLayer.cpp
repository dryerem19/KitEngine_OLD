//
// Created by Denis on 01.11.2022.
//
#include "Core/BaseLayer.h"

#include "Core/Logger.h"

KitEngine::Core::BaseLayer::BaseLayer(std::string name)
    : mName(std::move(name)) {

}

void KitEngine::Core::BaseLayer::OnStart() {

    Log::Info("Layer - {} has been started", mName);

}

void KitEngine::Core::BaseLayer::OnUpdate() {

}

void KitEngine::Core::BaseLayer::OnRender(double dt) {

}

void KitEngine::Core::BaseLayer::OnUIRender() {

}

void KitEngine::Core::BaseLayer::OnFinish() {

    Log::Info("Layer - {} finish", mName);

}

