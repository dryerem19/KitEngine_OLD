//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_BASELAYER_H
#define KITENGINE_BASELAYER_H

#include "KitEnginePch.h"

namespace KitEngine::Core
{
    struct BaseLayer
    {
    public:
        BaseLayer(const std::string name = "BaseLayer");
        virtual ~BaseLayer() = default;

        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnFrameRender(double dt);
        virtual void OnUIRender();
        virtual void OnFinish();

        inline const std::string& GetName() const { return mName; }

    protected:
        std::string mName;
    };
}

#endif //KITENGINE_BASELAYER_H
