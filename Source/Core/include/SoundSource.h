/**
 * @file SoundSource.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class SoundSource
{
private:
    ALuint _source;
    float _pitch = 1.f;
    float _gain = 1.f;
    float _positions[3] = { 0, 0, 0};
    float _velocity[3] = { 0, 0, 0};
    bool _loop = false;
    ALuint _bufferId = 0;
public:
    SoundSource();
    ~SoundSource();
    void Play(const ALuint bufferId);
};