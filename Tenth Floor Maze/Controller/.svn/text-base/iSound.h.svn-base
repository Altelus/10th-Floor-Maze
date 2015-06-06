#ifndef _I_SOUND_H_
#define _I_SOUND_H_

/* Sound Interface - Audio Component - Model Branch
 *
 * iSound.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "Frame.h" // for the Frame class declaration

//-------------------------------- iSound -------------------------------------
//
// iSound is the Interface to the Sound Primitive of the Audio Component
//
class iText;
enum  SoundType;

class iSound : public Frame {
  public:
    virtual iSound* clone() const                       = 0;
	// initialization functions
	virtual const  wchar_t* relFileName() const         = 0;
	virtual const  wchar_t* dirFileName() const         = 0;
	virtual float  coneAngle() const                    = 0;
	virtual void   attach(const iFrame* f)              = 0;
	virtual void   attach(const iText* t)               = 0;
	virtual void   change(const wchar_t* f)             = 0;
	virtual void   restore(int now)                     = 0;
	// execution functions
	virtual bool   toggle(int now)                      = 0;
    virtual Vector position() const                     = 0;
    virtual Vector orientation() const                  = 0;
	virtual void   update() const                       = 0;
	virtual void   play(int)                            = 0;
	virtual void forcePlay() = 0;
	virtual void   report(bool on) const                = 0;
	// termination functions
	virtual void   suspend()                            = 0;
	virtual void   Delete() const                       = 0;
};

extern "C"
iSound* CreateSound(const wchar_t*, SoundType, bool = true, bool = true, 
 float = 0);

iSound* Clone(const iSound*);

#endif
