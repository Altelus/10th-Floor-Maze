#ifndef _I_SOUND_CARD_H_
#define _I_SOUND_CARD_H_

/* SoundCard Interface - SoundCard Component - Direct Device Branch
 *
 * iSoundCard.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//------------------------------- iSoundCard ----------------------------------
//
// iSoundCard is the Interface to the SoundCard Portal of the Sound Card 
// Component 
//
class iContext;

class iSoundCard {
  public:
	// initialization functions
    virtual bool setup(void*)                  = 0;
	// execution function
    virtual void update()                      = 0;
	// termination functions
    virtual void release()                     = 0;
	virtual void Delete() const                = 0;
};

extern "C"
iSoundCard* CreateSoundCard(iContext*);

#endif
