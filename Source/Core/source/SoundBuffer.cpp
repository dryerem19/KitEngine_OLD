#include "pch.h"
#include "SoundBuffer.h"

SoundBuffer::SoundBuffer()
{

}

SoundBuffer::~SoundBuffer()
{
    alDeleteBuffers(buffers.size(), buffers.data());
    buffers.clear();
}

SoundBuffer &SoundBuffer::Instance()
{
    static SoundBuffer instance;
    return instance;
}

ALuint SoundBuffer::Add(const char *pFilename)
{
    assert(pFilename && "Filename empty!");

    ALenum err, format;
    ALuint buffer;
    SNDFILE* pSndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    /* Open the audio file and check that it's usable. */
    pSndfile = sf_open(pFilename, SFM_READ, &sfinfo);
    if (!pSndfile) {
        Core::Log::Error("Could not open audio file {} {}", pFilename, sf_strerror(pSndfile));
        return 0;
    }

	if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels) {
        Core::Log::Error("Bad sample count in {} {}", pFilename, sfinfo.frames);
        sf_close(pSndfile);
        return 0;
    }

    /* Get the sound format, and figure out the OpenAL format */
    format = AL_NONE;
    switch (sfinfo.channels) {
        case 1:
            format = AL_FORMAT_MONO16;
            break;
        case 2:
            format = AL_FORMAT_STEREO16;
            break;
        case 3: 
            if (sf_command(pSndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
                format = AL_FORMAT_BFORMAT2D_16;
            }
            break;
        case 4: 
            if (sf_command(pSndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
                format = AL_FORMAT_BFORMAT3D_16;
            }
            break;
    }
    if (!format) {
        sf_close(pSndfile);
        Core::Log::Error("Unsupported channel count {}", sfinfo.channels);
        return 0;
    }

    /* Decode audio file to a buffer */
    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));
    
    num_frames = sf_readf_short(pSndfile, membuf, sfinfo.frames);
    if (num_frames < 1) {
        free(membuf);
        sf_close(pSndfile);
        Core::Log::Error("Failed to read samples in {} {}", pFilename, num_frames);
        return 0;
    }
    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    /* Buffer the audio data into a new buffer object, then free the data and  close the file. */
    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

    free(membuf);
    sf_close(pSndfile);

    /* Check if an error occured, and clean up if so */
    err = alGetError();
    if (err != AL_NO_ERROR)
    {
        Core::Log::Error("OpenAL error {}", (char *)alGetString(err));
        if (buffer && alIsBuffer(buffer))
            alDeleteBuffers(1, &buffer);
        return 0;
    }

    buffers.push_back(buffer);
    return buffer;
}

bool SoundBuffer::Remove(const ALuint &buffer)
{
    auto it = std::find(buffers.begin(), buffers.end(), buffer);
    if (it == buffers.end()) {
        Core::Log::Warning("Failed to delete buffer, because it not found {}", buffer);
        return false;
    }

    alDeleteBuffers(1, &buffer);
    buffers.erase(it);

    return true;
}
