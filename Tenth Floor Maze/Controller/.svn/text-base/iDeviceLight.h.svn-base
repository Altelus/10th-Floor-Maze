#ifndef _I_DEVICE_LIGHT_H_
#define _I_DEVICE_LIGHT_H_

/* Device Light Interface - GraphicsCard Component - Direct Device Branch
 *
 * iDeviceLight.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iDeviceLight -------------------------------
//
// iDeviceLight is the Interface to the DeviceLight Primitive of the Graphics 
// Card Component
//
class  iLight;

class iDeviceLight {
  public:
    virtual iDeviceLight* clone() const   = 0;
	// initialization functions
    virtual bool setup(const iLight* l)   = 0;
	// execution functions
	virtual void turnOn(const iLight* l)  = 0;
	virtual void update(const iLight* l)  = 0;
	virtual void turnOff(const iLight* l) = 0;
	// termination functions
	virtual void suspend(const iLight* l) = 0;
	virtual void Delete() const           = 0;
};

extern "C"
iDeviceLight* CreateDeviceLight();

#endif