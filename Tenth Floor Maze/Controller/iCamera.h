#ifndef _I_CAMERA_H_
#define _I_CAMERA_H_

/* Camera Interface - Camera Component - Model Branch
 *
 * iCamera.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "Frame.h" // for the Frame declaration

//-------------------------------- iCamera ------------------------------------
//
// iCamera is the Interface to the Camera Primitive of the Viewpoint Component
//
class iContext;

class iCamera : public Frame {
  public:
	// execution function
    virtual void update(int delta)     = 0;
    // initialization function
    virtual void attach(const iFrame*) = 0;
	// termination function
	virtual void Delete() const        = 0;
};

extern "C"
iCamera* CreateCamera(iContext* c);
//extern "C"
//iCamera* CreateCameraWithMap(iContext*, int[20][20], int);
//extern "C"
//iCamera* CreateFirstPersonCamera(iContext* c);
//extern "C"
//iCamera* CreateFirstPersonCameraWithMap(iContext*, int[20][20], int);

// reporting string functions
const wchar_t* position(wchar_t* str, const iCamera* camera);
const wchar_t* heading(wchar_t* str, const iCamera* camera);

#endif
