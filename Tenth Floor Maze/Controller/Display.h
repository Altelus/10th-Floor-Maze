#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/* Display Declaration - GraphicsCard Component - Direct Device Branch
 *
 * Display.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iDisplay.h"         // for the Display Interface
#include "GraphicsPlatform.h" // for graphics api headers

//-------------------------------- Display ------------------------------------
//
// The Display Portal manages the API connectivity for the Graphics Card 
// Component
//
class Display : public iDisplay {

	iContext* context;   // points to the Context object
	HWND  hwnd;          // points to the main application window

    // available configuration dimensions
    int   (*modeDim)[2]; // points to list of available mode widths, heights

    // selected configuration
    int   display;       // display adapter identifier
    int   mode;          // resolution mode identifier
    int   pixel;         // pixel format identifier
    int   width_;        // width of the backbuffer
    int   height_;       // height of the backbuffer
	float aspect;        // aspect ratio of viewing area
    int   maxLights;     // max no of lights supported by selected adapter
	bool  runInWindow;   // run in resizeable windowed mode
    bool* lightIndex;    // list of available device lights
	bool  fogEnabled;    //GMOK: fog is enabled

    LPDIRECT3D9 d3d;             // Interface to the Direct3D object
    LPDIRECT3DDEVICE9 d3dd;      // Interface to Direct3D display device
    D3DPRESENT_PARAMETERS d3dpp; // parameters for creating/restoring D3D
                                 // display device
    LPD3DXSPRITE spriteManager_; // Interface to the sprite manager object

    void setupProjection();      // sets up the projection matrix
    void setupLighting();        // sets up the lighting
	void setupBlending();        // sets up the alpha blending

    Display(iContext*);
	Display(const Display& d);            // prevents copying
	Display& operator=(const Display& d); // prevents assignments
    virtual ~Display();

  public:
	friend iDisplay* CreateDisplay(iContext*);
	// configuration functions
	bool   interrogate(void*);
    void   setConfiguration();
	// initialization functions
    bool   setup(void*);
    int    getLightIndex();
    bool   restore();
	// execution functions
    void   beginDraw();
    void   alphaBlendOn();
    void   alphaBlendOff();
    void   beginSuperimpose();
    void   endDraw();
    void*  device() const; 
    int    width() const         { return width_; }
    int    height() const        { return height_; }
    void*  spriteManager() const;
    void   resize();
	void   toggleFog(bool fe);
	void   setFogColor(unsigned long c);
	void   setFogStartEnd(float s, float e);
	// termination functions
    void   suspend();
    void   releaseLightIndex(int i) { lightIndex[i] = false; }
    void   release();
	void   Delete() { delete this; }
};

#endif