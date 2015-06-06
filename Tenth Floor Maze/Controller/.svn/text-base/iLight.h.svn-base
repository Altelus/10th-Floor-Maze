#ifndef _I_LIGHT_H_
#define _I_LIGHT_H_

/* Light Interface - Lighting Component - Model Branch
 *
 * iLight.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "Frame.h" // for the Frame class declaration

//-------------------------------- iLight -------------------------------------
//
// iLight is the Interface to the Light Primitive of the Lighting Component
//
enum   LightType;
struct Vector;
struct Colour;
class  iText;

class iLight : public Frame {
  public:
    virtual iLight*   clone() const         = 0;
	// initialization functions
	virtual void      attach(const iFrame*) = 0;
	virtual void      attach(const iText*)  = 0;
	virtual void      restore(int now)      = 0;
	// execution functions
	virtual LightType isType() const        = 0;
	virtual Colour    diffuse() const       = 0;
	virtual Colour    ambient() const       = 0;
	virtual Colour    specular() const      = 0;
	virtual float     range() const         = 0;
	virtual Vector    attenuation() const   = 0;
	virtual Vector    spot() const          = 0;
    virtual Vector    position() const      = 0;
    virtual Vector    orientation() const   = 0;
	virtual bool      toggle(int now)       = 0;
	virtual void      update()              = 0;
	virtual void      report(bool on) const = 0;
	// termination functions
	virtual void      suspend()             = 0;
	virtual void      Delete() const        = 0;
};

extern "C"
iLight* CreateDistantLight(Colour, Colour, Colour, bool = true);

extern "C"
iLight* CreatePointLight(Colour, Colour, Colour, float, bool, float = 1, 
 float = 0, float = 0);

extern "C"
iLight* CreateSpotLight(Colour, Colour, Colour, float, bool, float = 1, 
 float = 0, float = 0, float = 0, float = 0, float = 0);

iLight* Clone(const iLight*);

#endif
