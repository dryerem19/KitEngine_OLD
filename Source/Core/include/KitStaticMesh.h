/**
 * @file KitStaticMesh.h
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
#include "KitModelFile.h"
#include "KitMaterial.h"
#include "KitVertex.h"

#include "Geometry.h"

namespace Render
{
    class KitStaticMesh
    {
    public:
        

        // Буфер вершин и индексов
        Geometry geometry;
        
        // Материал сетки
        std::shared_ptr<KitMaterial> mMaterial;

        KitStaticMesh(const KMFMesh& mesh);

        KitStaticMesh(const std::vector<KitVertex>& vertices, 
                const std::vector<uint32_t>&  indices);

        /*
        @brief Метод инициализация сетки 
        @param vertices Список вершин сетки
        @param indices Список индексов сетки
        */
        void Init(const std::vector<KitVertex>& vertices, 
                const std::vector<uint32_t>&  indices);

        void Draw();

        inline void SetMaterial(std::shared_ptr<KitMaterial> material)
        {
            //assert(pMaterial && "Material can't be nullptr!");

            mMaterial = material;
        }
    };
}