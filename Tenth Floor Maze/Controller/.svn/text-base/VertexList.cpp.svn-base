/* VertexList Implementation - GraphicsCard Component - Direct Device Branch
 *
 * VertexList.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iUtilities.h"      // for error()

#include "VertexList.h"      // for the Vertex, VertexList class declarations
#include "MathDefinitions.h" // for Vector and MODEL_Z_AXIS
#include "GraphicsPlatform.h" // for NULL and D3D..

//-------------------------------- Vertex -------------------------------------
//
// Vertex holds the data for a single vertex of the VertexList object
//
// constructor initializes the vertex to the values received
//
Vertex::Vertex(float xx, float yy, float zz, float nxx, float nyy, 
 float nzz, float ttu, float ttv) : x(xx), y(yy), z(zz), nx(nxx), ny(nyy), 
 nz(nzz), tu(ttu), tv(ttv) {}


//-------------------------------- VertexList ---------------------------------
//
// The VertexList object holds the vertex data for a Graphic object
//
// CreateVertexList creates a VertexList object, which implements the 
// VertexList Primitive
//
iVertexList* CreateVertexList(int n) {

    return new VertexList(n);
}

// constructor initializes instance variables in preparation for the creation
// of the vertex list
//
VertexList::VertexList(int n) {

    if (n <= 0) {
        error(L"VertexList::01 Invalid number of vertices");
        vertex = NULL;
        no     = 0;
    }
    else {
        vertex = new Vertex[n];
        no     = n;
    }
    next = 0;
}

// copy constructor calls assignment operator
//
VertexList::VertexList(const VertexList& src) {

    vertex = NULL;
    *this  = src;
}

// assignment operator
//
VertexList& VertexList::operator=(const VertexList& src) {

    if (this != &src) {
        if (vertex)
            delete [] vertex;
        if (src.no) {
            vertex = new Vertex[src.no];
            for (int i = 0; i < src.no; i++)
                vertex[i] = src.vertex[i];
        }
        else
            vertex = NULL;
        no   = src.no;
        next = src.next;
    }

    return *this;
}

// add adds one vertex to the vertex list
//
void VertexList::add(float x, float y, float z, float nx, float ny, float nz, 
 float u, float v) {

    if (next >= no)
        error(L"VertexList::10 Vertex list memory is full");
    else if (!vertex)
        error(L"VertexList::11 Vertex memory not allocated");
    else {
        #if MODEL_Z_AXIS == NEAR_TO_FAR
        vertex[next++] = Vertex(x, y, z, nx, ny, nz, u, v);
        #elif MODEL_Z_AXIS == FAR_TO_NEAR
        // order triangle vertices in counter-clockwise arrangement for a lhs
        vertex[next++] = Vertex(x, y, -z, nx, ny, nz, u, v);
        #endif
    }
}

// add adds six vertices to the vertex list describing a quadrilateral that
// has been defined in terms of four Vectors and a normal vector - vertex 
// coordinates are the coordinates transformed from the coordinate system 
// received to the system used by the host platform - the ordering of the 
// vertices in each triangle of the quad exposes the front (visible) face of
// the triangle on the host platform
//
void VertexList::add(Vector p1, Vector p2, Vector p3, Vector p4, Vector n) {

    if (next >= no)
        error(L"VertexList::10 Vertex list memory is full");
    else if (!vertex)
        error(L"VertexList::11 Vertex memory not allocated");
    else {
        #if MODEL_Z_AXIS == NEAR_TO_FAR
        // order triangle vertices in clockwise arrangement for a lhs
        vertex[next++] = Vertex(p1.x, p1.y, p1.z, n.x, n.y, n.z, 0, 0);
        vertex[next++] = Vertex(p2.x, p2.y, p2.z, n.x, n.y, n.z, 0, 1);
        vertex[next++] = Vertex(p3.x, p3.y, p3.z, n.x, n.y, n.z, 1, 1);
        vertex[next++] = Vertex(p1.x, p1.y, p1.z, n.x, n.y, n.z, 0, 0);
        vertex[next++] = Vertex(p3.x, p3.y, p3.z, n.x, n.y, n.z, 1, 1);
        vertex[next++] = Vertex(p4.x, p4.y, p4.z, n.x, n.y, n.z, 1, 0);
        #elif MODEL_Z_AXIS == FAR_TO_NEAR
        // order triangle vertices in counter-clockwise arrangement for a lhs
        vertex[next++] = Vertex(p1.x, p1.y, -p1.z, n.x, n.y, n.z, 0, 0);
        vertex[next++] = Vertex(p3.x, p3.y, -p3.z, n.x, n.y, n.z, 1, 1);
        vertex[next++] = Vertex(p2.x, p2.y, -p2.z, n.x, n.y, n.z, 0, 1);
        vertex[next++] = Vertex(p1.x, p1.y, -p1.z, n.x, n.y, n.z, 0, 0);
        vertex[next++] = Vertex(p4.x, p4.y, -p4.z, n.x, n.y, n.z, 1, 0);
        vertex[next++] = Vertex(p3.x, p3.y, -p3.z, n.x, n.y, n.z, 1, 1);
        #endif
    }
}

// populate fills *vb with the vertex list
//
void VertexList::populate(void* vb) const {

    Vertex* p = (Vertex*)vb;
    for (int i = 0; i < no; i++)
        *p++ = vertex[i];
}

// vertexFormat returns the vertex format of each vertex in the list
//
unsigned VertexList::vertexFormat() const {

    return (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0));
}

// destructor deletes the vertex list
//
VertexList::~VertexList() {

    if (vertex)
        delete [] vertex;
}

