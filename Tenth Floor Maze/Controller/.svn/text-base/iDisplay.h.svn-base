#ifndef _I_DISPLAY_H_
#define _I_DISPLAY_H_

/* Display Element Interface - GraphicsCard Component - Direct Device Branch
 *
 * iDisplay.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iDisplay -----------------------------------
//
// iDisplay is the Interface to the Display Portal of the Graphics Card
// Component
//
class iContext;

class iDisplay {
  public:
	// configuration functions
	virtual bool  interrogate(void*)                                   = 0;
    virtual void  setConfiguration()                                   = 0;
	// initialization functions
    virtual bool  setup(void*)                                         = 0;
    virtual int   getLightIndex()                                      = 0;
    virtual bool  restore()                                            = 0;
	// execution functions
    virtual void  beginDraw()                                          = 0;
    virtual void  alphaBlendOn()                                       = 0;
    virtual void  alphaBlendOff()                                      = 0;
    virtual void  beginSuperimpose()                                   = 0;
    virtual void  endDraw()                                            = 0;
    virtual void* device() const                                       = 0;
    virtual int   width() const                                        = 0;
    virtual int   height() const                                       = 0;
    virtual void* spriteManager() const                                = 0;
    virtual void  resize()											   = 0;
	virtual void  toggleFog(bool)						               = 0;
	virtual void  setFogColor(unsigned long)						   = 0;
	virtual void  setFogStartEnd(float, float)					       = 0;
	// termination functions
    virtual void  suspend()                                            = 0;
    virtual void  releaseLightIndex(int i)                             = 0;
    virtual void  release()                                            = 0;
	virtual void  Delete()                                             = 0;
};

extern "C"
iDisplay* CreateDisplay(iContext*);

#endif