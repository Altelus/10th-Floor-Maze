#ifndef _I_FONT_H_
#define _I_FONT_H_

/* Font Interface - GraphicsCard Component - Direct Device Branch
 *
 * iFont.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iFont --------------------------------------
//
// iFont is the Interface to the Font Primitive of the Graphics Card Component
//
class iText;

class iFont {
  public:
    virtual iFont* clone() const         = 0;
	// initialization functions
    virtual bool restore() const         = 0;
	// execution functions
    virtual void draw(const iText* text) = 0;
	// termination functions
    virtual void suspend() const         = 0;
	virtual void release()               = 0;
	virtual void Delete() const          = 0;
};

extern "C"
iFont* CreateAFont();

#endif