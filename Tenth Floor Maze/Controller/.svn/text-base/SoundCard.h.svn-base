#ifndef _SOUND_CARD_H_
#define _SOUND_CARD_H_

/* SoundCard Declaration - SoundCard Component - Direct Device Branch
 *
 * SoundCard.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iSoundCard.h" // for the SoundCard Interface

#define WIN32_LEAN_AND_MEAN
#define  INITGUID       // enables access to GUIDs used by DirectMusic
#include <dmusici.h>    // includes dsound.h, dmusicc.h, dmerr.h
#undef   INITGUID

//------------------------------- SoundCard -----------------------------------
//
// The SoundCard Portal manages the API connectivity for the SoundCard 
// Component
//
class SoundCard : public iSoundCard {

	iContext*                 context; // points to the Context object

    IDirectMusicPerformance8* mperf;             // music performance
    IDirectMusicLoader8*      loader;            // for loading files
    IDirectMusicAudioPath8*   ambientAudioPath;  // for ambient sounds
    IDirectSoundBuffer8*      buffer;            // on ambient path
    IDirectMusicAudioPath8*   listenerAudioPath; // for listener
    IDirectSound3DListener8*  listener;          // for local sounds

    SoundCard(iContext*);
    SoundCard(const SoundCard& s);            // prevent copying
    SoundCard& operator=(const SoundCard& s); // prevent assignments
    virtual ~SoundCard();

  public:
	friend iSoundCard* CreateSoundCard(iContext*);
	// initialization function
    bool   setup(void*);
	// execution function
    void   update();
	// termination functions
    void   release();
	void   Delete() const { delete this; }
	friend class Segment;
};

#endif
