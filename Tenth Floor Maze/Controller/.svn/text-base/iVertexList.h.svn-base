#ifndef _I_VERTEX_LIST_H_
#define _I_VERTEX_LIST_H_

/* VertexList Interface - GraphicsCard Component - Direct Device Branch
 *
 * iVertexList.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iVertexList --------------------------------
//
// IVertex is the Interface to the Vertex List Primitive of the Graphics Card
// Component
//
struct Vector;

class iVertexList {
  public:
    virtual iVertexList* clone() const                                     = 0;
    virtual void     add(float, float, float, float, float, float, float = 0, 
     float = 0)                                                            = 0;
    virtual void     add(Vector, Vector, Vector, Vector, Vector)           = 0;
    virtual int      noVertices() const                                    = 0;
    virtual int      vertexSize() const                                    = 0;
    virtual unsigned vertexFormat() const                                  = 0;
    virtual void     populate(void*) const                                 = 0;
	virtual void     Delete() const                                        = 0;
};

extern "C"
iVertexList* CreateVertexList(int);

#endif
