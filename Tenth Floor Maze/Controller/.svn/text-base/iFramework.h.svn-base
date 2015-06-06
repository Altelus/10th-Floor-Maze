#ifndef _I_FRAMEWORK_H_
#define _I_FRAMEWORK_H_

/* Framework Interface
 *
 * iFramework.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iFramework ---------------------------------
//
// iFramework is the Interface to the Framework
//
class iFramework {
  public:
    // execution function
	virtual int  run()          = 0;
	// termination function
    virtual void Delete() const = 0;
};

extern "C"
iFramework* CreateFramework(void*, int);

#endif