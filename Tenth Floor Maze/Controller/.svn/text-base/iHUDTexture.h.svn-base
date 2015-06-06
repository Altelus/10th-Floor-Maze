#ifndef _I_HUDTEXTURE_H_
#define _I_HUDTEXTURE_H_

/* HUD Texture Interface - Heads Up Display Element - Model Branch
*
* iHUDTexture.h
* fwk4gps version 1.0
* gam666/dps901
* August 30 2010
* copyright (c) 2010 Chris Szalwinski 
* distributed under TPL - see ../Licenses.txt
*/
//-------------------------------- Hud Texture ---------------------------------------
//
class iHUDTexture {
public:
	virtual iHUDTexture* clone() const     = 0;
	// execution functions
	virtual void  set(iTexture* tex)	   = 0;
	virtual void  set(float cur)		   = 0;
	virtual void  setAlpha(unsigned char recAlpha) = 0; // RYAN: added to set the icon opacity
	virtual void  setSprite(float, float, float, float, float ,float, float, float, int) = 0;
	virtual void  updateSprite(int)		   = 0;
	virtual	void  enableBackground(bool b, iTexture* bg, unsigned char aa) = 0;
	virtual	void  enableReport(bool b)	   = 0;
	virtual float topLeftX() const         = 0;
	virtual float topLeftY() const         = 0;
	virtual float bottomRightX() const     = 0;
	virtual float bottomRightY() const     = 0;
	virtual void  draw() const             = 0;
	//GMOK:  termination functions
	virtual void  suspend() const          = 0;
	virtual void  release() const          = 0;
	virtual void  Delete() const           = 0;
};

extern "C"
	iHUDTexture* CreateHUDTexture(float, float, float, float, unsigned char, int);

//GMOK: extern "C"
iHUDTexture* Clone(const iHUDTexture*);

#endif
