/**
 * @file SoundSource.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "SoundSource.h"

SoundSource::SoundSource()
{
    alGenSources(1, &_source);
    alSourcef(_source, AL_PITCH, _pitch);
    alSourcef(_source, AL_GAIN, _gain);
    alSource3f(_source, AL_POSITION, 0, 0, 0);
    alSource3f(_source, AL_VELOCITY, 0, 0, 0);
    alSourcei(_source, AL_LOOPING, false);
    //alSourcef(_source, AL_BUFFER, _bufferId);
}

SoundSource::~SoundSource()
{
    alDeleteSources(1, &_source);
}

void SoundSource::Play(const ALuint bufferId)
{
    if (bufferId != _bufferId) {
        _bufferId = bufferId;
        alSourcei(_source, AL_BUFFER, (ALint)_bufferId);
    }

    alSourcePlay(_source);

    ALint state = AL_PLAYING;
    std::cout << "playing sound\n";
    while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
    {
        std::cout << "currently playing sound\n";
        alGetSourcei(_source, AL_SOURCE_STATE, &state);
    }
    std::cout << "done playing sound\n";    
}
