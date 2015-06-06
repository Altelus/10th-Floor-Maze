/* Scene Implementation - Scene Component - Model Branch
 *
 * Scene.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"        // for the Context Interface
#include "iUtilities.h"      // for error()

#include "Scene.h"           // for the Scene class declaration
#include "Object.h"          // for Object::isCoordinatedBy
#include "Texture.h"         // for Texture::isCoordinatedBy

//-------------------------------- Scene --------------------------------------
//
// The Scene Coordinator manages the objects and textures in the Scene Component
//
// CreateScene creates the Scene Object, which implements the Scene Coordinator
//
iScene* CreateScene(iContext* c) {

	return new Scene(c);
}

// constructor initializes the object and texture pointers, the reference
// time and attaches the Scene class to the Object and Texture classes
//
Scene::Scene(iContext* c) : context(c) {

    noObjects = 0;
    for (int i = 0; i < MAX_OBJECTS; i++)
        object[i] = NULL;
	noTextures = 0;
    for (int i = 0; i < MAX_TEXTURES; i++)
        texture[i] = NULL;

	// manages the objects and textures
	Object::isCoordinatedBy(this);
	Texture::isCoordinatedBy(this);
}

// add adds a pointer to Object *o to the scene
// and returns true if successful, false otherwise
//
bool Scene::add(const iObject* o) {

    int i;
    bool rc = false;

    for (i = 0; i < noObjects; i++)
        if (!object[i]) {
            object[i] = o;
            i = noObjects + 1;
            rc = true;
        }
    if (i == noObjects && noObjects < MAX_OBJECTS) {
        object[noObjects++] = o;
        rc = true;
    }

    return rc;
}

// add adds a pointer to iTexture *t to the scene
// and returns true if successful, false otherwise
//
bool Scene::add(const iTexture* t) {

    int i;
    bool rc = false;

    for (i = 0; i < noTextures; i++)
        if (!texture[i]) {
            texture[i] = t;
            i = noTextures + 1;
            rc = true;
        }
    if (i == noTextures && noTextures < MAX_TEXTURES) {
        texture[noTextures++] = t;
        rc = true;
    }

    return rc;
}

// draw draws the graphic representations of the objects in the scene
// that match the requested opacity
//
void Scene::draw(bool opacity) const {

    for (int i = 0; i < noObjects; i++)
		if (object[i])
			object[i]->draw(opacity);
}

// suspend suspends each object and each texture
//
void Scene::suspend() const {

    for (int i = 0; i < noObjects; i++)
		if (object[i]) 
			object[i]->suspend();

	for (int i = 0; i < noTextures; i++)
		if (texture[i])
			texture[i]->suspend();
}

// release releases each object and each texture
//
void Scene::release() const {

    for (int i = 0; i < noObjects; i++)
		if (object[i]) 
			object[i]->release();

	for (int i = 0; i < noTextures; i++)
		if (texture[i])
			texture[i]->release();
}

// remove removes the pointer to iObject *o from the scene and
// returns true if successful, false otherwise
//
bool Scene::remove(const iObject* o) {

    bool rc = false;

    for (int i = 0; i < noObjects; i++)
        if (object[i] == o) {
            object[i] = NULL;
            rc = true;
        }
    while (!object[noObjects - 1])
        noObjects--;

    return rc;
}

// remove removes the pointer to iTexture *t from the scene and
// returns true if successful, false otherwise
//
bool Scene::remove(const iTexture* t) {

    bool rc = false;

    for (int i = 0; i < noTextures; i++)
        if (texture[i] == t) {
            texture[i] = NULL;
            rc = true;
        }
    while (!texture[noTextures - 1])
        noTextures--;

    return rc;
}

// destructor deletes all of the objects and textures in the scene
//
Scene::~Scene() {

    for (int i = 0; i < noObjects; i++)
        if (object[i]) 
            object[i]->Delete();

    for (int i = 0; i < noTextures; i++)
        if (texture[i]) 
            texture[i]->Delete();
}
