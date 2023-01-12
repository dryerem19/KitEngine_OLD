//
// Created by piokxix on 04.11.22.
//

#ifndef LEVELEDITOR_BASECAMERA_H
#define LEVELEDITOR_BASECAMERA_H

namespace Core
{
    class BaseCamera
    {
    public:
        BaseCamera();
        BaseCamera(const float& fov, const float& aspect, const float& near, const float& far);        
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

        virtual void OnUpdate();
        inline const glm::mat4& GetProjection() const { return mProjection; }
        inline const glm::mat4& GetViewProjection() const { return mViewProjection; }
        inline const glm::mat4& GetView() const { return mView; }
        inline float GetYaw() const { return mYaw; }
        inline float GetPitch() const { return mPitch; }
        inline float GetFov() const { return mFov; }
        inline float GetAspect() const { return mAspect; }
        inline float GetNear() const { return mNearClip; }
        inline float GetFar() const { return mFarClip; }
        inline void SetViewportSize(const float& width, const float& height) { mViewportWidth = width; mViewportHeight = height; UpdateProjection(); }
        glm::vec3 GetUp() const;
        glm::vec3 GetRight() const;
        glm::vec3 GetForward() const;
        inline const glm::vec3& GetPosition() const { return mPosition; } 
        glm::quat GetOrientation() const;
    private:
        void SetProjection(const float& fov, const float& aspect, const float& near, const float& far);
        void UpdateProjection();
        void UpdateView();
    protected:
        glm::vec3 mPosition;
        glm::mat4 mProjection;
        glm::mat4 mViewProjection;
        glm::mat4 mView;

        float mYaw;
        float mPitch;
        float mFov;
        float mAspect;
        float mNearClip;
        float mFarClip;    
        float mViewportWidth;
        float mViewportHeight;    
    };
}




#endif //LEVELEDITOR_BASECAMERA_H
