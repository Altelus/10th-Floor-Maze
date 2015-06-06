/* Texture Implementation - Scene Component - Model Branch
 *
 * Texture.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iScene.h"         // for the Scene Interface
#include "iDeviceTexture.h" // for the DeviceTexture Interface
#include "iUtilities.h"     // for error(), nameWithDir()

#include "Texture.h"        // for Texture class declaration
#include "Configuration.h"  // for TEXTURE_DIRECTORY

//-------------------------------- Texture ------------------------------------
//
// The Texture Primitive represents a texture in the Scene Component
//
// The Scene Coordinator manages the Texture Instances
//
iScene* Texture::coordinator = NULL;

// CreateTexture creates a Texture object, which implements the Texture 
// Primitive
//
iTexture* CreateTexture(const wchar_t* file) {

	return new Texture(file);
}

iTexture* Clone(const iTexture* src) {

    return src->clone();
}

// constructor adds a pointer to the texture to the scene, creates
// the full name of the texture file, stores the name and creates
// the graphics card representation of the texture
//
Texture::Texture(const wchar_t* file) {

	if (!coordinator)
		error(L"Texture 00: Couldn\'t access the Scene Coordinator");
	else if (!coordinator->add(this))
		error(L"Texture 01: Couldn\'t add the texture to the Scene Coordinator");

	int len = strlen(TEXTURE_DIRECTORY) + strlen(file) + 1;
	this->file = new wchar_t[len + 1];
	::nameWithDir(this->file, TEXTURE_DIRECTORY, file, len);

	deviceTexture = CreateDeviceTexture();
}

// copy constructor initializes the instance pointers and calls the
// assignment operator
//
Texture::Texture(const Texture& src) {

	if (!coordinator)
		error(L"Texture 00: Couldn\'t access the Scene Coordinator");
	else if (!coordinator->add(this))
		error(L"Texture 01: Couldn\'t add the texture to the Scene Coordinator");
	
	deviceTexture = NULL;
	file          = NULL;
	*this         = src;
}

// assignment operator discards the old data and copies new data
// from src - does not copy the DeviceTexture from src but creates
// a new DeviceTexture instead
//
Texture& Texture::operator=(const Texture& src) {

	if (this != &src) {
		if (deviceTexture)
			deviceTexture->Delete();
		if (file)
			delete [] file;
        if (src.deviceTexture)
            deviceTexture = src.deviceTexture->clone();
        else
            deviceTexture = NULL;
		int len = strlen(src.file);
		file = new wchar_t[len + 1];
		strcpy(file, src.file, len);
	}

	return *this;
}

// attach attaches the deviceTexture to the pipeline
//
void Texture::attach(int i, unsigned flags) const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->attach(this, i,
		 flags);
}

// detach detaches the deviceTexture from the pipeline
//
void Texture::detach(int i) const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->detach(i);
}

// draw draws the deviceTexture 
//
void Texture::draw(float x, float y, float w, float h, unsigned char a) 
 const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->draw(this, x, y,
		 w, h, a);
}

//GMOK: Draws a texture scaled by x value
//GMOK: percent scales the x value
void Texture::draw(float x, float y, float w, float h, unsigned char a, float p) 
 const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->draw(this, x, y,
		 w, h, a, p);
}

void Texture::draw(float x, float y, float w, float h, unsigned char a, float l, float r, float tt, float b, float xMax, float yMax) 
 const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->draw(this, x, y,
		 w, h, a, l, r, tt, b, xMax, yMax);
}

// suspend suspends the device texture 
//
void Texture::suspend() const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->suspend();
}

// release releases the device texture 
//
void Texture::release() const {

	if (deviceTexture)
		const_cast<iDeviceTexture*>(deviceTexture)->release();
}

// destructor deletes the graphics card representation and removes the 
// pointer to the texture from the scene
//
Texture::~Texture() {

	deviceTexture->Delete();
	if (file)
		delete [] file;
	if (coordinator)
		coordinator->remove(this);
	else
		error(L"Texture 90:: Couldn\'t access the Scene Coordinator");
}
