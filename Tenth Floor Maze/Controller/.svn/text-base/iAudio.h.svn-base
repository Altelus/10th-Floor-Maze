#ifndef _I_AUDIO_H_
#define _I_AUDIO_H_

/* Audio Interface - Audio Component - Model Branch
 *
 * iAudio.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iAudio -------------------------------------
//
// iAudio is the Interface to the Audio Coordinator of the Audio Component
//
class iContext;
class iSound;

class iAudio {
  public:
	// initialization functions
	virtual bool  initialize(int now)                    = 0;
	virtual bool  add(const iSound*)                     = 0;
	virtual void  reset(int now)                         = 0;
    virtual void  restore(int now)                       = 0;
	// execution functions
    virtual void  update(int now)                        = 0;
	virtual void  play(int) const                        = 0;
	// termination functions
    virtual void  suspend() const                        = 0;
	virtual bool  remove(const iSound*)                  = 0;
	virtual void  Delete() const                         = 0;
};

extern "C"
iAudio* CreateAudio(iContext* c);

#endif
