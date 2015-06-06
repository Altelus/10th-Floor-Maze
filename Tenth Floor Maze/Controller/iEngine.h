#ifndef _I_ENGINE_H_
#define _I_ENGINE_H_

/* Engine Interface
 *
 * iEngine.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iEngine ------------------------------------
//
// iEngine is the Interface to the Engine for the Model and Direct-Device 
// Components
//
class iContext;

class iEngine {
  public:
	// configuration functions
    virtual void interrogate(void*) = 0;
	virtual void reset()            = 0;
	// initialization function
    virtual void restore()          = 0;
    // execution function
	virtual int  run()              = 0;
	virtual void resize() const     = 0;
    virtual bool isActive() const   = 0;
	// termination functions
    virtual void suspend()          = 0;
    virtual void Delete() const     = 0;
};

extern "C"
iEngine* CreateEngine(void*, int, iContext*);

extern "C"
iEngine* EngineAddress();

#endif