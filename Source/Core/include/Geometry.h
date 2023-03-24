/**
 * @file Geometry.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct Geometry
{
    VertexArray  vao;
    VertexBuffer vbo;
    IndexBuffer  ibo;

    Geometry() = default;
    ~Geometry() = default;
};