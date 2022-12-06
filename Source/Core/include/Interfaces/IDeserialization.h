/**
 * @file ISerialization.h
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

/**
 * @brief Интерфейс десериалазации в файл
 * 
 */
class IDeserialization
{
public:
    virtual ~IDeserialization() = default;

    /**
     * @brief Десериализация данных из файла в класс
     * 
     * @param filepath путь к файлу
     */
    virtual void Deserialize(const std::string& filepath) = 0;
};