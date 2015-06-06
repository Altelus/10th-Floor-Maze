#ifndef _MATH_DECLARATIONS_H_
#define _MATH_DECLARATIONS_H_

/* Declarations of the Mathematical Structures
 *
 * MathDeclarations.h
 * gam666/dps901
 * fwk4gps version 1.0
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- Vector --------------------------------
//
struct Matrix;

struct Vector {
    float x;
    float y;
    float z;
    Vector() : x(0), y(0), z(0) {}
    Vector(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
    Vector  operator+();
    Vector  operator-();
    Vector& operator+=(const Vector& a);
    Vector& operator-=(const Vector& a);
    Vector  operator*(const Matrix& m);
    Vector  operator*(const Matrix& m) const;
    Vector  operator*=(const Matrix& m);
    float   length() const;
};

//------------------------------- Matrix --------------------------------
//
struct Matrix {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
    Matrix() : m11(0), m12(0), m13(0), m14(0),
               m21(0), m22(0), m23(0), m24(0),
               m31(0), m32(0), m33(0), m34(0),
               m41(0), m42(0), m43(0), m44(0) {}
    Matrix(float x) : m11(x), m12(0), m13(0), m14(0),
                      m21(0), m22(x), m23(0), m24(0),
                      m31(0), m32(0), m33(x), m34(0),
                      m41(0), m42(0), m43(0), m44(1) {}
    Matrix(const Vector& v) : m11(v.x), m12(0), m13(0), m14(0),
                              m21(0), m22(v.y), m23(0), m24(0),
                              m31(0), m32(0), m33(v.z), m34(0),
                              m41(0), m42(0), m43(0), m44(1) {}
    Matrix(float i11, float i12, float i13, float i14,
           float i21, float i22, float i23, float i24,
           float i31, float i32, float i33, float i34,
           float i41, float i42, float i43, float i44) :
               m11(i11), m12(i12), m13(i13), m14(i14),
               m21(i21), m22(i22), m23(i23), m24(i24),
               m31(i31), m32(i32), m33(i33), m34(i34),
               m41(i41), m42(i42), m43(i43), m44(i44) {}
    Matrix& isIdentity();
    Matrix& operator+=(const Matrix& a);
    Matrix& operator-=(const Matrix& a);
    Matrix& operator*=(const Matrix& m);
    Matrix  transpose() const;
	Matrix& translate(float x, float y, float z);
	Matrix& rotatex(float rad);
	Matrix& rotatey(float rad);
	Matrix& rotatez(float rad);
	Matrix& rotate(const Matrix& rot);
	Matrix& scale(float sx, float sy, float sz);
	Matrix& orient(const Matrix& rot);
	Vector  position() const;
	Matrix  rotation() const;
	Vector  direction(const Vector& v) const;
	Vector  direction(char c) const;
};

//-------------------------------- Colour --------------------------------
//
struct Colour {
    float r;
    float g;
    float b;
    float a;
    Colour(float red = 0, float grn = 0, float blu = 0, float alp = 1) :
	 r(red), g(grn), b(blu), a(alp) {}
    operator const float* () const { return &r; }
};

#endif
