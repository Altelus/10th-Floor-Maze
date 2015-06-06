#ifndef _I_VIEWERS_H_
#define _I_VIEWERS_H_

/* Viewing Interface - Viewing Component - Model Branch
 *
 * iViewing.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iViewing -----------------------------------
//
// iViewing is the Interface to the Viewing Coordinator of the Viewing Component
//
class iContext;
class iCamera;

class iViewing {
  public:
    // initialization functions
    virtual bool add(const iCamera*)              = 0;
    virtual void initialize(int now)              = 0;
    virtual void reset(int now)                   = 0;
	virtual void restore(int now)                 = 0;
	// execution functions
	virtual void update(int now)                  = 0;
	virtual void report() const                   = 0;
	// termination functions
    virtual bool remove(const iCamera*)           = 0;
	virtual void Delete() const                   = 0;
};

extern "C"
iViewing* CreateViewing(iContext* c);

#endif
