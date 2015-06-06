/* Graphic Implementation- GraphicsCard Component - Direct Device Branch
 *
 * Graphic.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iTexture.h"        // for the Texture Interface
#include "iDisplay.h"        // for the Display Interface
#include "iObject.h"         // for the Object Interface
#include "iVertexList.h"     // for the VertexList Interface
#include "iUtilities.h"      // for error()

#include "Graphic.h"         // for Graphic class declaration
#include "MathDefinitions.h" // for Matrix, Vector and Colour
#include "Configuration.h"   // for Display settings  

//-------------------------------- Graphic ------------------------------------
//
// The Graphic Primitive represents an object in the Graphics Card Component
//
// The Display object provides the API connectivity for the Graphic Primitives
//
iDisplay* Graphic::display = NULL; 

// CreateGraphic creates a Graphic object, which implements the Graphic Primitive
// with np primitives
//
iGraphic* CreateGraphic(PrimitiveType pType, int np) {

	return new Graphic(pType, np);
}

// constructor initializes the instance variables
//
Graphic::Graphic(PrimitiveType pType, int np) {

	// calculate number of vertices
	int nv;
    switch (pType) {
        case POINT_LIST:     nv = np;     break;
        case LINE_LIST:      nv = 2 * np; break;
        case LINE_STRIP:     nv = np + 1; break;
        case TRIANGLE_LIST:  nv = 3 * np; break;
        case TRIANGLE_STRIP: nv = np + 2; break;
        case TRIANGLE_FAN:   nv = np + 1; break;
        default: nv = np;
    }
    vertexList = CreateVertexList(nv);

	switch (pType) {
        case POINT_LIST    : type = D3DPT_POINTLIST;     break;
        case LINE_LIST     : type = D3DPT_LINELIST;      break;
        case LINE_STRIP    : type = D3DPT_LINESTRIP;     break;
        case TRIANGLE_LIST : type = D3DPT_TRIANGLELIST;  break;
        case TRIANGLE_STRIP: type = D3DPT_TRIANGLESTRIP; break;
        case TRIANGLE_FAN  : type = D3DPT_TRIANGLEFAN;   break;
        default            : type = D3DPT_POINTLIST;
    }
    nPrimitives      = np;
	vertexSize       = 0;
	vertexBufferSize = 0;
    vb = NULL;
}

Graphic::Graphic(const Graphic& src) {

    vertexList = NULL;
    *this = src;
}

Graphic& Graphic::operator=(const Graphic& src) {

    if (this != &src) {
        if (vertexList)
            vertexList->Delete();
        if (src.vertexList)
            vertexList = src.vertexList->clone();
        else
            vertexList = NULL;
        type             = src.type;
        nPrimitives      = src.nPrimitives;
	    vertexSize       = src.vertexSize;
	    vertexBufferSize = src.vertexBufferSize;
        vb               = NULL;
    }

    return *this;
}

// add adds a vertex to the vertexList of the set of graphics primitives
//
void Graphic::add(float x, float y, float z, float nx, float ny, float nz,
 float u, float v) {

     vertexList->add(x, y, z, nx, ny, nz, u, v);
}

// add adds a quadrilateral [p1, p2, p3, p4] to the vertexList of the 
// set of graphics primitives
//
void Graphic::add(Vector p1, Vector p2, Vector p3, Vector p4, Vector n) {

    vertexList->add(p1, p2, p3, p4, n);
}

// setup stores the primitive and vertex data, the material reflectivity, and
// creates and populates the vertex buffer
//
bool Graphic::setup(const iObject* object) {

    bool rc = true;
    Colour c = object->colour();

	// make a shiny material of the specified color
    ZeroMemory(&mat, sizeof(mat));
    mat.Ambient  = D3DXCOLOR(c.r*0.7f, c.g*0.7f, c.b*0.7f, c.a);
    mat.Diffuse  = D3DXCOLOR(c.r, c.g, c.b, c.a); // reflected from lights
    mat.Specular = D3DXCOLOR(1, 1, 1, c.a);       // shine from lights
    mat.Power    = 100; // 0 if it shouldn't be shiny

	// create the vertex buffer
    vertexSize       = vertexList->vertexSize();
	vertexBufferSize = vertexList->noVertices() * vertexSize;
    unsigned fvf     = vertexList->vertexFormat();
    ((LPDIRECT3DDEVICE9)display->device())->SetFVF(fvf);
    if (FAILED(((LPDIRECT3DDEVICE9)display->device())->CreateVertexBuffer(
     vertexBufferSize, 0, fvf, D3DPOOL_DEFAULT, &vb, NULL))) {
         error(L"Graphic::10 Couldn\'t create the vertex buffer");
        vb = NULL;
        rc = false;
    }

    // populate the newly created Vertex Buffer
    if (vb) {
        void* pv;
        if (SUCCEEDED(vb->Lock(0, vertexBufferSize, (void**)&pv, 0)))
            vertexList->populate(pv);
        vb->Unlock();
    }
    else
        rc = false;

    return rc;
}

// draw draws the set of graphics primitives using the object's world
// transformation and reflected colour, along with the object's texture
//
void Graphic::draw(const iObject* object, const iTexture* texture, 
 unsigned flags) {

    // if just created, setup first
    if (!vb) setup(object);

    if (vb) {
        ((LPDIRECT3DDEVICE9)display->device())->SetTransform(D3DTS_WORLD, 
		 (D3DXMATRIX*)(&object->world()));
        ((LPDIRECT3DDEVICE9)display->device())->SetStreamSource(0, vb, 0, vertexSize);
        ((LPDIRECT3DDEVICE9)display->device())->SetMaterial(&mat);
		if (texture)
			texture->attach(0, flags);
        ((LPDIRECT3DDEVICE9)display->device())->DrawPrimitive(type, 0, nPrimitives);
		if (texture)
			texture->detach(0);
    }

    // report the object
    object->report();
}

// suspend releases the vertex buffer for the graphic element
//
void Graphic::suspend() {

    // release the Interface to the vertex buffer
    if (vb) {
        vb->Release();
        vb = NULL;
    }
}

// release suspends the graphic representation
//
void Graphic::release() {

    suspend();
}

// destructor releases the graphic representation and deletes the vertex list 
//
Graphic::~Graphic() {

    release();

    if (vertexList)
        vertexList->Delete();
}
