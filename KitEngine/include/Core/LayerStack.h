//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_LAYERSTACK_H
#define KITENGINE_LAYERSTACK_H

#include "KitEnginePch.h"
#include "BaseLayer.h"

namespace KitEngine::Core
{
    class LayerStack
    {
    private:
        std::vector<std::shared_ptr<BaseLayer>> mLayers;
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(const std::shared_ptr<BaseLayer> layer);
        void PopLayer(const std::shared_ptr<BaseLayer> layer);

        inline std::vector<std::shared_ptr<BaseLayer>>::iterator begin()
        { return mLayers.begin(); }
        inline std::vector<std::shared_ptr<BaseLayer>>::iterator end()
        { return mLayers.end(); }

        [[maybe_unused]] inline std::vector<std::shared_ptr<BaseLayer>>::reverse_iterator rbegin()
        { return mLayers.rbegin(); }
        inline std::vector<std::shared_ptr<BaseLayer>>::reverse_iterator rend()
        { return mLayers.rend(); }

        inline std::vector<std::shared_ptr<BaseLayer>>::const_iterator begin() const
        { return mLayers.begin(); }
        inline std::vector<std::shared_ptr<BaseLayer>>::const_iterator end() const
        { return mLayers.end(); }
        [[nodiscard]] inline std::vector<std::shared_ptr<BaseLayer>>::const_reverse_iterator rbegin() const
        { return mLayers.rbegin(); }
        inline std::vector<std::shared_ptr<BaseLayer>>::const_reverse_iterator rend() const
        { return mLayers.rend(); }

        inline const auto& GetLayers() const { return mLayers; }
    };
}

#endif //KITENGINE_LAYERSTACK_H
