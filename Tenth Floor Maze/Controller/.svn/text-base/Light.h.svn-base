#ifndef _LIGHT_H_
#define _LIGHT_H_

/* Light Declaration - Lighting Component - Model Branch
 *
 * Light.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iLight.h"           // for the Light Interface
#include "MathDeclarations.h" // for Vector, Colour

//-------------------------------- Light --------------------------------------
//
// The Light Primitive describes a light source in the Lighting Component
//
class iLighting;
class iDeviceLight;

class Light : public iLight {

    static iLighting*   coordinator;  // points to the lighting coordinator

	const iDeviceLight* deviceLight;  // points to the device light
    const iFrame*       frame;        // points to the host frame, if any
	const iText*        text;         // points to the attached text, if any

    LightType           type;         // light type
	bool                on;           // light is on?
	bool                turnOn;       // turn on the light?
	bool                turnOff;      // turn off the light?
    Colour              diffuse_;     // diffuse Component
    Colour              ambient_;     // ambient Component
    Colour              specular_;    // specular Component
    float               range_;       // beyond which light ceases
    float               attenuation0; // constant attenuation
    float               attenuation1; // linear attenuation
    float               attenuation2; // quadratic attenuation

    int                 lastToggle;   // time of the last toogle

  protected:
    Light(LightType t, Colour d, Colour a, Colour s, float r, bool, float a0, 
	 float a1, float a2);
	Light(const Light&);
	virtual ~Light();

  public:
	friend iLight* CreatePointLight(Colour d, Colour a, Colour s, float r, 
	 bool o, float a0, float a1, float a2);
	friend iLight* CreateDistantLight(Colour d, Colour a, Colour s, bool o);
	static    void isCoordinatedBy(iLighting* lighting) { coordinator = lighting; }
	Light& operator=(const Light&);
    iLight*   clone() const { return new Light(*this); }
	// initialization functions
	void      attach(const iFrame* f);
	void      attach(const iText*);
	void      restore(int now);
	// execution functions
	LightType isType() const      { return type; }
   	Colour    diffuse() const     { return diffuse_; }
	Colour    ambient() const     { return ambient_; }
	Colour    specular() const    { return specular_; }
	float     range() const       { return range_; }
	Vector    spot() const        { return Vector(0, 0, 0);}
	Vector    attenuation() const { return Vector(attenuation0, 
		       attenuation1, attenuation2); }
    Vector    position() const;
    Vector    orientation() const;
	bool      toggle(int now);
	void      update();
	void      report(bool on) const;
	// termination functions
	void      suspend();
	void      Delete() const { delete this; }
};

class SpotLight : public Light {

    float  phi;          // angle of spot light in radians
    float  theta;        // angle of inner spot in radians
    float  falloff;      // falloff factor [0,1]

	SpotLight(Colour d, Colour a, Colour s, float r, bool o, float a0, 
	 float a1, float a2, float ph, float th, float f);
    SpotLight(const SpotLight&);

  public:
    friend iLight* CreateSpotLight(Colour d, Colour a, Colour s, float r, 
    bool o, float a0, float a1, float a2, float ph, float th, float f);
    SpotLight& operator=(const SpotLight& src);
    iLight* clone() const { return new SpotLight(*this); }
	Vector  spot() const { return Vector(phi, theta, falloff);}
};

#endif
