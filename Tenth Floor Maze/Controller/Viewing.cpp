/* Viewing Implementation - Viewing Component - Model Branch
 *
 * Viewing.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"      // for the Context Interface
#include "iText.h"         // for the Text Interface

#include "Viewing.h"       // for the Viewing class declarations
#include "Camera.h"        // for Camera::isCoordinatedBy
#include "ModelSettings.h" // for CAMERA_SELECT, MODEL_LATENCY
#include "ModelSystem.h"   // for MODEL_Z_AXIS

//-------------------------------- Viewing -----------------------------------
//
// The Viewing Coordinator manages the viewpoints in the Viewing Component
//
// CreateViewing creates the Viewing object, which implements the Viewing 
// Coordinator
//
iViewing* CreateViewing(iContext* c) {

	return new Viewing(c);
}

// constructor initializes the pointers to the Camera objects and identifies
// the Viewing object as the coordinator of the Viewing Component
//
Viewing::Viewing(iContext* c) : context(c) {

    noCameras = 0;
	for (int i = 0; i < MAX_CAMERAS; i++)
        camera[i] = 0;

    // current camera
    current = 0;

    // pointers to the camera text items
    cameraPosition = NULL;
    cameraHeading  = NULL;

    // toggle and reference time
    lastUpdate = 0;
    lastToggle = 0;

	// manages the Camera class
	Camera::isCoordinatedBy(this);
}

// add adds a pointer to Camera *c within the Viewing Component and
// returns true if successful, false otherwise
//
bool Viewing::add(const iCamera* c) {

    int i;
    bool rc = false;

    for (i = 0; i < noCameras; i++)
        if (!camera[i]) {
            camera[i] = c;
            i = noCameras + 1;
            rc = true;
        }
    if (i == noCameras && noCameras < MAX_CAMERAS) {
        camera[noCameras++] = c;
        rc = true;
    }

    return rc;
}

// initialize sets the reference time
//
void Viewing::initialize(int now) {
	//RYAN: Removed by ryan.
	//CreateText(0.0f, 0.1f, 0.30f, 0.2f, TXT_DEFAULT, L" Camera: at ");
    //CreateText(0.50f, 0.1f, 0.70f, 0.2f, TXT_DEFAULT, L" heading ");
	//cameraPosition = CreateText(0.3f, 0.1f, 0.5f, 0.2f);
	//cameraHeading  = CreateText(0.73f, 0.1f, 0.95f, 0.2f);

    lastUpdate = now;
}

// reset resets the reference time
//
void Viewing::reset(int now) {

    lastUpdate = now;
}

// restore resets the reference time
//
void Viewing::restore(int now) {

    lastUpdate = now;
}

// update selects the current Camera object of the Viewing Component
// updates the current Camera 
//
void Viewing::update(int now) {

	// update the on/off state
	if (context->pressed(CAMERA_SELECT) && now - lastToggle > MODEL_LATENCY) {
        lastToggle = now;
        current++;
        if (current == noCameras)
            current = 0;
    }

    // update the current camera
    if (camera[current])
        const_cast<iCamera*>(camera[current])->update(now - lastUpdate);

    // reference time
    lastUpdate = now;

    // report camera text items
    if (camera[current])
        report();
}

// report creates the text strings for the current camera
//
void Viewing::report() const {

	wchar_t str[MAX_DESC + 1];
	if (cameraPosition)
		const_cast<iText*>(cameraPosition)->set(::position(str, camera[current]));
	if (cameraHeading)
		const_cast<iText*>(cameraHeading)->set(::heading(str, camera[current]));
}		

// remove removes the pointer to iCamera *l from the Viewing Component
// and returns true if successful, false otherwise
//
bool Viewing::remove(const iCamera* l) {

    bool rc = false;

    for (int i = 0; i < noCameras; i++)
        if (camera[i] == l) {
            camera[i] = 0;
            rc = true;
        }
    while (!camera[noCameras - 1])
        noCameras--;

    return rc;
}

// destructor deletes the Camera objects within the Viewing Component
//
Viewing::~Viewing() {

    for (int i = 0; i < noCameras; i++)
        if (camera[i])
            camera[i]->Delete();
}
