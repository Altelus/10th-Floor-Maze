#ifndef _SCENE_H_
#define _SCENE_H_

/* Scene Declaration - Scene Component - Model Branch
 *
 * Scene.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iScene.h" // for the Scene Interface

//-------------------------------- Scene --------------------------------------
//
// The Scene Coordinator manages objects and textures in the Scene Component 
//
class Scene : public iScene {

	static const int MAX_OBJECTS  = 5000;
	static const int MAX_TEXTURES = 100;

	iContext*       context;               // points to the Context object

	int             noObjects;             // number of objects
	int             noTextures;            // number of textures
    const iObject*  object[MAX_OBJECTS];   // points to the objects
	const iTexture* texture[MAX_TEXTURES]; // points to the textures

    Scene(iContext* c);
    Scene(const Scene& s);            // prevents copying
    Scene& operator=(const Scene& s); // prevents assignment
    virtual ~Scene();

  public:
	friend iScene* CreateScene(iContext* c);
	// initialization functions
    bool   add(const iObject*);
    bool   add(const iTexture*);
	// execution function
    void   draw(bool opaque) const;
	// termination functions
    void   suspend() const;
    void   release() const;
    bool   remove(const iObject*);
    bool   remove(const iTexture*);
	void   Delete() const { delete this; }
};

#endif
