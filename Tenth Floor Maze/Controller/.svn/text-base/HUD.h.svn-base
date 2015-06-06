#ifndef _HUD_H_
#define _HUD_H_

/* HUD Declaration - Heads Up Display Element - Model Branch
 *
 * HUD.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iHUD.h" // for the HUD Interface

//-------------------------------- HUD ----------------------------------------
//
// The HUD Coordinator manages the Text items in the HUD Component 
//
class HUD : public iHUD {

	static const unsigned MAX_TEXTS = 100;
	static const int MAX_HUDTEXTURES = 50;

	iContext*    context;         // points to the Context object

    int          noTexts;         // number of text items
	int          noHUDTextures;	  //GMOK:  number of HUDTextures

    const iText* text[MAX_TEXTS]; // points to each text item on the HUD
	const iHUDTexture* hTexture[MAX_HUDTEXTURES]; //GMOK: points to the HUDTextures

    iText*       fpsText;         // points to the fps text item

    int          lastUpdate;      // last time display status was updated
	int          lastToggle;      // last time display status was toggled
    bool         on;              // is the HUD being displayed?

	// relative coordinates [0,1] with respect to client area
	float        tlx;             // horizontal top left coordinate
    float        tly;             // vertical top left coordinate
    float        rw;              // width of the HUD
    float        rh;              // height of the HUD

    HUD(iContext*);
    HUD(const HUD& h);            // prevents copying
    HUD& operator=(const HUD& h); // prevents assignment
    virtual ~HUD();

	void validate();

  public:
	friend iHUD* CreateHUD(iContext*);
	// initialization functions
    void   initialize(int now);
    bool   add(const iText* t);
	bool   add(const iHUDTexture* t);
	void   reset(int now);
    void   restore(int now);
	// execution functions
	void   update(int now);
	float  topLeftX() const { return tlx; }
	float  topLeftY() const { return tly; }
	float  width() const    { return rw; }
	float  height() const   { return rh; }
    void   fps(int) const;
    void   draw() const;
	// termination functions
    void   suspend() const;
    bool   remove(const iText* t);
	bool   remove(const iHUDTexture* t); 
	void   release() const;
	void   Delete() const { delete this; }
};

#endif
