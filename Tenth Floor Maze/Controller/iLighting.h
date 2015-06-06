#ifndef _I_LIGHTING_H_
#define _I_LIGHTING_H_

/* Lighting Interface - Lighting Component - Model Branch
 *
 * iLighting.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iLighting ----------------------------------
//
// iLighting is the Interface to the Lighting Coordinator of the Lighting 
// Component
//
class iContext;
class iLight;

class iLighting {
  public:
    // initialization functions
    virtual bool add(const iLight*)                     = 0;
	virtual void restore(int now)                       = 0;
	// execution functions
	virtual void update() const                         = 0;
	// termination functions
	virtual void suspend() const                        = 0;
    virtual bool remove(const iLight*)                  = 0;
	virtual void Delete() const                         = 0;
};

extern "C"
iLighting* CreateLighting(iContext* c);

#endif
