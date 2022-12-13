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
    static const uint32_t BUFFER_SAMPLES = 8192;
    static const uint32_t NUM_BUFFERS = 4;
    ALuint _source;
    ALuint _buffers[NUM_BUFFERS];
    SF_INFO _sfinfo;
    ALenum _format;
    short* _pMembuf;
    SNDFILE* _pSndfile;
    ALint _state;
public:
    SoundBuffer();
    ~SoundBuffer();
    void Init(const char* pFilename);
    void Play();
    void Update();
    bool IsPlaying() const;
    ALint GetState() const;
    void Release();
};