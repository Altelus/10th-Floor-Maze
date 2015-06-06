#ifndef _I_SEGMENT_H_
#define _I_SEGMENT_H_

/* Segment Interface - SoundCard Component - Direct Device Branch
 *
 * iSegment.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- Segment ------------------------------------
//
// iSegment is the Interface to the Segment Primitive of the Sound Card 
// Component
//
class  iSound;

class iSegment {
  public:
    virtual iSegment* clone() const                                 = 0;
	// initialization functions
    virtual bool setup(const iSound* sound, bool global, bool cont) = 0;
	// execution functions
    virtual void update(const iSound* sound)                        = 0;
    virtual void play(const iSound* sound, bool global, bool cont)  = 0;
	virtual void status(const iSound* sound) const                  = 0;
    virtual void stop(const iSound* sound)                          = 0;
	// termination functions
	virtual void release()                                          = 0;
	virtual void Delete() const                                     = 0;
};

extern "C"
iSegment* CreateSegment();

#endif
