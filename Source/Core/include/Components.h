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


/**
 * @brief Представляет компонент
 * камеры от первого лица (FPS Camera)
 */
struct CameraComponent 
{

    BaseCamera* pCamera = nullptr;

    // float mFov          = 0.785398;              // Угол обзора
    // float mAspect       = 1.778f;                // Соотношение сторон
    // float mNear         = 0.1f;                  // Ближняя плоскость отсечения
    // float mFar          = 1000.0f;               // Дальняя плоскость отсечения
    // float mYaw          = -90.0f;                // Угол поворота вокруг оси Y
    // float mPitch        = 0.0f;                  // Угол поворота вокруг оси X
    // glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };  // Позиция камеры

    // /**
    //  * @brief Возвращает матрицу вида
    //  * @return glm::mat4
    //  */
    // glm::mat4 getView() const
    // {
    //     glm::quat orientation = getOrientation();
    //     glm::mat4 view = glm::translate(glm::mat4(1.0f), mPosition) * glm::toMat4(orientation);
    //     return glm::inverse(view);
    // };

    // /**
    //  * @brief Возвращает матрицу перспективной проекции
    //  * @return glm::mat4
    //  */
    // glm::mat4 getProjection() const
    // {
    //     return glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
    // }

    // /**
    //  * @brief Возвращает матрицу вида-проекции
    //  * 
    //  * @return glm::mat4
    //  */
    // glm::mat4 getViewProjection() const 
    // {
    //     return getView() * getProjection();
    // }

    // /**
    //  * @brief Возвращает вектор, направленный вверх, относительно ориентации объекта.
    //  * @return glm::vec3
    //  */
    // glm::vec3 getUp() const
    // {
    //     return glm::normalize(glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f)));
    // }

    // /**
    //  * @brief Возвращает вектор, направленный вправо, относительно ориентации объекта.
    //  * @return glm::vec3
    //  */
    // glm::vec3 getRight() const
    // {
    //     return glm::normalize(glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f)));
    // }

    // /**
    //  * @brief Возвращает вектор, направленный вперед, относительно ориентации объекта.
    //  * @return glm::vec3
    //  */
    // glm::vec3 getForward() const
    // {
    //     return glm::normalize(glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f)));
    // }

    // /**
    //  * @brief Возвращает кватернион, представляющий ориентацию объекта.
    //  * @return glm::vec3
    //  */
    // glm::quat getOrientation() const
    // {
    //     // Отрицательные углы поворота означают вращение против часовой стрелки
    //     return glm::quat(glm::vec3(-mPitch, -mYaw, 0.0f));
    // }
};

struct PlayerComponent
{
    float mMovementSpeed        = 2.5f;   // Скорость передвижения игрока.
    float mMouseSensitivity     = 0.7f;   // Чувствительность мыши.
};