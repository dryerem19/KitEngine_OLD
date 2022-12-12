/**
 * @file SoundBuffer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Logger.h"

class SoundBuffer
{
private:
    SoundBuffer();
    SoundBuffer(const SoundBuffer&) = delete;
    SoundBuffer& operator=(const SoundBuffer&) = delete;
    ~SoundBuffer();
private:
    std::vector<ALuint> buffers;
public:
    static SoundBuffer& Instance();
    ALuint Add(const char* pFilename);
    bool Remove(const ALuint& buffer);
};