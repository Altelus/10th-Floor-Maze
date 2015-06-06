/* Lighting Implementation - Lighting Component - Model Branch
 *
 * Lighting.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"   // for the Context Interface

#include "Lighting.h"   // for the Lighting class declarations
#include "Light.h"      // for Light::isCoordinatedBy

//-------------------------------- Lighting -----------------------------------
//
// The Lighting Coordinator manages the light sources in Lighting Component
//
// CreateLighting creates the Lighting object, which implements the Lighting 
// Coordinator
//
iLighting* CreateLighting(iContext* c) {

	return new Lighting(c);
}

// constructor initializes the pointers to the Light objects and identifies
// the Lighting object as the coordinator of the Light class
//
Lighting::Lighting(iContext* c) : context(c) {

    noLights = 0;
	for (int i = 0; i < MAX_LIGHTS; i++)
        source[i] = 0;

	// manages the Light class
	Light::isCoordinatedBy(this);
}

// add adds a pointer to Light *l withi the lighting Component and
// returns true if successful, false otherwise
//
bool Lighting::add(const iLight* l) {

    int i;
    bool rc = false;

    for (i = 0; i < noLights; i++)
        if (!source[i]) {
            source[i] = l;
            i = noLights + 1;
            rc = true;
        }
    if (i == noLights && noLights < MAX_LIGHTS) {
        source[noLights++] = l;
        rc = true;
    }

    return rc;
}

// restore restores each Light object of the Lighting Component
//
void Lighting::restore(int now) {

	for (int i = 0; i < noLights; i++)
		if (source[i])
			const_cast<iLight*>(source[i])->restore(now);
}

// update updates the Light objects of the Lighting Component 
//
void Lighting::update() const {

	for (int i = 0; i < noLights; i++)
		if (source[i])
			const_cast<iLight*>(source[i])->update();
}

// suspend suspends each Light object of the Lighting Component
//
void Lighting::suspend() const {

	for (int i = 0; i < noLights; i++)
		if (source[i])
			const_cast<iLight*>(source[i])->suspend();
}

// remove removes the pointer to iLight *l from the lighting Component
// and returns true if successful, false otherwise
//
bool Lighting::remove(const iLight* l) {

    bool rc = false;

    for (int i = 0; i < noLights; i++)
        if (source[i] == l) {
            source[i] = 0;
            rc = true;
        }
    while (!source[noLights - 1])
        noLights--;

    return rc;
}

// destructor deletes the Light objects within the Lighting Component
//
Lighting::~Lighting() {

    for (int i = 0; i < noLights; i++)
        if (source[i])
            source[i]->Delete();
}
