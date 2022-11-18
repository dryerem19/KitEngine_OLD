//
// Created by Denis on 01.11.2022.
//
#include "LayerStack.h"

Core::LayerStack::~LayerStack() {

    // Iterate for all layers
    for (auto* pLayer : mLayers) {
        if (pLayer != nullptr) {

            // Run the finish function
            pLayer->OnFinish();

            // Free memory
            delete pLayer;
        }
    }

    if (mOverlayLayer != nullptr) {
        mOverlayLayer->OnFinish();
        delete mOverlayLayer;
    }

}

void Core::LayerStack::Push(Core::BaseLayer *pLayer) {

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

void Core::LayerStack::PushOverlay(Core::BaseLayer *pLayer) {

    if (pLayer != nullptr) {

        if (mOverlayLayer == nullptr) {
            mOverlayLayer = pLayer;
            mOverlayLayer->OnStart();
        } else {
            throw std::runtime_error("Overlay layer exist!");
        }
    }
    else {
        throw std::runtime_error("Null pointer to the layer");
    }

}

void Core::LayerStack::Pop(Core::BaseLayer *pLayer) {

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

void Core::LayerStack::PopOverlay() {

    if (mOverlayLayer != nullptr) {

        mOverlayLayer->OnFinish();
        mOverlayLayer = nullptr;

    }

}



