/* Text Implementation - Heads Up Display Element - Model Branch
 *
 * Text.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iHUD.h"           // for the HUD Interface
#include "iFont.h"          // for the Font Interface
#include "iUtilities.h"     // for error()

#include "Text.h"           // for the Text class declaration
#include "ModelSettings.h"  // for Model Action enumeration constants

//-------------------------------- Text --------------------------------------
//
// The Text Primitive represents a single text item in the HUD Component
//
// The HUD Coordinator manages the Text Instances
//
iHUD* Text::coordinator  = NULL;

// CreateText creates a Text object, which implements the Text Primitive
//
iText* CreateText(float x, float y, float xx, float yy, unsigned f, 
 const wchar_t* str) {

	return new Text(x, y, xx, yy, f, str);
}

iText* Clone(const iText* src) {

    return src->clone();
}

Text::Text(float x, float y, float xx, float yy, unsigned flags, 
 const wchar_t* text) :  tlx(x), tly(y), brx(xx), bry(yy), dFlags(flags) {

    if (!coordinator)
        error(L"Text::00 Couldn\'t access the HUD Coordinator");
    else if(!coordinator->add(this))
        error(L"Text::01 Couldn\'t add the text to the HUD Coordinator");

    font = CreateAFont();
    str = NULL;

    if (tlx < TL_MIN) tlx = TL_MIN;
    else if (tlx > TL_MAX) tlx = TL_MAX;
    if (tly < TL_MIN) tly = TL_MIN;
    else if (tly > TL_MAX) tly = TL_MAX;
    if (brx < TL_MIN) brx = TL_MIN;
    else if (brx > TL_MAX) brx = TL_MAX;
    if (bry < TL_MIN) bry = TL_MIN;
    else if (bry > TL_MAX) bry = TL_MAX;

	if (text) set(text);
}

// copy constructor initializes instance pointers and calls
// assignment operator
//
Text::Text(const Text& src) {

    if (!coordinator)
        error(L"Text::00 Couldn\'t access the HUD Coordinator");
    else if(!coordinator->add(this))
        error(L"Text::01 Couldn\'t add the text to the HUD Coordinator");

    font  = NULL;
    str   = NULL;
	*this = src;
}

// assignment operator discards old data and copies over data
// form src - does not copy over the Font object from src but
// creates a new Font object for the current Text object
//
Text& Text::operator=(const Text& src) {

	if (this != &src) {
		if (font)
			font->Delete();
		if (str)
			delete [] str;
        if (src.font)
            font = src.font->clone();
        else
            font = NULL;
		int len = strlen(src.str);
		str     = new wchar_t[len + 1];
		strcpy(str, src.str, len);
		tlx     = src.tlx;
		tly     = src.tly;
		brx     = src.brx;
		bry     = src.bry;
		dFlags  = src.dFlags;
	}

	return *this;
}

// restore restores the font associated with the text object
//
void Text::restore() const {

	if (font)
		const_cast<iFont*>(font)->restore();
}

// topLeftX returns the relative top left x coordinate of the text
//
float Text::topLeftX() const { 
	
	return coordinator->topLeftX() + coordinator->width() * tlx; 
}

// topLeftY returns the relative top left y coordinate of the text
//
float Text::topLeftY() const { 
	
	return coordinator->topLeftY() + coordinator->height() * tly; 
}

// bottomRightX returns the relative bottom right x coordinate of the text
//
float Text::bottomRightX() const { 
	
	return coordinator->topLeftX() + coordinator->width() * brx; 
}

// bottomRightY returns the relative bottom right y coordinate of the text
//
float Text::bottomRightY() const { 
	
	return coordinator->topLeftY() + coordinator->height() * bry; 
}

// set copies str[] into the Text object
//
void Text::set(const wchar_t* text) {

    int len = strlen(text);
    if (str)
        delete [] str;
    str = new wchar_t[len + 1];
    strcpy(str, text, len);
}

// draw draws the text string using the Font object
//
void Text::draw() const {

	if (font)
		const_cast<iFont*>(font)->draw(this);
}

// suspends suspends the font associated with the text object
//
void Text::suspend() const {

	if (font)
		font->suspend();
}

// release releases the font associated with the text object
//
void Text::release() const {

	if (font)
		const_cast<iFont*>(font)->release();
}

// destructor destroys the font associated with this text object
// and the text stored in the object and removes the text object
// from the HUD
//
Text::~Text() {

    if (font)
        font->Delete();
    if (str)
        delete [] str;
    if (coordinator)
        coordinator->remove(this);
    else
        error(L"Text::90 Couldn\'t access the HUD Coordinator");
}
