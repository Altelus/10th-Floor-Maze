#ifndef _I_DESIGN_H_
#define _I_DESIGN_H_

/* Design Interface - Model Branch
 *
 * iDesign.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iDesign ------------------------------------
//
// iDesign is the Interface to the Design Component
//
class iContext;

class iDesign {
  public:
	// initialization functions
	virtual void initialize(int now)                    = 0;
	virtual void reset(int now)                         = 0;
    virtual void restore(int now)                       = 0;
	// execution functions
    virtual void update(int now)                        = 0;
	// termination functions
    virtual void Delete() const                         = 0;
	// LOAD MAP
	virtual void LoadMap(wchar_t* file_name) = 0;
};

extern "C"
iDesign* CreateDesign(iContext* c);

#endif
