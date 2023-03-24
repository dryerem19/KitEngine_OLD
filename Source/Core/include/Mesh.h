/**
 * @file Mesh.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include "KitMaterial.h"
#include "KitVertex.h"


#include "Geometry.h"

class Mesh
{
public:
    
    std::string name;

    // Буфер вершин и индексов
    Geometry geometry;
    
    // Материал сетки
    //std::shared_ptr<Render::KitMaterial> mMaterial;
    Render::KitMaterial mMaterial;

    Mesh(const std::vector<KitVertex>& vertices, 
            const std::vector<uint32_t>&  indices);


    Mesh(const void* vertices, const uint32_t size,
        const uint32_t* indices, const uint32_t count);

    /*
    @brief Метод инициализация сетки 
    @param vertices Список вершин сетки
    @param indices Список индексов сетки
    */
    void Init(const std::vector<KitVertex>& vertices, 
            const std::vector<uint32_t>&  indices);
};