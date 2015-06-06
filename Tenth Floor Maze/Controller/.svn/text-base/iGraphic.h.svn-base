#ifndef _I_GRAPHIC_H_
#define _I_GRAPHIC_H_

/* Graphic Interface - GraphicsCard Component - Direct Device Branch
 *
 * iGraphic.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iGraphic -----------------------------------
//
// iGraphic is the Interface to the Graphic Primitive of the Graphics Card 
// Component
//
class  iObject;
class  iTexture;
class  iVertexList;
struct Vector;
enum   PrimitiveType;

class iGraphic {
  public:
    virtual iGraphic* clone() const                                    = 0;
	// initialization functions
    virtual void add(float, float, float, float, float, float, float   = 0, 
     float = 0)                                                        = 0;
    virtual void add(Vector, Vector, Vector, Vector, Vector)           = 0;
    virtual bool setup(const iObject* object)                          = 0;
	// execution functions
    virtual void draw(const iObject* o, const iTexture* t, unsigned f) = 0;
	// termination functions
    virtual void suspend()                                             = 0;
    virtual void release()                                             = 0;
	virtual void Delete() const                                        = 0;
};

extern "C"
iGraphic* CreateGraphic(PrimitiveType t, int np);

#endif