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
#include <Interfaces/ISerialization.h>
#include <Interfaces/IDeserialization.h>

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

class KitModelFile final : public ISerialization, public IDeserialization
{
public:
    KMFHeader header;
    KMFDescription description;

    void Serialize() override;
    void Deserialize(const std::string& filepath) override; 
    inline bool IsValid() const { return mIsValid; }
private:
    bool mIsValid = false;

};
