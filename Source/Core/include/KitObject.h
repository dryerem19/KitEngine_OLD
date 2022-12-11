/**
 * @file KitObject.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class GameLevel;

class KitObject
{
public:
    KitObject() : mID(0) {};

    uint32_t GetID() const { return mID; }
private:
    friend class GameLevel;
    uint32_t mID;

    void SetID(const uint32_t id) 
    {
        mID = id;
    };
};
