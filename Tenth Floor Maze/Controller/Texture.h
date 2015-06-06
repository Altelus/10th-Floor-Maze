#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/* Texture Declaration - Scene Component - Model Branch
 *
 * Texture.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iTexture.h" // for the Texture Interface

//-------------------------------- Texture ------------------------------------
//
// The Texture Primitive represents a single texture in the Scene Component
//
class iScene;
class iDeviceTexture;

class Texture : public iTexture {

	static iScene*         coordinator;     // points to the texture coordinator

	wchar_t*               file;           // points to texture file name
	const  iDeviceTexture* deviceTexture;  // points to the representation of
	                                       // the texture on the graphics card

	Texture(const wchar_t* file);
	Texture(const Texture&);
	virtual ~Texture();

  public:
	friend iTexture* CreateTexture(const wchar_t* file);
	static void isCoordinatedBy(iScene* scene) { coordinator = scene; }
	Texture& operator=(const Texture&);
    iTexture* clone() const { return new Texture(*this); }
	// execution functions
	void attach(int i, unsigned flags) const;
	void detach(int i) const;
	void draw(float x, float y, float w, float h, unsigned char a) const;
	void draw(float x, float y, float w, float h, unsigned char a, float p) const;
	void draw(float x, float y, float w, float h, unsigned char a, float l, float r, float tt, float b, float xMax, float yMax) const;
	const wchar_t* filename() const { return file; }
	// termination functions
	void suspend() const;
    void release() const;
	void Delete() const { delete this; }
};

#endif
