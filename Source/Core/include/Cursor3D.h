/**
 * @file Cursor3D.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Input.h"
#include "BaseCamera.h"
#include "Application.h"

class Cursor3D
{
public:

    /**
     * @brief Возвращает точку клика в 3-x мерном пространстве мира
     * Метод основан на https://antongerdelan.net/opengl/raycasting.html
     * @param camera Камера игрока
     * @return glm::vec3 Точка в пространстве
     */
    glm::vec3 GetPickPoint(const Core::BaseCamera& camera);
};