/**
 * @file KitModelFile.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include "Interfaces/ISerialization.h"
#include "Interfaces/IDeserialization.h"
#include "KitVertex.h"

struct KMFMesh final
{
    /* Имя сетки*/
    std::string name;

    /* Путь к материалу сетки */
    std::string material;

    /* Данные индексов сетки */
    std::vector<uint32_t> indices;

    /* Данные вершин сетки */
    std::vector<Render::KitVertex> vertices;
};

class KitModelFile final : private ISerialization, private IDeserialization
{
public:
    const uint8_t version = 1;
    std::string name;
    std::vector<std::unique_ptr<KMFMesh>> meshes;
    std::string filepath;
    
    /**
     * @brief Сохранение модели в .kmf файл
     * 
     * @param filepath путь к .kmf файлу на диске
     */
    void Serialize(const std::string& filepath) override final;

    /**
     * @brief Чтение модели из .kmf файла
     * 
     * @param filepath путь к файлу на диске
     */
    void Deserialize(const std::string& filepath) override final;

    /**
     * @brief Проверяет корректно ли был считан файл
     * * Значение по умолчнию всегда true, если вы создаёте новый экземпляр
     * 
     * @return true Если файл считан корректно
     * @return false Если в процессе чтения произошли ошибки
     */
    inline bool IsValid() const { return valid; }

private:
    bool valid = true;
};
