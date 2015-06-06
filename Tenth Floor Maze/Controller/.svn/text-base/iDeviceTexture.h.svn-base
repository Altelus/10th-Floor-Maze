#ifndef _I_DEVICE_TEXTURE_H_
#define _I_DEVICE_TEXTURE_H_

/* DeviceTexture Interface - GraphicsCard Component - Direct Device Branch
 *
 * iDeviceTexture.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */
//-------------------------------- iDeviceTexture -----------------------------
//
// iDeviceTexture is the Interface to the DeviceTexture Primitive of the
// Graphics Card Component
//
class iTexture;

class iDeviceTexture {
  public:
    virtual iDeviceTexture* clone() const                             = 0;
	// initialization functions
	virtual void setup(const iTexture* t, int w, int h, int c)        = 0;
	// execution functions
	virtual void attach(const iTexture* t, int i, unsigned flags)     = 0;
	virtual void detach(int i)                                        = 0;
	virtual void draw(const iTexture* t, float x, float y, float w, 
	 float h, unsigned char alpha)                                    = 0;
	virtual void draw(const iTexture* t, float x, float y, float w, 
		float h, unsigned char alpha, float percent)				  = 0;
	virtual void draw(const iTexture* t, float x, float y, float w, 
	 float h, unsigned char alpha, float l, float r, float tt, float b, float xMax, float yMax) =0;
	// termination functions
	virtual void suspend()                                            = 0;
	virtual void release()                                            = 0;
	virtual void Delete() const                                       = 0;
};

extern "C"
iDeviceTexture* CreateDeviceTexture();

#endif