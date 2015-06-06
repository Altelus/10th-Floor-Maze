#ifndef _SOUND_H_
#define _SOUND_H_

/* Sound Declaration - Audio Component - Model Branch
 *
 * Sound.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iSound.h" // for the Sound Interface

//------------------------------- Sound ---------------------------------------
//
// The Sound Primitive represents a single sound in the Audio Component
//
class iAudio;
class iSegment;

class Sound : public iSound {

    static iAudio*  coordinator; // points to the Audio Object

    const iSegment* segment; // points to the representation on the device
    const iFrame*   frame;   // points to the host frame, if any exists
	const iText*    text;    // points to the attached text, if any
    wchar_t*        dirFile; // name of the sound file with path
	wchar_t*        relFile; // name of the sound file without path

    SoundType       type;        // type of sound - local or global
    float           cone;        // angle of sound cone in degrees [0,360]
    bool            on;          // is this sound on?
    bool            setToStart;  // is this sound ready to start playing?
    bool            setToStop;   // is this sound ready to stop playing?
    bool            continuous;  // is this sound continuous?
	bool            overwrite;   // is this sound's text to be overwritten?

    int             lastToggle;  // time of the last toggle

    Sound(const wchar_t*, SoundType, bool, bool, float = 0);
	Sound(const Sound&);
    virtual ~Sound();

  public:
	friend iSound* CreateSound(const wchar_t*, SoundType, bool, bool, float);
	static void isCoordinatedBy(iAudio* audio)  { coordinator = audio; }
	Sound& operator=(const Sound&);
    iSound* clone() const                   { return new Sound(*this); }
	// initialization functions
	const  wchar_t* dirFileName() const     { return dirFile; }
	const  wchar_t* relFileName() const     { return relFile; }
	float  coneAngle() const                { return cone; }
	void   attach(const iFrame* f);
	void   attach(const iText* t);
	void   change(const wchar_t* f);
	void   restore(int now);
	// execution functions
	bool   toggle(int now);
    Vector position() const;
    Vector orientation() const;
	void   update() const;
	void   forcePlay();
	void   play(int);
	void   report(bool on) const;
	// termination functions
	void   suspend();
	void   Delete() const                   { delete this; }
};

#endif
