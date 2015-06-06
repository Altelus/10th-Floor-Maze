#ifndef _I_SCENE_H_
#define _I_SCENE_H_

/* Scene Interface - Scene Component - Model Branch
 *
 * iScene.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iScene -------------------------------------
//
// iScene is the Interface to the Scene Coordinator of the Scene Component
//
class iContext;
class iObject;
class iTexture;

class iScene {
  public:
	// initialization functions
    virtual bool add(const iObject* o)                  = 0;
    virtual bool add(const iTexture* t)                 = 0;
	// execution functions
    virtual void draw(bool opacity) const               = 0;
	// termination functions
    virtual void suspend() const                        = 0;
    virtual void release() const                        = 0;
	virtual bool remove(const iObject* o)               = 0;
	virtual bool remove(const iTexture* t)              = 0;
    virtual void Delete() const                         = 0;
};

extern "C"
iScene* CreateScene(iContext* c);

#endif
