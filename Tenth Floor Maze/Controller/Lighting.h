#ifndef _LIGHTING_H_
#define _LIGHTING_H_

/* Lighting Declaration - Lighting Component - Model Branch
 *
 * Lighting.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iLighting.h"        // for the Lighting Interface
#include "MathDeclarations.h" // for Vector, Colour

//-------------------------------- Lighting -----------------------------------
//
// The Lighting Coordinator manages the light sources in the Lighting Component 
//
class Lighting : public iLighting {

	static const int MAX_LIGHTS = 8;

	iContext*     context;            // points to the Context object

	int           noLights;           // number of lights
    int           maxLights;          // maximum number of lights
    const iLight* source[MAX_LIGHTS]; // points to the light sources

    Lighting(iContext*);
	Lighting(const Lighting& l);            // prevents copying
    Lighting& operator=(const Lighting& l); // prevents assignment
    virtual ~Lighting();

  public:
	friend iLighting* CreateLighting(iContext*);
    // initialization functions
    bool   add(const iLight*);
	void   restore(int now);
	// execution function
	void   update() const;
	// termination functions
	void   suspend() const;
    bool   remove(const iLight*);
	void   Delete() const { delete this; }
};

#endif
