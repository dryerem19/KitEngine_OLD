//
// Created by piokxix on 04.11.22.
//

#ifndef LEVELEDITOR_BASECAMERA_H
#define LEVELEDITOR_BASECAMERA_H

namespace Core
{
    class BaseCamera
    {
    private:
        float mFovy;
        float mAspect;
        float mZNear;
        float mZFar;

    public:
        BaseCamera() = default;
        ~BaseCamera() = default;

        void SetPerspective(float fovy, float aspect, float zNear, float zFar);
        void SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
        const float* GetView() const;
        const glm::mat4& GetGlmView() const { return mView;}
        const float* GetPerspective() const;
        glm::vec3 GetPos() const { return cameraPos; };
        glm::vec3 GetFront() const { return cameraFront; };
        glm::vec3 GetUp() const { return cameraUp; };
        
        /**
         * @brief Преобразует точку из экранного пространства в мировое
         * 
         * @param position Координаты мыши в пикселях
         * @param screen Размеры экранной области в пикселях
         * @param outOrigin Начало луча
         * * Начинается с ближней плоскости, поэтому если вы хотите, чтобы луч начинался с положения камеры, игнорируйте этот параметр
         * @param outDirection Направление луча в мировом пространсве, который проходит через мышь
         */
        void ScreenToWorldPoint(const glm::vec2& position, const glm::vec2& screen, glm::vec3& outOrigin, glm::vec3& outDirection);

        float& GetZNear();

        void UpdateAspect(const float& aspect);
        const glm::mat4& GetProj() const { return mProjection; }

    protected:
        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        glm::mat4 mTransform = glm::mat4(1.0f);
        glm::mat4 mView = glm::mat4(1.0f);
        glm::mat4 mProjection = glm::mat4(1.0f);
    };
}




#endif //LEVELEDITOR_BASECAMERA_H
