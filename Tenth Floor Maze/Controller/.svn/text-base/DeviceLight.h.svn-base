#ifndef _DEVICE_LIGHT_H_
#define _DEVICE_LIGHT_H_

/* DeviceLight Declaration - GraphicsCard Component - Direct Device Branch
 *
 * DeviceLight.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iDeviceLight.h" // for the DeviceLight Interface

//-------------------------------- DeviceLight --------------------------------
//
// The DeviceLight Primitive implements a Light in the Graphics Card Component
//
class iDisplay;

class DeviceLight : public iDeviceLight {

	static iDisplay* display;   // points to the Display object

	int              index;     // identifier for this light
	bool             isSetup;   // this light has been setup?

	DeviceLight();
    DeviceLight(const DeviceLight&);

  public:
	friend iDeviceLight* CreateDeviceLight();
	static void connectsThrough(iDisplay* d) { display = d; }
    iDeviceLight* clone() const { return new DeviceLight(*this); }
    DeviceLight& operator=(const DeviceLight& src);
	// initialization functions
	bool   setup(const iLight* light);
	// execution functions
	void   turnOn(const iLight* light);
	void   update(const iLight* light);
	void   turnOff(const iLight* light);
	// termination functions
	void   suspend(const iLight* light);
	void   Delete() const { delete this; }
};

#endif