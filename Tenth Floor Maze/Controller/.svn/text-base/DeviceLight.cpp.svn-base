/* DeviceLight Implementation  - GraphicsCard Component - Direct Device Branch
 *
 * DeviceLight.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iLight.h"           // for the Light Interface
#include "iDisplay.h"         // for the Display Interface
#include "iUtilities.h"       // for error()

#include "DeviceLight.h"      // for the DeviceLight class declaration
#include "MathDeclarations.h" // for Matrix, Vector and Colour
#include "GraphicsPlatform.h" // for graphics api headers
#include "Configuration.h"    // for LightType enumeration  

//-------------------------------- DeviceLight --------------------------------
//
// The DeviceLight Primitive implements a light source in the Graphics Card 
// Component
//
// The Display object provides the API connectivity for the DeviceLight Objects
//
iDisplay* DeviceLight::display = NULL;
//
// CreateDeviceLight creates a DeviceLight object, which implements the 
// DeviceLight Primitive
//
iDeviceLight* CreateDeviceLight() {

	return new DeviceLight;
}

// constructor initializes the device light as needing to be setup
//
DeviceLight::DeviceLight() : isSetup(false), index(0) {}

// copy constructor

DeviceLight::DeviceLight(const DeviceLight& src) {

    *this = src;
}

DeviceLight& DeviceLight::operator=(const DeviceLight& src) {

    if (this != &src) {
        isSetup = false;
        index = 0;
    }

    return *this;
}

// setup finds an index for the device light and creates the
// device light using light's properties - returns true if
// successful, false otherwise
//
bool DeviceLight::setup(const iLight* light) {

	bool rc = false;

	// find an index for this device light and assign it
    index = display->getLightIndex();
	if (index == -1)
		error(L"DeviceLight::21 No more room for lights on this device");
	else {
		Colour d           = light->diffuse();
		Colour a           = light->ambient();
		Colour s           = light->specular();
		Vector spot        = light->spot();
		LightType type     = light->isType();
		Vector attenuation = light->attenuation();
		float  range       = light->range();
		Vector p           = light->position();
		Vector o           = light->orientation();

		D3DLIGHT9 d3dLight;
		ZeroMemory(&d3dLight, sizeof d3dLight);
		switch (type) {
		  case POINT_LIGHT:
			d3dLight.Type = D3DLIGHT_POINT;
			break;
		  case SPOT_LIGHT:
			d3dLight.Type = D3DLIGHT_SPOT;
			break;
		  case DIRECTIONAL_LIGHT:
			d3dLight.Type = D3DLIGHT_DIRECTIONAL;
			break;
		}
		d3dLight.Diffuse      = D3DXCOLOR(d.r, d.g, d.b, d.a);
		d3dLight.Ambient      = D3DXCOLOR(a.r, a.g, a.b, a.a);
		d3dLight.Specular     = D3DXCOLOR(s.r, s.g, s.b, s.a);
		d3dLight.Attenuation0 = attenuation.x;
		d3dLight.Attenuation1 = attenuation.y;
		d3dLight.Attenuation2 = attenuation.z;
		d3dLight.Phi          = spot.x;
		d3dLight.Theta        = spot.y;
		d3dLight.Falloff      = spot.z;
		d3dLight.Range        = range;
		d3dLight.Position     = D3DXVECTOR3(p.x, p.y, p.z);
		d3dLight.Direction    = D3DXVECTOR3(o.x, o.y, o.z);

		if (!display->device() || 
         FAILED(((LPDIRECT3DDEVICE9)display->device())->SetLight(index, &d3dLight)))
			error(L"DeviceLight::22 Failed to create device light");
		else
			rc = true;
	}

	return rc;
}

// turnOn sets up the device light if it needs to be setup,
// adjusts its position and orientation if it is mobile and
// turns on the device light 
//
void DeviceLight::turnOn(const iLight* light) {

	if (!isSetup) isSetup = setup(light);

	if (isSetup) {
		D3DLIGHT9 d3dLight;
		if (FAILED(((LPDIRECT3DDEVICE9)display->device())->GetLight(index,
            &d3dLight)))
			error(L"DeviceLight::23 Failed to find a device light");
		else {
			Vector p = light->position();
			Vector o = light->orientation();
			d3dLight.Position  = D3DXVECTOR3(p.x, p.y, p.z);
			d3dLight.Direction = D3DXVECTOR3(o.x, o.y, o.z);
			if (FAILED(((LPDIRECT3DDEVICE9)display->device())->SetLight(
                index, &d3dLight)))
				error(L"DeviceLight:24 Failed to update position");
		}
		((LPDIRECT3DDEVICE9)display->device())->LightEnable(index, true);
		
		// report the current state of the device light
		light->report(true);
	}
}

// update sets up the device light if it needs to be setup
// and adjusts its position and orientation 
//
void DeviceLight::update(const iLight* light) {

	if (!isSetup) isSetup = setup(light);

	if (isSetup) {
		D3DLIGHT9 d3dLight;
		if (FAILED(((LPDIRECT3DDEVICE9)display->device())->GetLight(index,
            &d3dLight)))
			error(L"DeviceLight::23 Failed to find a device light");
		else {
			Vector p = light->position();
			Vector o = light->orientation();
			d3dLight.Position  = D3DXVECTOR3(p.x, p.y, p.z);
			d3dLight.Direction = D3DXVECTOR3(o.x, o.y, o.z);
			if (FAILED(((LPDIRECT3DDEVICE9)display->device())->SetLight(
                index, &d3dLight)))
				error(L"DeviceLight:24 Failed to update position");
		}

		// report the current state of the device light
		light->report(true);
	}
}

// turnOff turns off the device light
//
void DeviceLight::turnOff(const iLight* light) {

    LPDIRECT3DDEVICE9 d3dd = (LPDIRECT3DDEVICE9)display->device();
    if (d3dd)
        d3dd->LightEnable(index, false);

	// report the current state of the device light
	light->report(false);
}

// suspend turns off the device light and makes its index available
// for restoration
//
void DeviceLight::suspend(const iLight* light) {

    LPDIRECT3DDEVICE9 d3dd = (LPDIRECT3DDEVICE9)display->device();
    if (d3dd)
        d3dd->LightEnable(index, false);
	
	// report the current state of the device light
	light->report(false);

	if (isSetup) {
		display->releaseLightIndex(index);
		isSetup = false;
	}
}
