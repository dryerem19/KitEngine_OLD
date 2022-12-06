/**
 * @file KitMaterial.h
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
#include "Interfaces/ISerialization.h"
#include "Interfaces/IDeserialization.h"

class KitMaterialFile final : private ISerialization, private IDeserialization
{
public:
    /* Название материала */
    std::string name;

    /* Путь к материалу на диске, используется при десериализации */
    std::string filepath;

    /* Путь к основной diffuse текстуре */
    std::string diffuse_texture_path;

    KitMaterialFile() = default;

    /**
     * @brief Создаёт новый экземпляр файла материала
     * 
     * @param name название материала
     * @param diffuse_texture_path путь к текстуре на диске
     */
    KitMaterialFile(const std::string& name, const std::string& diffuse_texture_path)
    {
        assert(!name.empty() && "name should not be empty!");
        assert(!diffuse_texture_path.empty() && "diffuse_texture_path should not be empty!");

        this->name = name;
        this->diffuse_texture_path = diffuse_texture_path;
    }

    /**
     * @brief Создаёт новый экземпляр файла материала
     * 
     * @param name название материала
     * @param diffuse_texture_path путь к текстуре на диске
     */
    KitMaterialFile(const std::string& name, const char* diffuse_texture_path)
    {
        assert(!name.empty() && "name should not be empty!");
        assert(diffuse_texture_path && "diffuse_texture_path should not be empty!");

        this->name = name;
        this->diffuse_texture_path = diffuse_texture_path;
    }

    /**
     * @brief Запись данных материала в файл
     * 
     * @param filepath путь к файлу
     */
    void Serialize(const std::string& filepath) override final;

    /**
     * @brief Чтение данных материала из файла
     * 
     * @param filepath путь к файлу
     */
    void Deserialize(const std::string& filepath) override final;
};