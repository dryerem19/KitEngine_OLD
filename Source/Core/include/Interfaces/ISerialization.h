/**
 * @file ISerialization.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class ISerialization
{
public:
    virtual ~ISerialization() = default;

    virtual void Serialize() = 0;
};