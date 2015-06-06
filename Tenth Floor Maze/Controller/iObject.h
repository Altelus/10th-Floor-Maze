#ifndef _I_OBJECT_H_
#define _I_OBJECT_H_

/* Object Interface - Scene Component - Model Branch
 *
 * iObject.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "Frame.h" // for the Frame class declaration

//-------------------------------- iObject ------------------------------------
//
// iObject is the Interface to the Object Primitive of the Scene Component
//
class  Box;
class  iTexture;
class  iSound;
class  iLight;
class  iCamera;
class  iText;
struct Colour;
enum   PrimitiveType;

class iObject : public Frame {
  public:
	// initialization functions
    virtual iObject* clone() const                                         = 0;
	virtual void attach(const iTexture* t, unsigned filter = 0)            = 0;
	virtual void attach(const iSound* s)                                   = 0;
	virtual void attach(const iLight* l)                                   = 0;
	virtual void attach(const iCamera* c)                                  = 0;
	virtual void attach(const iText* t, 
	 const wchar_t* (*data)(wchar_t* s, const iObject* object))            = 0;
	// execution functions
	virtual void draw(bool opaque) const                                   = 0;
	virtual Colour colour() const                                          = 0;
	virtual void report() const                                            = 0;
	// termination functions
	virtual void suspend() const                                           = 0;
    virtual void release() const                                           = 0;
	virtual void Delete() const                                            = 0;
};
//
///* RYAN */
//extern "C"
//iObject* CreateBoard(float minx, float minz, float maxx,  float maxz, float y, Colour c);

extern "C"
iObject* CreatePlayer(float minx, float miny, float minz, float maxx, float maxy, float maxz, Colour c);

extern "C"
iObject* CreateBox(float minx, float miny, float minz, float maxx, float maxy, float maxz, Colour c);
iObject* Clone(const iObject*);

extern "C"
iObject* CreateGrid(int min, int y, int max, int n, Colour clr);

extern "C"
iObject* CreateBillboard(float x, float y, float z, float xx, 
 float yy, Colour c);


// AKV - traps related
// AKV - added method to create a floor spike
extern "C"
iObject* CreateFloorSpike(float minx, float y, float minz, 
	 float maxx, float maxz, int numSpikes, float height, float damage, Colour c, bool includePadding = true);

enum ProjectileType;		// AKV

// AKV - added method to create a projectile
extern "C"
iObject* CreateProjectile(float minx, float miny, float minz, float maxx, float maxy,
				 float maxz, float amtDamage, Colour c, ProjectileType prjType);

// AKV - added method to create an atom
extern "C"
iObject* CreateAtom(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, float damage, Colour cBox, Colour cSpikes, ProjectileType embedPrjType, float boxPercentage);


// Text reporting functions for the Object Instance
const wchar_t* orientX(wchar_t* str, const iObject* object);
const wchar_t* orientY(wchar_t* str, const iObject* object);
const wchar_t* orientZ(wchar_t* str, const iObject* object);

// AKV - used for testing
const wchar_t* playerBoundryDetails(wchar_t* str, const iObject* object);

#endif
