/* Audio Implementation - Audio Component - Model Branch
 *
 * Audio.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"      // for the Context Interface
#include "iUtilities.h"    // for strcpy(), error()

#include "Audio.h"         // for the Audio class declaration
#include "Sound.h"         // for Sound::isCoordinatedBy
#include "ModelSettings.h" // for AUDIO_DIRECTORY

//------------------------------- Audio ---------------------------------------
//
// The Audio Coordinator manages the sounds in Audio Component
//
// CreateAudio creates the Audio object, which implements the Audio Coordinator
//
iAudio* CreateAudio(iContext* c) {

	return new Audio(c);
}

// constructor initializes the pointers to the sounds, initializes the 
// reference time and attaches the Sound class to the Audio object
//
Audio::Audio(iContext* c) : context(c) {

    noSounds = 0;
    for (int i = 0; i < MAX_SOUNDS; i++)
        sound[i] = NULL;

	// reference time
	lastUpdate   = 0;

	// manages the Sound class
	Sound::isCoordinatedBy(this); 
}

// initialize sets the volume and frequency parameters for the Audio Coordinator
//
bool Audio::initialize(int now) {

    // volume and frequency settings
    idle      = context->get(GF_AU_FREQ) - FREQ_RANGE;
    freq      = idle;
    maxVolume = context->get(GF_AU_MXVL);
    minVolume = context->get(GF_AU_MNVL);
    incVolume = (maxVolume - minVolume) / DELTA_VOLUME;
    curVolume = maxVolume;
    context->set(GF_AU_CVOL, curVolume);

    // reference time
    lastUpdate = now;

    return true;
}

// add adds iSound *s to the Audio Component and returns true if 
// successful, false otherwise
//
bool Audio::add(const iSound* s) {

    int i;
    bool rc = false;

    for (i = 0; i < noSounds; i++)
        if (!sound[i]) {
            sound[i] = s;
            i = noSounds + 1;
            rc = true;
        }
    if (i == noSounds && noSounds < MAX_SOUNDS) {
        sound[noSounds++] = s;
        rc = true;
    }

    return rc;
}

// reset reinitializes the reference time
//
void Audio::reset(int now) {

	// reference time
	lastUpdate = now;
}

// restore restores each sound and resets the reference time 
//
void Audio::restore(int now) {

	for (int i = 0; i < noSounds; i++) {
		if (sound[i]) 
			const_cast<iSound*>(sound[i])->restore(now);
	}

	// reinitialize reference time
	lastUpdate = now;
}

// attenuate attenuates the volume of the ambient sounds by factor *
// incVolume - positive factor increases the volume, negative factor
// decreases the volume
//
void Audio::attenuate(int factor) {

    curVolume = curVolume + factor * incVolume;
    if (curVolume > maxVolume)
        curVolume = maxVolume;
    else if (curVolume < minVolume)
        curVolume = minVolume;
    context->set(GF_AU_CVOL, curVolume);
}

// update updates the volume and frequency according to the user's intervention
// and resets the reference time
//
void Audio::update(int now) {

    long dz = 0;
    int delta = now - lastUpdate;

	// RYAN: Not necessary for this game. 

    //// joystick input
    //int iy = context->get(GF_CT_DSPY);
    //if (iy)
    //    dz = (long)(iy * CTR_DISPLACEMENT_FACTOR);

    //if (context->pressed(AUD_VOLUME_DEC))
    //    attenuate(-1);
    //if (context->pressed(AUD_VOLUME_INC))
    //    attenuate(1);
    //if (context->pressed(AUD_SPEED_UP))
    //    dz += delta;
    //if (context->pressed(AUD_SLOW_DOWN))
    //    dz -= delta;

    //// drop frequency if AUD_SLOW_DOWN
    //if (dz == 0 && freq > idle) {
    //    long newfreq = freq - FREQ_DROP_VELOCITY * delta;
    //    freq = newfreq < idle ? idle : newfreq;
    //    context->set(GF_AU_FREQ, freq);
    //}
    //// increase frequency if AUD_SPEED_UP
    //else if (dz != 0 && freq < idle + FREQ_RANGE) {
    //    long newfreq = freq + FREQ_RISE_VELOCITY * (dz > 0 ? dz : -dz);
    //    freq = newfreq > idle + FREQ_RANGE ? idle + FREQ_RANGE : newfreq;
    //    context->set(GF_AU_FREQ, freq);
    //}

    // update the Sound objects
    for (int i = 0; i < noSounds; i++)
		if (sound[i]) 
			sound[i]->update();

	// reset reference time
    lastUpdate = now;
}

// play() implements the playing of each Sound object of the Audio Component
//
void Audio::play(int now) const {

    for (int i = 0; i < noSounds; i++)
		if (sound[i]) 
			const_cast<iSound*>(sound[i])->play(now);
}

// suspend suspends the playing of all Sound objects
//
void Audio::suspend() const {

    for (int i = 0; i < noSounds; i++)
		if (sound[i]) 
			const_cast<iSound*>(sound[i])->suspend();
}

// remove removes iSound *s from the Audio Component and returns true if
// successful, false otherwise
//
bool Audio::remove(const iSound* s) {

    bool rc = false;

    for (int i = 0; i < noSounds; i++)
        if (sound[i] == s) {
            sound[i] = NULL;
            rc = true;
        }
    while (!sound[noSounds - 1])
        noSounds--;

    return rc;
}

// destructor deletes all of the Sound objects within the Audio Component 
//
Audio::~Audio() {

    for (int i = 0; i < noSounds; i++)
        if (sound[i])
            sound[i]->Delete();
}

