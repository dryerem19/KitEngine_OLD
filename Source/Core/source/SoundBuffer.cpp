#include "pch.h"
#include "SoundBuffer.h"

SoundBuffer::SoundBuffer()
    : KitObject(KIT_OBJECT_SOUND)
{
    _format = AL_NONE;
    _pMembuf = nullptr;
    _pSndfile = nullptr;
    _state = AL_STOPPED;
    _volume = 1.f;
    _pitch = 1.f;
    _mute = false;
    _loop = false;

    SetName("Sound");
}

void SoundBuffer::Init(const char* pFilename)
{
    assert(pFilename && "Filename empty!");

    // Clear all errors
    alGetError();
    Release();

    alGenSources(1, &_source);
    alGenBuffers(NUM_BUFFERS, _buffers);

    alSourcef(_source, AL_ROLLOFF_FACTOR, 1.0f);
    alSourcef(_source, AL_REFERENCE_DISTANCE, 6);
    alSourcef(_source, AL_MAX_DISTANCE, 15);

    /* Open the audio file and check that it's usable. */
    _pSndfile = sf_open(pFilename, SFM_READ, &_sfinfo);
    if (!_pSndfile) {
        Core::Log::Error("Could not open audio file {} {}", pFilename, sf_strerror(_pSndfile));
        return;
    }

	if (_sfinfo.frames < 1 || _sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / _sfinfo.channels) {
        Core::Log::Error("Bad sample count in {} {}", pFilename, _sfinfo.frames);
        sf_close(_pSndfile);
        return;
    }

    /* Get the sound format, and figure out the OpenAL format */
    _format = AL_NONE;
    switch (_sfinfo.channels) {
        case 1:
            _format = AL_FORMAT_MONO16;
            break;
        case 2:
            _format = AL_FORMAT_STEREO16;
            break;
        case 3: 
            if (sf_command(_pSndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
                _format = AL_FORMAT_BFORMAT2D_16;
            }
            break;
        case 4: 
            if (sf_command(_pSndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
                _format = AL_FORMAT_BFORMAT3D_16;
            }
            break;
    }
    if (!_format) {
        sf_close(_pSndfile);
        Core::Log::Error("Unsupported channel count {}", _sfinfo.channels);
        return;
    }

    size_t frame_size = ((size_t)BUFFER_SAMPLES * (size_t)_sfinfo.channels) * sizeof(short);
    _pMembuf = new short[frame_size];
}

void SoundBuffer::Play()
{
    assert(_pSndfile && "pSndfile nullptr!");
    assert(_pMembuf && "pMembuf nullptr!");

    // Clear all errors
    alGetError();

    /* Rewind the source position and clear the buffer queue */
    alSourceRewind(_source);
    alSourcei(_source, AL_BUFFER, 0);

    /* Fill the buffer queue */
    for (uint8_t iBuffer = 0; iBuffer < NUM_BUFFERS; iBuffer++)
    {
        /* Get some data to give it to the buffer */
        sf_count_t slen = sf_readf_short(_pSndfile, _pMembuf, BUFFER_SAMPLES);
        if (slen < 1)
            break;
        
        slen *= _sfinfo.channels * (sf_count_t)sizeof(short);
        alBufferData(_buffers[iBuffer], _format, _pMembuf, (ALsizei)slen, _sfinfo.samplerate);
    }

    if (alGetError() != AL_NO_ERROR) {
        Core::Log::Error("Error buffering for playback");
        return;        
    }

    /* Now queue and start playback */
    alSourceQueueBuffers(_source, NUM_BUFFERS, _buffers);
    alSourcePlay(_source);

    if (alGetError() != AL_NO_ERROR) {
        Core::Log::Error("Error starting playback");
        return;        
    }

    _state = AL_PLAYING;
}

void SoundBuffer::Update()
{
    assert(_pSndfile && "pSndfile nullptr!");
    assert(_pMembuf && "pMembuf nullptr!");

    // Set current position
    alSource3f(_source, AL_POSITION, transform.GetPosition().x,
                                     transform.GetPosition().y,
                                     transform.GetPosition().z);

    if (transform.IsDirty()) {
        std::cout << transform.DebugString() << std::endl;
    }                                     

    // Clear all errors
    alGetError();

    ALint processed, state;
    alGetSourcei(_source, AL_SOURCE_STATE, &state);
    alGetSourcei(_source, AL_BUFFERS_PROCESSED, &processed);

    if (alGetError() != AL_NO_ERROR) {
        Core::Log::Error("Error chacking source state");
        return;        
    }    

    /* Unqueue and handle each processed buffer */
    while (processed > 0)
    {
        ALuint buffer_id;
        alSourceUnqueueBuffers(_source, 1, &buffer_id);
        processed--;

        /* Read the next chunk of data, refill the buffer, and queue it back on the source */
        sf_count_t slen = sf_readf_short(_pSndfile, _pMembuf, BUFFER_SAMPLES);
        if (slen > 0)
        {
            slen *= _sfinfo.channels * (sf_count_t)sizeof(short);
            alBufferData(buffer_id, _format, _pMembuf, (ALsizei)slen, _sfinfo.samplerate);
            alSourceQueueBuffers(_source, 1, &buffer_id);
        }

        if (alGetError() != AL_NO_ERROR) {
            Core::Log::Error("Error buffering data");
            return;        
        }            
    }

    /* Make sure the source hasn't uderrun */
    if (state != AL_PLAYING && state != AL_PAUSED)
    {
        /* If no buffers are queued, playback is finished */
        ALint queued;
        alGetSourcei(_source, AL_BUFFERS_QUEUED, &queued);
        if (queued == 0){
            _state = AL_STOPPED;
            return;
        }

        alSourcePlay(_source);
        if (alGetError() != AL_NO_ERROR) {
            Core::Log::Error("Error restarting playback");
            return;        
        }               

        _state = AL_PLAYING;     
    }
}

void SoundBuffer::SetVolume(float value)
{
    assert((value >= 0 && value <= 1) && "acceptable range [0.0...1.0]");
    alSourcef(_source, AL_GAIN, value);
    _volume = value;
}

void SoundBuffer::SetPitch(float pitch)
{
    assert((pitch >= 0.5 && pitch <= 2.0) && "acceptable range [0.5...2.0]");
    alSourcef(_source, AL_PITCH, pitch);
    _pitch = pitch;
}

void SoundBuffer::SetMute(bool mute)
{
    _mute = mute;

    if (mute) {
        alSourcef(_source, AL_GAIN, 0.0f);
        return;
    }

    alSourcef(_source, AL_GAIN, _volume);
}

void SoundBuffer::SetLoop(bool loop)
{
    _loop = loop;

    alSourcei(_source, AL_LOOPING, loop);
}

bool SoundBuffer::IsPlaying() const
{
    return _state == AL_PLAYING;
}

ALint SoundBuffer::GetState() const
{
    ALint state;
    alGetSourcei(_source, AL_SOURCE_STATE, &state);
    return state;
}

void SoundBuffer::Release()
{
    alDeleteSources(1, &_source);

    if (_pSndfile) {
        sf_close(_pSndfile);
        _pSndfile = nullptr;
    }

    if (_pMembuf) {
        delete[] _pMembuf;
        _pMembuf = nullptr; 
    }

    std::memset(&_sfinfo, 0, sizeof(SF_INFO));
    _format = AL_NONE;
    _state = AL_STOPPED;

    alDeleteBuffers(NUM_BUFFERS, _buffers);    
}

SoundBuffer::~SoundBuffer()
{
    Release();
}

SoundBuffer* cast_object_to_sound_source(KitObject* pObject) 
{
    if (!pObject || pObject->Type() != KIT_OBJECT_SOUND)
        return nullptr;       

    return dynamic_cast<SoundBuffer*>(pObject); 
}