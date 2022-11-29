//
// Created by Denis on 01.11.2022.
//
#include "pch.h"
#include "BaseLayer.h"

Core::BaseLayer::BaseLayer(std::string name)
    : mName(std::move(name)) {

}

void Core::BaseLayer::OnStart() {

    Log::Info("Layer - {} has been started", mName);

}

void Core::BaseLayer::OnUpdate() {

}

void Core::BaseLayer::OnBegin() {

}

void Core::BaseLayer::EventHandler(const Event& event)
{
    
}

void Core::BaseLayer::OnEnd() {

}


void Core::BaseLayer::OnRender(double dt) {

}

void Core::BaseLayer::OnUIRender() {

}

void Core::BaseLayer::OnFinish() {

    Log::Info("Layer - {} finish", mName);

}

