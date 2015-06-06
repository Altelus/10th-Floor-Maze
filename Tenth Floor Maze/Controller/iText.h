#ifndef _I_TEXT_H_
#define _I_TEXT_H_

/* Text Interface - Heads Up Display Element - Model Branch
 *
 * iText.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- Text ---------------------------------------
//
// iText is the Interface to the Text Primitive of the HUD Component
//
class iText {
  public:
    virtual iText* clone() const           = 0;
    // initialization functions
    virtual void  restore() const          = 0;
	// execution functions
    virtual void  set(const wchar_t* text) = 0;
	virtual float topLeftX() const         = 0;
	virtual float topLeftY() const         = 0;
	virtual float bottomRightX() const     = 0;
	virtual float bottomRightY() const     = 0;
	virtual const wchar_t* text() const    = 0;
	virtual void  draw() const             = 0;
	virtual unsigned flags() const         = 0;
	// termination functions
	virtual void  suspend() const          = 0;
	virtual void  release() const          = 0;
	virtual void  Delete() const           = 0;
};

extern "C"
iText* CreateText(float, float, float, float, unsigned = 0, const wchar_t* = 0);

extern "C"
iText* Clone(const iText*);

#endif
