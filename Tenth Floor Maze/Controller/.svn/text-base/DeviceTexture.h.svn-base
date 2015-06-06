#ifndef _DEVICE_TEXTURE_H_
#define _DEVICE_TEXTURE_H_

/* DeviceTexture Declaration - GraphicsCard Component - Direct Device Branch
 *
 * DeviceTexture.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iDeviceTexture.h"   // for the DeviceTexture Interface
#include "GraphicsPlatform.h" // for graphics api headers

//-------------------------------- DeviceTexture ------------------------------
//
// The DeviceTexture Primitive implements a Texture in the Graphics Card
// Component
//
class iDisplay;

class DeviceTexture : public iDeviceTexture {

	static iDisplay* display; // points to the Display object

    LPDIRECT3DTEXTURE9 tex;   // texture stored on the graphics card

	DeviceTexture();
	virtual ~DeviceTexture();

	void setSamplerState(int i, unsigned flags) const;
	void setup(const iTexture* t, int w, int h, int c);

  public:
	friend iDeviceTexture* CreateDeviceTexture();
	static void connectsThrough(iDisplay* d) { display = d; }
	DeviceTexture(const DeviceTexture&);
	DeviceTexture& operator=(const DeviceTexture&);
    iDeviceTexture* clone() const { return new DeviceTexture(*this); }
	// execution functions
	void   attach(const iTexture* t, int i, unsigned flags);
	void   detach(int i);
	void   draw(const iTexture* t, float x, float y, float w, float h, 
		    unsigned char alpha);
	void draw(const iTexture* t, float x, float y, float w, 
		float h, unsigned char alpha, float percent);
	void draw(const iTexture* t, float x, float y, float w, 
		float h, unsigned char alpha, float l, float r, float tt, float b, float xMax, float yMax);
	// termination functions
	void   suspend();
    void   release();
	void   Delete() const { delete this; }
};

#endif