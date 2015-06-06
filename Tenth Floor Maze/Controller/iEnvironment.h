#ifndef _I_ENVIRONMENT_H_
#define _I_ENVIRONMENT_H_

/* Enviroment Interface - GraphicsCard Component - Direct Device Branch
 *
 * iEnvironment.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */
//GMOK: -------------------------------- iEnvironment -----------------------------
//GMOK: 
//GMOK: iEnvironment is the Interface to the Environment of the
//GMOK: Graphics Card Component

class iEnvironment {
  public:
    virtual iEnvironment* clone() const                             = 0;
	// initialization functions
	virtual void setup()        = 0;
	// execution functions
	virtual void toggleFog(bool)						              = 0;
	virtual void setFogColor(unsigned long)						      = 0;
	virtual void setFogStartEnd(float, float)					      = 0;
	// termination functions
	virtual void suspend()                                            = 0;
	virtual void release()                                            = 0;
	virtual void Delete() const                                       = 0;
};

extern "C"
iEnvironment* CreateEnvironment();

#endif