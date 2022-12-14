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
#include "KitObject.h"

class SoundBuffer final : public KitObject
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
    float _pitch;
    float _volume;
    bool _mute;
    bool _loop;
public:
    SoundBuffer();
    ~SoundBuffer();
    void Init(const char* pFilename);
    void Play();
    void Update();

    /**
     * @brief Устанвливает громкость
     * 
     * @param value допустимые значения [0.0...1.0]
     */
    void SetVolume(float value);

    /**
     * @brief Возвращает значение громкости
     * 
     * @return float 
     */
    float GetVolume() const { return _volume; }
    
    /**
     * @brief Устанавливает высоту тона
     * 
     * @param pitch допустимые значения [0.5...2.0]
     */
    void SetPitch(float pitch);

    /**
     * @brief Возвращает значение высоты тона
     * 
     * @return float 
     */
    float GetPitch() const { return _pitch; }

    /**
     * @brief Временно убрать звук
     * Воспроизведение продолжается, но источник не слышно
     * 
     * @param mute True - убрать звук, False - включить обратно
     */
    void SetMute(bool mute);

    /**
     * @brief Проверяет, слышен ли источник
     * 
     * @return true Если звук убран
     * @return false Если источник слышен
     */
    bool IsMute() const { return _mute; }

    /**
     * @brief Проигрывание автоматически возобновляется, если установлена петля
     * 
     * @param loop True - установить петлю, False - отключить петлю
     */
    void SetLoop(bool loop);

    /**
     * @brief Проверяет, установлена ли петля
     * 
     * @return true если петля установлена
     * @return false если петля не установлена
     */
    bool IsLoop() const { return _loop; }

    bool IsPlaying() const;
    ALint GetState() const;
    void Release();
};

SoundBuffer* cast_object_to_sound_source(KitObject* pObject);