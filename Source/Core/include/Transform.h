/**
 * @file Transform.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Object transformation
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
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
    glm::vec3 mPivotPosition = { 0.0f, 0.0f, 0.0f };

    /* Мировая матрица объекта */
    glm::mat4 mModelMatrix = glm::mat4(1.0f);

    glm::mat4 mPivotMatrix = glm::mat4(1.0f);

    /* Грязный флаг */
    bool mDirty = true;

    btRigidBody* m_pRigidBody;

public:
    Transform();
    Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s)
        : mTranslation(p), mRotation(r), mScale(s) { }

    void SetPosition(const glm::vec3& p);
    void SetPosition(const float& x, const float& y, const float& z);
    void SetRotation(const glm::vec3& r);
    void SetRotation(const float& x, const float& y, const float& z);
    void SetScale(const glm::vec3& s);
    void SetScale(const float& x, const float& y, const float& z);

    void SetTransform(const glm::mat4& transform); 

    inline void SetPivotPosition(const glm::vec3& position) { mPivotPosition = position; }
    inline const glm::vec3& GetPivotPosition() const { return mPivotPosition; }
    void SetRigidBody(btRigidBody* pRigidBody);

    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;
    const glm::mat4& GetModelMatrix();
    inline glm::mat4 GetPivotMatrix() { return mPivotMatrix; }

    std::string DebugString() const;

    bool IsDirty() const;
    //void UpdateRigidBody();
    //void UpdateRigidBodyScale();
private:
    //void UpdatePivot();
};