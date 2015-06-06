#ifndef _FONT_H_
#define _FONT_H_

/* Font Declaration - GraphicsCard Component - Direct Device Branch
 *
 * Font.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iFont.h"            // for the Font Interface
#include "GraphicsPlatform.h" // forgraphics api headers

//-------------------------------- Font ---------------------------------------
//
// The Font Primitive implements a Text item in the Graphics Card Component
//
class iText;
class iDisplay;

class Font : public iFont {

	static iDisplay* display; // points to the Display object

	unsigned flags;           // font display flags

    LPD3DXFONT d3dfont;       // points to the Direct3D font Interface

    Font();
    virtual ~Font();
    void   setup(const iText* text);

  public:
	friend iFont* CreateAFont();
	static void connectsThrough(iDisplay* d) { display = d; }
    Font(const Font& v);
    Font& operator=(const Font& v);
    iFont* clone() const { return new Font(*this); }
	// initialization function
    bool   restore() const;
	// execution functions
    void   draw(const iText* text);
	// termination functions
    void   suspend() const;
	void   release();
	void   Delete() const { delete this; }
};

#endif