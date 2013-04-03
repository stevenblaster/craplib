#include "crap.h"

#include "threading/sleep.h"
#include "audio/audiodevice.h"

#include "audio/test.h"

void playme( void )
{
	crap::audiodevice ad;

	ALuint buf1;
    alGenBuffers(1, &buf1);
	ALuint buf2;
    alGenBuffers(1, &buf2);
	ALuint buf3;
    alGenBuffers(1, &buf3);

	float freq1 = 440.f;
	float freq2 = 587.f;
	float freq3 = 660.f;

	int byte_per_sec = 2;

    int seconds1 = 4;
	int seconds2 = 3;
	int seconds3 = 2;

	unsigned sample_rate = 44100;

    size_t buf_size1 = seconds1 * sample_rate * byte_per_sec;
	size_t buf_size2 = seconds2 * sample_rate * byte_per_sec;
	size_t buf_size3 = seconds3 * sample_rate * byte_per_sec;

    short *samples1 = new short[buf_size1];
    short *samples2 = new short[buf_size2];
	short *samples3 = new short[buf_size3];

	memset(samples1, 0, sizeof(short)*buf_size1);
	memset(samples2, 0, sizeof(short)*buf_size2);
	memset(samples3, 0, sizeof(short)*buf_size3);

    for(int i=0; i<buf_size1; ++i) {
        samples1[i] = 32760 * sin( (2.f*float(CRAP_PI)*freq1)/sample_rate * i );
    }
	for(int i=0; i<buf_size2; ++i) {
        samples2[i] = 32760 * sin( (2.f*float(CRAP_PI)*freq2)/sample_rate * i );
    }
	for(int i=0; i<buf_size3; ++i) {
        samples3[i] = 32760 * sin( (2.f*float(CRAP_PI)*freq3)/sample_rate * i );
    }

	alBufferData(buf1, AL_FORMAT_MONO16, samples1, buf_size1, sample_rate);
	alBufferData(buf2, AL_FORMAT_MONO16, samples2, buf_size2, sample_rate);
	alBufferData(buf3, AL_FORMAT_MONO16, samples3, buf_size3, sample_rate);

    /* Set-up sound source and play buffer */
    ALuint src1 = 0;
    alGenSources(1, &src1);
    alSourcei(src1, AL_BUFFER, buf1);
	ALuint src2 = 0;
    alGenSources(1, &src2);
    alSourcei(src2, AL_BUFFER, buf2);
	ALuint src3 = 0;
    alGenSources(1, &src3);
    alSourcei(src3, AL_BUFFER, buf3);

	alSourcePlay(src1);
	crap::sleep_msec(1000);
    alSourcePlay(src2);
	crap::sleep_msec(1000);
	alSourcePlay(src3);
	crap::sleep_msec(2000); 
}