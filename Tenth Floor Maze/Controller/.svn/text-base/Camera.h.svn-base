#ifndef _CAMERA_H_
#define _CAMERA_H_

/* Camera Declaration - Viewing Component - Model Branch
 *
 * Camera.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iCamera.h" // for the Camera Interface
#include "iText.h"
#include <windows.h>
//-------------------------------- Camera -------------------------------------
//
// The Camera Primitive represents a single viewpoint in the Viewing Component
//
class iViewing;

class Camera : public iCamera {

    static iViewing* coordinator; // points to the Viewing Object
    iContext*        context;     // points to the Context object
    const iFrame*    host;        // points to the host frame, if any
	
	/*float bumping_effect_coordinate; 
	float breathingEffectCoordinate;
	float breathing_effect_frequency;
	float breathing_effect_magnitude;
	int received_map[20][20];*/
	//int	tile_size;
	//float point_of_interest_y;
	/* RYAN:variable required to get the sine value 
			for the camera bumping effect. */  
	//iText* camera_text;

    Camera(iContext*);
	//Camera(iContext* c, int map[20][20], int) ;
	Camera(const Camera& c);            // prevents copying
	Camera& operator=(const Camera& c); // prevents assignment
    virtual ~Camera();

  public:
	friend iCamera* CreateCamera(iContext*);
	//friend iCamera* CreateCameraWithMap(iContext*, int[20][20], int);
	static void isCoordinatedBy(iViewing* viewing) { coordinator = viewing; }
    // initialization function
    void   attach(const iFrame*);
	// execution function
    void   update(int delta);
	// termination function
	void   Delete() const { delete this; }
};

#endif
