/**
 * @file KitMesh.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 3D Geometry mesh
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once

struct KitMesh final
{
    std::vector<glm::vec3> mVertices;
    std::vector<glm::vec3> mNormals;
    std::vector<glm::vec2> mUvs;
    std::vector<uint32_t> mIndices;
};