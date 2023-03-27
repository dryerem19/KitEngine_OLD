/**
 * @file Components.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Components
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "pch.h"
#include "Types.h"
#include "BaseCamera.h"
#include "Model.h"
#include "TransformComponent.h"

struct RelationshipComponent
{
    entt::entity mParent { entt::null };
    std::vector<entt::entity> mChildren;

    RelationshipComponent() = default;
    RelationshipComponent(const RelationshipComponent&) = default;
    RelationshipComponent(const std::vector<entt::entity>& children, entt::entity parent = entt::null)
        : mChildren(children), mParent(parent) { }
};

struct TagComponent
{
    std::string mTag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag)
        : mTag(tag) { }
};

struct ModelComponent
{
    std::shared_ptr<Model> mModel;

    ModelComponent() = default;
    ModelComponent(std::shared_ptr<Model> model)
        : mModel(model) { }
};

enum class LightType
{
    Directional,
    Point
};

struct LightComponent
{
    LightType mType;
    glm::vec3 mDirection { 1.0f, 1.0f, 1.0f };
    glm::vec3 mAmbient   { 1.0f, 1.0f, 1.0f };
    glm::vec3 mDiffuse   { 1.0f, 1.0f, 1.0f };
    glm::vec3 mSpecular  { 1.0f, 1.0f, 1.0f }; 
    float mRange { 1.0f };

    LightComponent()
        : mType(LightType::Directional) { }
    LightComponent(LightType type)
        : mType(type) { }

    void SendToShader(const std::shared_ptr<Shader>& shader, const glm::vec3& position) const
    {
        if (!shader) {
            return;
        }

        if (mType == LightType::Directional) {
            shader->SetVec("u_directionalLight.direction", mDirection);
            shader->SetVec("u_directionalLight.ambient", mAmbient);
            shader->SetVec("u_directionalLight.diffuse", mDiffuse);
            shader->SetVec("u_directionalLight.specular", mSpecular);
            shader->SetFloat("u_directionalLight.range", mRange);
        }
    }
};

struct RigidbodyComponent
{
    std::unique_ptr<btRigidBody> mRigidBody;

    // If mass set as zero, rigidbody - static 
    btScalar mMass = 0.0f;

    RigidbodyComponent() = default;
    RigidbodyComponent(const RigidbodyComponent&) = default;
};

struct BoxColliderComponent
{
    glm::vec3 mCenter { 0.0f, 0.0f, 0.0f };
    glm::vec3 mSize { 0.0f, 0.0f, 0.0f };

    BoxColliderComponent() = default;
    BoxColliderComponent(const glm::vec3& size)
        : mSize(size) { }
    BoxColliderComponent(const BoxColliderComponent&) = default;
};

struct ScriptComponent
{
    // Текст Lua скрипта
    std::string script;

    // Объект Lua, созданный из скрипта
    luabridge::LuaRef object;
};


struct CameraComponent
{
    float mFov              = 45;      // Угол обзора в градусах
    int   mViewportX        = 0;       // Позиция левого верхнего угла вьюпорта по оси X
    int   mViewportY        = 0;       // Позиция левого верхнего угла вьюпорта по оси Y
    float mViewportWidth    = 1280;    // Ширина вьюпорта
    float mViewportHeight   = 720;     // Высота вьюпорта
    float mNearPlane        = 0.1f;    // Ближняя плоскость отсечения
    float mFarPlane         = 1000.0f; // Дальняя плоскость отсечения
    float mYaw              = -90.0f;  // Отвечает за поворот камеры вокруг вертикальной оси
    float mPitch            = 0.0f;    // Отвечает за поворот камеры вокруг горизонтальной оси

    glm::mat4 mViewMatrix     = glm::mat4(1.0f); // Матрица вида
    glm::mat4 mProjMatrix     = glm::mat4(1.0f); // Матрица проекции
    glm::mat4 mViewProjMatrix = glm::mat4(1.0f); // Матрица вида-проекции

    glm::vec3 getUp() const
    {
        return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 getRight() const
    {
        return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::vec3 getForward() const
    {
        return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::quat getOrientation() const
    {
        return glm::quat(glm::vec3(-mPitch, -mYaw, 0.0f));
    }
};



struct PlayerComponent
{
    float mMovementSpeed        = 2.5f;   // Скорость передвижения игрока
    float mMouseSensitivity     = 0.3f;   // Чувствительность мыши
};