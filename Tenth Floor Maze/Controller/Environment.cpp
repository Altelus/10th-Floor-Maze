/* Environment Implementation - GraphicsCard Component - Direct Device Branch
 *
 * Environment.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iDisplay.h"         //GMOK:  for the Display Interface
#include "iUtilities.h"       //GMOK:  for error()

#include "Environment.h"    //GMOK:  for the Environment class declaration

//GMOK: -------------------------------- Environment ------------------------------
//GMOK: 
//GMOK:  The Environment represents the display in the Graphics Card
//GMOK:  Component
//GMOK: 
//GMOK:  The Display object provides the API connectivity for the environment
//GMOK: 
iDisplay* Environment::display = NULL;

iEnvironment* CreateEnvironment() {

	return new Environment();
}

//GMOK:  constructor initializes the texture identifier
//GMOK: 
Environment::Environment() {
}

Environment::Environment(const Environment& src) {

    *this = src;    
}

Environment& Environment::operator=(const Environment& src) {

    if (this != &src) {
    }

    return *this;
}

void Environment::setup() {

}

//GMOK: Toggles state of for (on/off)
void Environment::toggleFog(bool fe)
{
	display->toggleFog(fe);
}

//GMOK: sets the fog color
void Environment::setFogColor(unsigned long c)
{
	display->setFogColor(c);
}

//GMOK: sets the fog start and end distance from player (fog thickness/density)
void Environment::setFogStartEnd(float s, float e)
{
	//const_cast<iDisplay*>(display)->setFogStartEnd(s,e);
	display->setFogStartEnd(s,e);
}

void Environment::suspend() {
}

void Environment::release() {

    suspend();
}

//GMOK:  destructor suspends the environment
//GMOK: 
Environment::~Environment() {

   release();
}
