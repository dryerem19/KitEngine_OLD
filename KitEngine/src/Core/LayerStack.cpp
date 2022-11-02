//
// Created by Denis on 01.11.2022.
//
#include "Core/LayerStack.h"

KitEngine::Core::LayerStack::~LayerStack() {

    // Iterate for all layers
    for (auto* pLayer : mLayers) {
        if (pLayer != nullptr) {

            // Run the finish function
            pLayer->OnFinish();

            // Free memory
            delete pLayer;
        }
    }

}

void KitEngine::Core::LayerStack::Push(KitEngine::Core::BaseLayer *pLayer) {

    if (pLayer != nullptr) {

        // Push layer to the back
        mLayers.emplace_back(pLayer);

        // Run the initialization
        pLayer->OnStart();
    }
    else {
        throw std::runtime_error("Null pointer to the layer");
    }

}

void KitEngine::Core::LayerStack::Pop(KitEngine::Core::BaseLayer *pLayer) {

    if (pLayer != nullptr) {

        // Run the finish function
        pLayer->OnFinish();

        // Remove layer from vector by value
        mLayers.erase(std::remove(mLayers.begin(), mLayers.end(),
                                  pLayer), mLayers.end());
    }
    else {
        throw std::runtime_error("Null pointer to the layer");
    }

}



