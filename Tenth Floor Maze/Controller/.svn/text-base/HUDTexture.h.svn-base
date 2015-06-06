#ifndef _HUDTEXTURE_H_
#define _HUDTEXTURE_H_

/* HUD Texture Declaration - Heads Up Display Element - Model Branch
 *
 * Text.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iHUDTexture.h" //GMOK:  for the HUDTexture Interface

#include "ModelSettings.h" //GMOK:  for HUD_?

#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <sstream>
//-------------------------------- HUDTexture ---------------------------------------
//
class iHUD;
class iTexture;
class iText;

class HUDTexture : public iHUDTexture {

    static iHUD* coordinator; //GMOK:  points to the Heads Up Display coordinator

    const iTexture* t;    //GMOK:  points to the texture used to display this object
	const iTexture* background; //GMOK:  points to a background texture for progress bars
	iText* rCValue; //GMOK: points to text used to report current value

	//GMOK:  relative coordinates [0 -> 1] within the hud
	float        tlx;     //GMOK:  horizontal top left
    float        tly;     //GMOK:  vertical top left
    float        brx;     //GMOK:  horizontal bottom right
    float        bry;     //GMOK:  vertical bottom right
	unsigned char a;      //GMOK: alpha of texture
	unsigned char bgA;    //GMOK: background alpha if background is enabled

	int	type;    //GMOK:  type of texture 0=static/1=progress bar/2=sprite

	float maxValue;		  //GMOK: max value for progress bar
	float curValue;		  //GMOK: cur value for progress bar
	bool showBG; //GMOK: enable background texture
	bool showText; //GMOK: enable text report of current value

	//specifies a rectangle area of the texture to display
	float saL;
	float saR;
	float saT;
	float saB;

	float saX;//left and right box boundary to increment by
	float saXMax;//max left and right value

	float saY;//top and bottem box boundary to increment by
	float saYMax;//max y value

	int lastUpdate;

    HUDTexture(float xx = 0, float yy = 0, float bxx = HUD_W, float byy = HUD_H,  unsigned char aa = HUD_A_DEFAULT, int type = HUDT_STATIC);
    HUDTexture(const HUDTexture& src);
    virtual ~HUDTexture();

  public:
	friend iHUDTexture* CreateHUDTexture(float xx, float yy, float bxx, float byy, unsigned char aa, int type);
	static void isCoordinatedBy(iHUD* hud) { coordinator = hud; }
    HUDTexture&  operator=(const HUDTexture& src);
    iHUDTexture* clone() const { return new HUDTexture(*this); }
	//GMOK:  execution functions
    void   set(iTexture* tex);
	void   set(float cur);
	void   setAlpha(unsigned char recAlpha);

	void  setSprite(float l, float r, float tt, float b, float xShift, float xMax, float yShift, float yMax, int now);
	void  updateSprite(int now);

	void   enableBackground(bool b, iTexture* bg, unsigned char aa);
	void   enableReport(bool b);

	float  topLeftX() const;
	float  topLeftY() const;
	float  bottomRightX() const;
	float  bottomRightY() const;
	void   draw() const;
	//GMOK:  termination functions
	void   suspend() const;
	void   release() const;
	void   Delete() const { delete this; }
};

#endif
