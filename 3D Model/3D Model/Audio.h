#pragma once

#include "AL\al.h"
#include "AL\alc.h"
#include "AL\alut.h"

#include <stdio.h>

class Audio
{
public:
	Audio(void);
	~Audio(void);

	ALsizei size,freq;
	ALenum 	format;
	ALvoid 	*data;
	int 	ch;
	ALboolean loop;
	void initAL();

	void playAL(int musicValue);
	void playAsStream(int musicValue);
	void stopAL(int musicValue);
	void pauseAL(int musicValue);
};

