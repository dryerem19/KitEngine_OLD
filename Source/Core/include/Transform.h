/**
 * @file Transform.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class Transform
{
private:

    /* Локальная информация о трансформации */
    glm::vec3 mTranslation   = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mRotation      = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale         = { 1.0f, 1.0f, 1.0f };

    /* Мировая матрица объекта */
    glm::mat4 mModelMatrix = glm::mat4(1.0f);

    /* Грязный флаг */
    bool mDirty = true;

public:
    Transform() = default;
    Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s)
        : mTranslation(p), mRotation(r), mScale(s) { }

    void SetPosition(const glm::vec3& p);
    void SetPosition(const float& x, const float& y, const float& z);
    void SetRotation(const glm::vec3& r);
    void SetRotation(const float& x, const float& y, const float& z);
    void SetScale(const glm::vec3& s);
    void SetScale(const float& x, const float& y, const float& z);
    void SetModelMatrix(const float* matrix);

    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;
    const float* GetModelMatrix();

    bool IsDirty() const;
};