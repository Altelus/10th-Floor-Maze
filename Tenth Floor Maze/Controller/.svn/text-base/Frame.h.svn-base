#ifndef _FRAME_H_
#define _FRAME_H_

/* Frame Declaration - Frame Component - Model Branch
 *
 * Frame.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iFrame.h"           // for the Frame Interface
#include "MathDeclarations.h" // for Matrix

//-------------------------------- Frame --------------------------------------
//
// The Frame class represents a reference frame in the Model branch
//
class Frame : public iFrame {

    Matrix T; // relative transformation matrix wrt world space

  public:
    Frame();
	void    scale(float sx, float sy, float sz)  { T.scale(sx, sy, sz); }
	void    rotatex(float rad)                   { T.rotatex(rad); }
    void    rotatey(float rad)                   { T.rotatey(rad); }
    void    rotatez(float rad)                   { T.rotatez(rad); }
	void    translate(float x, float y, float z) { T.translate(x, y, z); }
    void    orient(const Matrix& rot)
	//GMOK: For billboarding (used to orient a object to face the specified object matrix)
	{ T.orient(rot);}
    iFrame* integrate(const iFrame*);
    Vector  position() const;
    Matrix  rotation() const;
	Vector  orientation(const Vector& v) const   { return T.direction(v); }
	Vector  orientation(char c) const            { return T.direction(c); }
    Matrix  world() const;
    virtual ~Frame() {}
};

#endif