/* Frame Implementation - Model Branch
 *
 * Frame.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * Chris Szalwinski
 */

#include "Frame.h"           // for the Frame class declaration
#include "MathDefinitions.h" // for position, rotation

//-------------------------------- Frame --------------------------------------
//
// The Frame object represents a reference frame in the Model Branch
//
Frame::Frame() : T(1) {}

// position returns the position of the Frame in world space
//
Vector Frame::position() const {

	return ::position(T);
}

// world returns the homogeneous transformation of the Frame corrected for
// the coordinate system of the model - this is the transformation passed
// to the direct device api level
//
Matrix Frame::world() const {

    return Matrix(T.m11, T.m12, T.m13, T.m14,
                  T.m21, T.m22, T.m23, T.m24,
                  T.m31, T.m32, T.m33, T.m34,
                  T.m41, T.m42, T.m43 * MODEL_Z_AXIS, 1);
}

// rotation returns the orientation of the Frame in world space
//
Matrix Frame::rotation() const {

	return ::rotation(T);
}

// integrate transforms T to include f.T
//
iFrame* Frame::integrate(const iFrame* f) {

    Matrix rot = f->rotation();
    T.rotate(rot);
    Vector pos = f->position();
    T.translate(pos.x, pos.y, pos.z);

    return this;
}
