/**
 * @file KitModelFile.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * 
 */
#pragma once
#include <cstdint>


#define KMF_VERSION 1

struct KMFHeader
{
    uint8_t version;
};

struct KMFDescription
{
    std::string filepath;
    std::string name;
};

struct KitModelFile
{
    KMFHeader header;
    KMFDescription description;
};

