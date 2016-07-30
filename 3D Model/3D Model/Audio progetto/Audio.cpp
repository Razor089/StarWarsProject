#include "Audio.h"

Audio::Audio(void)
{
}

Audio::~Audio(void)
{
}

#define NUM_BUFFERS 9
#define NUM_SOURCES 9
#define NUM_ENVIRONMENTS 1

ALfloat listenerPos[]={0.0,0.0,0.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat	listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};

ALfloat source0Pos[]={ 0.0, 0.0, 0.0};
ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

ALuint	buffer[NUM_BUFFERS];
ALuint	source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];


void Audio::initAL() {
	alutInit(0, NULL);

    alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);
    
    alGetError(); // clear any error messages
    
    if(alGetError() != AL_NO_ERROR) 
    {
        printf("- Errore nella creazione dei buffer!!\n");
    }
    
    // Generate buffers, or else no sound will happen!
    alGenBuffers(NUM_BUFFERS, buffer);
    
	loop = false;

	alutLoadWAVFile((ALbyte*)"music/LAZER.WAV", &format, &data, &size, &freq, &loop);
    alBufferData(buffer[0],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

    alutLoadWAVFile((ALbyte*)"music/The Asteroid Field.wav",&format,&data,&size,&freq,&loop);
    alBufferData(buffer[1],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

    alutLoadWAVFile((ALbyte*)"music/swforce2.wav",&format,&data,&size,&freq,&loop);
    alBufferData(buffer[2],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

	alutLoadWAVFile((ALbyte*)"music/xwing.wav",&format,&data,&size,&freq,&loop);
    alBufferData(buffer[3],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

	alutLoadWAVFile((ALbyte*)"music/specFX.wav",&format,&data,&size,&freq,&loop);
    alBufferData(buffer[4],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

	alutLoadWAVFile((ALbyte*)"music/XwingFire.wav",&format,&data,&size,&freq,&loop);
    alBufferData(buffer[5],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);	

	alutLoadWAVFile((ALbyte*)"music/DeathStar Explosion.wav",&format,&data,&size,&freq,&loop);
	alBufferData(buffer[6],format,data,size,freq);
	alutUnloadWAV(format,data,size,freq);

	alutLoadWAVFile((ALbyte*)"music/creditsmusic.wav",&format,&data,&size,&freq,&loop);
	alBufferData(buffer[7],format,data,size,freq);
	alutUnloadWAV(format,data,size,freq);

	alutLoadWAVFile((ALbyte*)"music/failedme.wav",&format,&data,&size,&freq,&loop);
	alBufferData(buffer[8],format,data,size,freq);
	alutUnloadWAV(format,data,size,freq);

    alGetError(); /* clear error */
    alGenSources(NUM_SOURCES, source);

    if(alGetError() != AL_NO_ERROR) 
    {
        printf("- Errore nella creazione dei sorgenti !!\n");
    }

	for (int i = 0; i < NUM_SOURCES; i++) {
		alSourcef(source[i],AL_PITCH,1.0f);
		alSourcef(source[i],AL_GAIN,1.0f);
		alSourcefv(source[i],AL_POSITION,source0Pos);
		alSourcefv(source[i],AL_VELOCITY,source0Vel);
		alSourcei(source[i],AL_BUFFER,buffer[i]);
		alSourcei(source[i],AL_LOOPING,AL_TRUE);
	}
}

void Audio::playAL(int musicValue) {
	alSourcePlay(source[musicValue]);
	alSourcei(source[musicValue], AL_LOOPING, AL_FALSE);
}

void Audio::playAsStream(int musicValue) {
	alSourcePlay(source[musicValue]);
	alSourcei(source[musicValue], AL_LOOPING, AL_TRUE);
}

void Audio::stopAL(int musicValue) {
	alSourceStop(source[musicValue]);
}

void Audio::pauseAL(int musicValue) {
	alSourcePause(source[musicValue]);
}


