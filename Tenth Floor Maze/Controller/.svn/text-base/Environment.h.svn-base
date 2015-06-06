#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

/* Environment Declaration - GraphicsCard Component - Direct Device Branch
 *
 * Environment.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iEnvironment.h"   //GMOK:  for the Environment Interface
#include "GraphicsPlatform.h" //GMOK:  for graphics api headers

//GMOK: -------------------------------- Environment ------------------------------
//GMOK: 
//GMOK:  Environment configures the settings of the display (Fog)
//GMOK: 
class iDisplay;

class Environment : public iEnvironment {

	static iDisplay* display; //GMOK:  points to the Display object

	Environment();
	virtual ~Environment();

	void setup();

  public:
	friend iEnvironment* CreateEnvironment();
	static void connectsThrough(iDisplay* d) { display = d; }
	Environment(const Environment&);
	Environment& operator=(const Environment&);
    iEnvironment* clone() const { return new Environment(*this); }
	// execution functions
	void   toggleFog(bool fe);
	void   setFogColor(unsigned long color);
	void   setFogStartEnd(float s, float e);
	// termination functions
	void   suspend();
    void   release();
	void   Delete() const { delete this; }
};

#endif