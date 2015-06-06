#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

/* Graphic Declaration - GraphicsCard Component - Direct Device Branch
 *
 * Graphic.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iGraphic.h"         // for the Graphic Interface
#include "GraphicsPlatform.h" // for graphics api headers

//-------------------------------- Graphic ------------------------------------
//
// The Graphic Primitive implements an Object in the Graphics Card Component
//
class iDisplay;
class iVertexList;

class Graphic : public iGraphic {

	static iDisplay* display;   // points to the Display object

    iVertexList*  vertexList;   // points to the vertex list

	int  vertexSize;            // size of a single vertex
	int  vertexBufferSize;      // size of the vertex buffer
    LPDIRECT3DVERTEXBUFFER9 vb; // points to the vertex buffer
    D3DPRIMITIVETYPE type;      // primitive type
    D3DMATERIAL9 mat;           // material reflectivity
    int nPrimitives;            // number of primitives

    Graphic(PrimitiveType t, int np);
    virtual ~Graphic();

	bool setup(const iObject* object);

  public:
	friend iGraphic* CreateGraphic(PrimitiveType t, int np);
	static void connectsThrough(iDisplay* d) { display = d; }
    Graphic(const Graphic& v);            
    Graphic& operator=(const Graphic& v); 
    iGraphic* clone() const { return new Graphic(*this); }
    // initialization functions
    void   add(float, float, float, float, float, float, float, float);
    void   add(Vector p1, Vector p2, Vector p3, Vector p4, Vector n);
	// execution function
    void   draw(const iObject* object, const iTexture* t, unsigned f);
	// termination functions
    void   suspend();
    void   release();
	void   Delete() const { delete this; }
};

#endif