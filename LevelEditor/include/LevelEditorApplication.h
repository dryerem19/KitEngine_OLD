//
// Created by dryerem19 on 10/28/22.
//

#ifndef LEVELEDITOR_LEVELEDITORAPPLICATION_H
#define LEVELEDITOR_LEVELEDITORAPPLICATION_H

#include <Core/Application.h>

namespace LevelEditor
{
    class LevelEditorApplication : public KitEngine::Core::Application
    {
    private:
        void OnStart() override;
        void OnUpdate() override;
        void OnRender(double dt) override;
    };
}

#endif //LEVELEDITOR_LEVELEDITORAPPLICATION_H
