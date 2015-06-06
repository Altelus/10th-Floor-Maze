#ifndef _I_TEXTURE_H_
#define _I_TEXTURE_H_

/* Texture Interface - Scene Component - Model Branch
 *
 * iTexture.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */
//-------------------------------- iTexture -----------------------------------
//
// iTexture is the Interface to the Texture Primitive of the Scene Component
//
class iTexture {
  public:
    virtual iTexture* clone() const                                    = 0;
	// execution functions
	virtual void attach(int, unsigned) const                           = 0;
	virtual void detach(int) const                                     = 0;
	virtual void draw(float, float, float, float, unsigned char) const = 0;
	virtual void draw(float, float, float, float, unsigned char, float) const = 0;
	virtual void draw(float, float, float, float, unsigned char, float, float, float, float, float, float) const = 0;
	virtual const wchar_t* filename() const                            = 0;
	// termination functions
	virtual void suspend() const                                       = 0;
	virtual void release() const                                       = 0;
	virtual void Delete() const                                        = 0;
};

extern "C"
iTexture* CreateTexture(const wchar_t* file);

iTexture* Clone(const iTexture*);

#endif
