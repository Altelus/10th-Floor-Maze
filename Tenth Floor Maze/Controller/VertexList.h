#ifndef _VERTEX_LIST_H_
#define _VERTEX_LIST_H_

/* VertexList Declaration - Graphics Card Component - Direct Device Branch
 *
 * VertexList.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iVertexList.h"      // for the VertexList Interface

//-------------------------------- Vertex -------------------------------------
//
// Vertex holds the data for a single vertex of the VertexList Primitive
//
struct Vertex {

    float x;   // x coordinate in the local frame
    float y;   // y coordinate in the local frame
    float z;   // z coordinate in the local frame
    float nx;  // x coordinate of normal in the local frame
    float ny;  // y coordinate of normal in the local frame
    float nz;  // z coordinate of normal in the local frame
    float tu;  // u coordinate of texture
    float tv;  // v coordinate of texture
    Vertex(float xx = 0, float yy = 0, float zz = 0, float nxx = 0, 
	 float nyy = 0, float nzz = 0, float ttu = 0, float ttv = 0);
};

//-------------------------------- VertexList ---------------------------------
//
// The VertexList Primitive holds the vertex data for a Graphic Primitive
//
class VertexList : public iVertexList {

    int     no;     // number of verticies in the vertex list
    int     next;   // index of next vertex to be filled
    Vertex* vertex; // list of vertices

    VertexList(int n);
    virtual ~VertexList();

public:
    friend iVertexList* CreateVertexList(int n);
    VertexList(const VertexList&);
    VertexList& operator=(const VertexList&);
    iVertexList* clone() const { return new VertexList(*this); }
    void add(float, float, float, float, float, float, float, float);
    void add(Vector, Vector, Vector, Vector, Vector);
    int  noVertices() const    { return no; }
    int  vertexSize() const    { return sizeof Vertex; }
    unsigned vertexFormat() const;
    void populate(void*) const;
    void Delete() const        { delete this; } 
};

#endif
