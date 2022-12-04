/**
 * @file IDeserialization.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class IDeserialization
{
public:
    virtual ~IDeserialization() = default;

    virtual void Deserialize(const std::string& filepath) = 0;
};