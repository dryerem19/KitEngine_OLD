/**
 * @file SoundManager.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
    : pAlcDevice(nullptr), pAlcContext(nullptr), _release(false)
{
    pAlcDevice = alcOpenDevice(nullptr);
    assert(pAlcDevice && "Failed to get sound device");

    pAlcContext = alcCreateContext(pAlcDevice, nullptr);
    assert(pAlcContext && "Failed to set sound context");

    /* Set active context */
    ALCboolean result = alcMakeContextCurrent(pAlcContext);
    assert(result && "Failed to make current ALC context");

    /* Initialize listener */
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alListenerf(AL_GAIN, 1.0f);

    const ALCchar* pName = nullptr;
    if (alcIsExtensionPresent(pAlcDevice, "ALC_ENUMERATE_ALL_EXT"))
        pName = alcGetString(pAlcDevice, ALC_ALL_DEVICES_SPECIFIER);

    if (!pName || alcGetError(pAlcDevice) != AL_NO_ERROR)
        pName = alcGetString(pAlcDevice, ALC_DEVICE_SPECIFIER);

    // Setup model audio
    alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
    alListener3f(AL_POSITION, 0, 0, 0);
}

SoundManager::~SoundManager()
{
    Release();
}

SoundManager& SoundManager::Instance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::Release()
{
    if (_release)
        return;

    /* Reset to current context to NULL */
    ALCboolean result = alcMakeContextCurrent(nullptr);
    assert(result && "Failed to set sound context to nullptr");

    /* Destroy the context */
    if (pAlcContext) {
        alcDestroyContext(pAlcContext);
        pAlcContext = nullptr;
    }

    /* Close the device */
    if (pAlcDevice) {
        result = alcCloseDevice(pAlcDevice);
        pAlcDevice = nullptr;
    }

    _release = true;
}
