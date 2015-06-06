#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

/* Framework Declaration
 *
 * Framework.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- Framework ----------------------------------
//
// The Framework supervises the Context and the Engine Objects 
//
class iContext;
class iEngine;

class Framework {

    iContext* context; // points to the Context object
    iEngine*  engine;  // points to the Engine object

	Framework(const Framework& m);            // prevents copying
	Framework& operator=(const Framework& m); // prevents assignment

  public:
    Framework(void*, int);
	int     run();
    virtual ~Framework();
};

#endif