/**
 * @file SoundDevice.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class SoundManager
{
private:
    SoundManager();
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    ~SoundManager();
private:
    ALCdevice* pAlcDevice;
    ALCcontext* pAlcContext;
public:
    static SoundManager& Instance();
};