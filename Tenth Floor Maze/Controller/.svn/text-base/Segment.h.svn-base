#ifndef _SEGMENT_H_
#define _SEGMENT_H_

/* Segment Declaration - SoundCard Component - Direct Device Branch
 *
 * Segment.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iSegment.h" // for the Segment Interface

#define WIN32_LEAN_AND_MEAN
#define  INITGUID     // enables access to GUIDs used by DirectMusic
#include <dmusici.h>  // includes dsound.h, dmusicc.h, dmerr.h
#undef   INITGUID

//-------------------------------- Segment ------------------------------------
//
// The Segment Primitive implements a Sound in the Sound Card Component 
//
class iSound;
class SoundCard;

class Segment : public iSegment {

    static SoundCard*       soundCard; // points to the SoundCard object

    IDirectMusicSegment8*   segment;   // sound segment
    IDirectMusicAudioPath8* audioPath; // controls the playback
    IDirectSound3DBuffer8*  buffer;    // on the audio path

    Segment();
    virtual ~Segment();

  public:
	friend iSegment* CreateSegment();
	static void connectsThrough(SoundCard* s) { soundCard = s; }
    Segment(const Segment& s);
    Segment& operator=(const Segment& s);
    iSegment* clone() const { return new Segment(*this); }
	// initialization functions
    bool   setup(const iSound* sound, bool global, bool continuous);
	// execution functions
    void   update(const iSound* sound);
    void   play(const iSound* sound, bool global, bool continuous);
	void   status(const iSound* sound) const;
    void   stop(const iSound* sound);
	// termination functions
	void   release();
	void   Delete() const { delete this; }
};
#endif
