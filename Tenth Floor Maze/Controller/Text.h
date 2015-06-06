#ifndef _TXT_H_
#define _TXT_H_

/* Text Declaration - Heads Up Display Element - Model Branch
 *
 * Text.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iText.h" // for the Text Interface

//-------------------------------- Text ---------------------------------------
//
// The Text Primitive represents a single text item in the HUD Component
//
class iHUD;
class iFont;

class Text : public iText {

    static iHUD* coordinator; // points to the Heads Up Display coordinator

    const iFont* font;    // points to the font used to display this object
    wchar_t*     str;     // points to the text string

	// relative coordinates [0 -> 1] within the hud
	float        tlx;     // horizontal top left
    float        tly;     // vertical top left
    float        brx;     // horizontal bottom right
    float        bry;     // vertical bottom right

	unsigned     dFlags;  // text display flags

    Text(float x, float y, float xx, float yy, unsigned f, 
	 const wchar_t* str);
    Text(const Text& src);
    virtual ~Text();

  public:
	friend iText* CreateText(float x, float y, float xx, float yy, 
	 unsigned f, const wchar_t* str);
	static void isCoordinatedBy(iHUD* hud) { coordinator = hud; }
    Text&  operator=(const Text& src);
    iText* clone() const { return new Text(*this); }
	// initialization function
	void   restore() const;
	// execution functions
    void   set(const wchar_t* text);
	float  topLeftX() const;
	float  topLeftY() const;
	float  bottomRightX() const;
	float  bottomRightY() const;
	const  wchar_t* text() const { return str; }
	unsigned flags() const       { return dFlags; }
	void   draw() const;
	// termination functions
	void   suspend() const;
	void   release() const;
	void   Delete() const { delete this; }
};

#endif
