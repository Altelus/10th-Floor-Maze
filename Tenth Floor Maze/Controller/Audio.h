#ifndef _AUDIO_H_
#define _AUDIO_H_

/* Audio Declaration - Audio Component - Model Branch
 *
 * Audio.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iAudio.h" // for the Audio Interface

//-------------------------------- Audio --------------------------------------
//
// The Audio Coordinator manages the sounds in the Audio Component 
//
class Audio : public iAudio {

	static const int MAX_SOUNDS = 50;

	iContext*     context;           // points to the Context object

    int           noSounds;          // number of sound sources
    const iSound* sound[MAX_SOUNDS]; // points to the sound sources

    long          idle;              // idle ambient frequency
    long          freq;              // current ambient frequency
    long          maxVolume;         // maximum volume
    long          minVolume;         // minimum volume
    long          incVolume;         // volume increment
    long          curVolume;         // current volume

	int           lastUpdate;        // reference time

    Audio(iContext*);
    Audio(const Audio& s);            // prevents copying
    Audio& operator=(const Audio& s); // prevents assignments
    void    attenuate(int factor);
    virtual ~Audio();

  public:
	friend iAudio* CreateAudio(iContext*);
	// initialization functions
    bool   initialize(int now);
    bool   add(const iSound*);
	void   reset(int now);
    void   restore(int now);
	// execution functions
    void   update(int now);
    void   play(int) const;
	// termination functions
    void   suspend() const;
    bool   remove(const iSound*);
	void   Delete() const { delete this; }
};

#endif
