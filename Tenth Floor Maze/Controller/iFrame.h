#ifndef _I_FRAME_H_
#define _I_FRAME_H_

/* Frame Interface - Model Branch
 *
 * iFrame.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iFrame -------------------------------------
//
// iFrame is the Interface to the Frame Primitive of the Model Branch
//
struct Matrix;
struct Vector;

class iFrame {
  public:
    virtual void translate(float x, float y, float z) = 0;
    virtual void scale(float x, float y, float z)     = 0;
    virtual void rotatex(float rad)                   = 0;
    virtual void rotatey(float rad)                   = 0;
    virtual void rotatez(float rad)                   = 0;
    virtual Vector position() const                   = 0;
	virtual Matrix rotation() const                   = 0;
    virtual Vector orientation(char axis) const       = 0;
    virtual iFrame* integrate(const iFrame*)          = 0;
	virtual Matrix world() const                      = 0;
};

#endif
