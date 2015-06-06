/* Font Implementation - GraphicsCard Component - Direct Device Branch
 *
 * Font.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iText.h"            // for the Text Interface
#include "iDisplay.h"         // for the Display Interface
#include "iUtilities.h"       // for error()

#include "Font.h"             // for the Font class declaration
#include "MathDeclarations.h" // for Matrix, Vector and Colour
#include "Configuration.h"    // for Font display colour  

//-------------------------------- Font ---------------------------------------
//
// The Font Primitive represents a text item in the Graphics Card Component 
//
// The Display object provides the API connectivity for the font objects
//
iDisplay* Font::display = NULL;

// CreateAFont creates a Font object, which implements the Font Primitive
//
iFont* CreateAFont() {

	return new Font();
}

// constructor initializes the instance variables
//
Font::Font() : flags(0) {

    d3dfont = NULL;
}

Font::Font(const Font& src) {

    *this = src;
}

Font& Font::operator=(const Font& src) {

    if (this != &src) {
        d3dfont = NULL;
        flags = src.flags;
    }

    return *this;
}

// setup creates the font on the graphics card 
//
void Font::setup(const iText* text) {

	// define the text alignment flags
	unsigned f = text->flags();
	if (!f) f = TXT_DEFAULT;
    flags = 0;
    if (f & TXT_LEFT)        flags |= DT_LEFT;
    else if (f & TXT_RIGHT)  flags |= DT_RIGHT;
    else if (f & TXT_CENTER) flags |= DT_CENTER;
    if (f & TXT_TOP)         flags |= DT_TOP;
    else if (f & TXT_BOTTOM) flags |= DT_BOTTOM;
    else if (f & TXT_MIDDLE) flags |= DT_VCENTER;
    // create the font COM object on the display device
	wchar_t* DefaultFontFileName = L"TenthFloorDefault.ttf";
	wchar_t* DefaultFontName = L"Tw Cen MT Condensed Extra Bold";
	int len = strlen(FONT_DIRECTORY) + strlen(DefaultFontFileName) + 1;
	wchar_t* DefaultFontFilePath = new wchar_t[len + 1];
	nameWithDir(DefaultFontFilePath, FONT_DIRECTORY, DefaultFontFileName, len);
	AddFontResource(DefaultFontFilePath);
	int font_size = 25;

    if (FAILED(D3DXCreateFont(((LPDIRECT3DDEVICE9)display->device()), 
     font_size, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
     5, FF_DONTCARE | DEFAULT_PITCH, DefaultFontName, &d3dfont)))
        error(L"Font::10 Failed to create the font object");
}

// restore re-acquires the reference to the display device
//
bool Font::restore() const {

    bool rc = false;

    // re-acquire the reference to the graphics card
    if (d3dfont)
        rc = d3dfont->OnResetDevice() == D3D_OK;

    return rc;
}

// draw defines the location of the font and draws text->text() at that 
// location using color TXT_R, TXT_G, TXT_B, TXT_A
//
void Font::draw(const iText* text) {

    if (!d3dfont) setup(text);
	if (display->spriteManager() && d3dfont && text->text()) {
		// creates the drawing rectangle in screen coordinates 
		RECT rect;
		SetRect(&rect, 
		 (int)(display->width()  * text->topLeftX()), 
		 (int)(display->height() * text->topLeftY()),
		 (int)(display->width()  * text->bottomRightX()), 
		 (int)(display->height() * text->bottomRightY()));
        // draws the text string str within the rectangle
		d3dfont->DrawText(((LPD3DXSPRITE)display->spriteManager()), 
         text->text(), -1, &rect, flags, D3DCOLOR_RGBA(TXT_R, TXT_G, TXT_B, 
         TXT_A));
	}
}

// suspend detaches the font from the display device
//
void Font::suspend() const {

    // release references to the display device
    if (d3dfont)
        d3dfont->OnLostDevice();
}

// release releases the font object altogether 
//
void Font::release() {

	suspend();

    if (d3dfont) {
        d3dfont->Release();
        d3dfont = NULL;
    }
}

// destructor releases the font object
//
Font::~Font() {

	release();
}

