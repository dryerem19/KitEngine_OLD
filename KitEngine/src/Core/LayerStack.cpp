//
// Created by Denis on 01.11.2022.
//
#include "Core/LayerStack.h"

KitEngine::Core::LayerStack::~LayerStack() {

    for (auto& layer : mLayers) {
        layer->OnFinish();
    }

}

void KitEngine::Core::LayerStack::PushLayer(const std::unique_ptr<BaseLayer> layer) {

    mLayers.emplace_back(layer);
    layer->OnStart();

}

void KitEngine::Core::LayerStack::PopLayer(const std::unique_ptr<BaseLayer> layer) {

    layer->OnFinish();
    mLayers.erase(std::remove(mLayers.begin(), mLayers.end(),
                              layer), mLayers.end());

}


