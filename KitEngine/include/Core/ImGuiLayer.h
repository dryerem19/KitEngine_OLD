//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_IMGUILAYER_H
#define KITENGINE_IMGUILAYER_H

#include "BaseLayer.h"

namespace KitEngine::Core
{
    class ImGuiLayer : public BaseLayer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnStart() override;
        void OnFinish() override;

        void BeginFrame();
        void EndFrame();
    };
}

#endif //KITENGINE_IMGUILAYER_H
