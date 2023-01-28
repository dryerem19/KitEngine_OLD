/**
 * @file AABB.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Axis aligned bounding box
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include <glm/glm.hpp>

namespace KitEngine
{
    struct AABB
    {
        glm::vec3 max;
        glm::vec3 min;

        bool TestIntersection(const glm::vec3& point)
        {
            return (point.x >= min.x && point.x <= max.x) &&
                    (point.y >= min.y && point.y <= max.y) &&
                    (point.z >= min.z && point.z <= max.z);
        }
    };
}