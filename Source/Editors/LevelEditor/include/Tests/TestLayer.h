//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_TESTLAYER_H
#define KITENGINE_TESTLAYER_H

#include <Core/BaseLayer.h>


#include <Renderer.h>


#include <Graphics/Components/ModelComponent.h>

// TODO: УБРАТЬ
#include <memory>
#include <Loader.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include <KitModel.h>

using namespace KitEngine::Core;
using namespace KitEngine::Graphics::Components;

namespace LevelEditor::Tests
{
    class TestLayer : public KitEngine::Core::BaseLayer
    {
    private:
        bool isModelLoaded = false;        
        std::unique_ptr<Render::Shader>       mShader;
        Render::KitModel mNanoModel;
        std::unique_ptr<KitEngine::Graphics::Components::ModelComponent> mModel;

        glm::mat4                                          mTransform;
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        GLfloat yaw   = -90.0f;
        GLfloat pitch =   0.0f;
        GLfloat lastX =  800  / 2.0;
        GLfloat lastY =  600 / 2.0;

        Render::FrameBuffer frameBuffer;

        bool isCheckMouse = true;

    public:
        TestLayer() = default;

        void OnStart() override;
        void OnUpdate() override;
        void OnRender(double dt) override;
        void OnUIRender() override;
        void OnFinish() override;

        void DoMovement();
        void OnLoadModel(std::string filepath);

        // UI Window
        void ShowAbout(bool* close);
        void Docking();
        void Viewport();

    };
}

#endif //KITENGINE_TESTLAYER_H
