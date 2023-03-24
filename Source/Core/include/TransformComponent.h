/**
 * @file TransformComponent.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Transform interface
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once

class TransformComponent
{
public:
    glm::vec3 mPosition      = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mRotation      = { 0.0f, 0.0f, 0.0f }; // Поворот в градусах
    glm::vec3 mScale         = { 1.0f, 1.0f, 1.0f };
private:
    glm::mat4 mMatrix        = glm::mat4(1.0f);
    bool mChangedMarker = true;
    std::string mDebugInfo;
public:
    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& position);
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation);
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    void SetPosition(const glm::vec3& position);
    inline const glm::vec3& GetPosition() const { return mPosition; }

    void SetRotation(const glm::vec3& rotation);
    inline const glm::vec3& GetRotation() const { return mRotation; }

    void SetScale(const glm::vec3& scale);
    inline const glm::vec3& GetScale() const { return mScale; }

    void SetPivot(const glm::vec3& pivot);

    void SetMatrix(const glm::mat4& matrix);
    glm::mat4 GetMatrix();

    inline bool IsDirty() const { return mChangedMarker; }
    const std::string& GetDebugInfo();
};