#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <iostream>
using namespace std;

const int SRATE = 44100;
const int SSIZE = 1024;

ALbyte buffer[22050];
ALint sample;

int main(int argc, char *argv[]) {
    alGetError();
    ALCdevice *device = alcCaptureOpenDevice(NULL, SRATE, AL_FORMAT_STEREO16, SSIZE);
    if (alGetError() != AL_NO_ERROR) {
        return 0;
    }
    alcCaptureStart(device);

    while (true) {
        alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, (ALCsizei)sizeof(ALint), &sample);
        alcCaptureSamples(device, (ALCvoid *)buffer, sample);

        // ... do something with the buffer 
    }

    alcCaptureStop(device);
    alcCaptureCloseDevice(device);

    return 0;
}
