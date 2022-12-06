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
 * @brief Интерфейс класса сериализации
 * 
 */
class ISerialization
{
public:
    virtual ~ISerialization() = default;

    /**
     * @brief Сериализовать класс в файл
     * 
     * @param filepath путь, куда сериализовать
     */
    virtual void Serialize(const std::string& filepath) = 0;
};