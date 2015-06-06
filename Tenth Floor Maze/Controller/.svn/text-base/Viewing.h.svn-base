#ifndef _VIEWERS_H_
#define _VIEWERS_H_

/* Viewing Declaration - Viewing Component - Model Branch
 *
 * Viewing.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iViewing.h" // for the Viewing Interface

//-------------------------------- Viewing ------------------------------------
//
// The Viewing Coordinator manages the Cameras in the Viewing Component 
//
class iText;

class Viewing : public iViewing {

	static const int MAX_CAMERAS = 8;

	iContext*      context;             // points to the Context object

	int            noCameras;           // number of cameras
    int            current;             // index of current camera
    const iCamera* camera[MAX_CAMERAS]; // points to the cameras

    iText*         cameraPosition;      // describes current viewpoint
    iText*         cameraHeading;       // describes current heading

    int            lastToggle;          // time of most recent toggle
    int            lastUpdate;          // reference time

    Viewing(iContext*);
	Viewing(const Viewing& l);            // prevents copying
    Viewing& operator=(const Viewing& l); // prevents assignment
    virtual ~Viewing();

  public:
	friend iViewing* CreateViewing(iContext*);
    // initialization functions
    bool   add(const iCamera*);
    void   initialize(int now);
    void   reset(int now);
	void   restore(int now);
	// execution functions
	void   update(int now);
	void   report() const;
	// termination functions
    bool   remove(const iCamera*);
	void   Delete() const { delete this; }
};

#endif
