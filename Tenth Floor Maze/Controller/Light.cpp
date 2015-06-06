/* Light Implementation - Lighting Component - Model Branch
 *
 * Light.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iLighting.h"      // for the Lighting Interface
#include "iText.h"          // for the Text Interface
#include "iFrame.h"         // for the Frame Interface
#include "iDeviceLight.h"   // for the DeviceLight Interface
#include "iUtilities.h"     // for error()

#include "Light.h"          // for Light class declarations
#include "MathDefinitions.h"// for math functions in model coordinates
#include "ModelSettings.h"  // for LIGHT_POINT_0, _SPOT_0, _DISTANT_0

//-------------------------------- Light --------------------------------------
//
// The Light Primitive represents a light source in the Lighting Component
//
// The Lighting Coordinator manages the Light Instances
//
iLighting* Light::coordinator = NULL;

// CreateDistantLight creates a distant Light object, which implements the 
// Light Primitive
//
iLight* CreateDistantLight(Colour d, Colour a, Colour s, bool o) {

	return new Light(DIRECTIONAL_LIGHT, d, a, s, 0, o, 1, 0, 0);
}

// CreatePointLight creates a point Light object, which implements the 
// Light Primitive
//
iLight* CreatePointLight(Colour d, Colour a, Colour s, float r, bool o,
 float a0, float a1, float a2) {

	return new Light(POINT_LIGHT, d, a, s, r, o, a0, a1, a2);
}

iLight* Clone(const iLight* src) {

    return src->clone();
}

// constructor stores the properties of the light, creates the DeviceLight
// and initializes the reference time
//
Light::Light(LightType t, Colour d, Colour a, Colour s, float r, bool o, 
 float a0, float a1, float a2) : type(t), on(false), diffuse_(d), ambient_(a),
 specular_(s), range_(r), attenuation0(a0), attenuation1(a1), attenuation2(a2),
 turnOn(o), turnOff(false), frame(NULL), text(NULL) {

    if (!coordinator)
        error(L"Light::00 Couldn\'t access the Lighting Coordinator");
    else if(!coordinator->add(this))
        error(L"Light::01 Couldn\'t add the light to Lighting Coordinator");

    deviceLight = CreateDeviceLight();

	// reference time
	lastToggle  = 0;
}

// copy constructor initializes the deviceLight and copies over the
// instance variables from src
//
Light::Light(const Light& src) {

    if (!coordinator)
        error(L"Light::02 Couldn\'t access the Lighting Coordinator");
    else if(!coordinator->add(this))
        error(L"Light::03 Couldn\'t add the light to the Lighting Coordinator");

	deviceLight = NULL;
	*this = src;
}

// assignment operator discards the old deviceLight and copies over properties
// from src
//
Light& Light::operator=(const Light& src) {

	if (this != &src) {
        *((Frame*)this) = src;
		if (deviceLight) 
			deviceLight->Delete();
        if (src.deviceLight)
            deviceLight = src.deviceLight->clone();
        else
            deviceLight = NULL;
		type            = src.type;   
		on              = false;     
		turnOn          = src.on;    
		turnOff         = false;   
		diffuse_        = src.diffuse_;  
		ambient_        = src.ambient_;  
		specular_       = src.specular_;  
		range_          = src.range_;       
		attenuation0    = src.attenuation0; 
		attenuation1    = src.attenuation1;
		attenuation2    = src.attenuation2; 
		lastToggle      = 0;
        if (src.frame)
            integrate(src.frame);
        frame           = NULL;
		text            = NULL;   
	}

	return *this;
}

// attach attaches Frame *f to the light
//
void Light::attach(const iFrame* f) {

	frame = f;
}

// attach attaches Text *t to the light
//
void Light::attach(const iText* t) {

	text = t;
}

// restore reinitializes the time of the last toggle
//
void Light::restore(int now) {

	lastToggle = now;
}

// toggle toggles the state of the light if outside the latency period
// and returns the future state
//
bool Light::toggle(int now) {

	bool rc = on;

    if (now - lastToggle > LIGHT_LATENCY) {
		if (on)
			turnOff = true;
		else
			turnOn  = true;
		rc          = !rc;
        lastToggle  = now;
    }

	return rc;
}

// position returns the position of the Light in world space
//
Vector Light::position() const {

    Vector v;

    if (frame)
        v = Frame::position() * frame->world();
    else
        v = Frame::position();

    v.z *= MODEL_Z_AXIS;

    return v;
}

// orientation returs the heading of the Light in world space
//
Vector Light::orientation() const {

    Vector h;

    if (frame)
        h = Frame::orientation('z') * frame->rotation();
    else
        h = Frame::orientation('z');

    h.z *= MODEL_Z_AXIS;

    return h;
}

// update turns the device light on or off or updates its
// position and orientation
//
void Light::update() {

	if (turnOn) {
		const_cast<iDeviceLight*>(deviceLight)->turnOn(this);
		turnOn = false;
		on     = true;
	}
	else if (turnOff) {
		const_cast<iDeviceLight*>(deviceLight)->turnOff(this);
		turnOff = false;
		on      = false;
	}
    else if (on) {
		const_cast<iDeviceLight*>(deviceLight)->update(this);
    }
}

// report reports the text associated with the light
//
void Light::report(bool on) const {

	if (text)
		const_cast<iText*>(text)->set(on ? LGT_TXT_ON : LGT_TXT_OFF);
}

// suspend suspends the device light and prepares for turning on the light
// upon restoration
//
void Light::suspend() {

	if (deviceLight) 
		const_cast<iDeviceLight*>(deviceLight)->suspend(this);
	turnOn  = on || turnOn;
	turnOff = false;
}

// destructor deletes the light source from the lighting Component
//
Light::~Light() {

    if (coordinator)
        coordinator->remove(this);
    else
        error(L"Light::90 Couldn\'t access the Lighting Coordinator");
}

//-------------------------------- SpotLight ----------------------------------
//
// CreateSpotLight creates a spot Light object, which implements the 
// Light Primitive
//
iLight* CreateSpotLight(Colour d, Colour a, Colour s, float r, bool o, 
 float a0, float a1, float a2, float ph, float th, float f) {

	return new SpotLight(d, a, s, r, o, a0, a1, a2, ph, th, f);
}

// constructor stores the properties of the light, creates the DeviceLight
// and initializes the reference time
//
SpotLight::SpotLight(Colour d, Colour a, Colour s, float r, bool o, float a0, 
 float a1, float a2, float ph, float th, float f) : Light(SPOT_LIGHT, d, a, s,
 r, o, a0, a1, a2), phi(ph), theta(th), falloff(f) { }

// copy constructor calls base class constructor and copies the instance
// variables
//
SpotLight::SpotLight(const SpotLight& src) : Light(src) {

    *this = src;
}

// assignment operator assignment and copies instance
// variables
//
SpotLight& SpotLight::operator=(const SpotLight& src) {

    if (this != &src) {
        phi     = src.phi;
        theta   = src.theta;
        falloff = src.falloff;
    }

    return *this;
}
