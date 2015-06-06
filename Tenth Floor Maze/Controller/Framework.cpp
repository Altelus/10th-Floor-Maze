/* Framework Implementation  
 *                       
 * Framework.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"  // for the Context Interface
#include "iEngine.h"   // for the Engine Interface

#include "Framework.h" // for the Framework class declaration

//-------------------------------- Framework ----------------------------------
//
// The Framework constructor creates the Context and Engine Objects
//
Framework::Framework(void* hinst, int show) {

    context = CreateContext();
    engine  = CreateEngine(hinst, show, context);
}

// run runs the Engine and returns the exit code
//
int Framework::run() {

	return context && engine ? engine->run() : 0;
}

// destructor deletes the Engine and the Context Objects
//
Framework::~Framework() {

	if (engine) engine->Delete();
    if (context) context->Delete();
}

