/* HUDTexture Implementation - Heads Up Display Element - Model Branch
 *
 * HUDTexture.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iHUD.h"           //GMOK:  for the HUD Interface
#include "iTexture.h"       //GMOK:  for the Texture Interface
#include "iText.h"       //GMOK:  for the Texture Interface
#include "iUtilities.h"     //GMOK:  for error()

#include "HUDTexture.h"     //GMOK:  for the HUDTexture class declaration
#include "ModelSettings.h"  //GMOK:  for Model Action enumeration constants

//GMOK: -------------------------------- HUDTexture --------------------------------------
//
//GMOK:  The HUDTexture Primitive represents a single HUDTexture item in the HUD Component
//
//GMOK:  The HUD Coordinator manages the HUDTexture Instances
//
iHUD* HUDTexture::coordinator  = NULL;

//GMOK:  CreateText creates a HUDTexture object, which implements the HUDTexture Primitive
iHUDTexture* CreateHUDTexture(float xx, float yy, float bxx, float byy, unsigned char aa, int type)  {

	return new HUDTexture(xx, yy, bxx, byy, aa, type);
}

iHUDTexture* Clone(const iHUDTexture* src) {

    return src->clone();
}

HUDTexture::HUDTexture(float xx, float yy, float bxx, float byy, unsigned char aa, int type) : 
tlx(xx), tly(yy), brx(bxx), bry(byy), a(aa), type(type) {

    if (!coordinator)
        error(L"HUDTexture::00 Couldn\'t access the HUD Coordinator");
    else if(!coordinator->add(this))
        error(L"HUDTexture::01 Couldn\'t add the HUDTexture to the HUD Coordinator");

    t = NULL;

	//GMOK: setup for background
	showBG = false;
	background = NULL;
	bgA = NULL;

	//GMOK: setup for text report (progress bar)
	showText = false;
	rCValue = NULL;

	//GMOK: setup progress bar value
	curValue = maxValue = 0;

	//GMOK: checks and corrects texture coordinates to be with in the HUD 
    if (tlx < HUDT_MIN) tlx = HUDT_MIN;
    else if (tlx > HUDT_MAX) tlx = HUDT_MAX;
    if (tly < HUDT_MIN) tly = HUDT_MIN;
    else if (tly > HUDT_MAX) tly = HUDT_MAX;
    if (brx < HUDT_MIN) brx = HUDT_MIN;
    else if (brx > HUDT_MAX) brx = HUDT_MAX;
    if (bry < TL_MIN) bry = TL_MIN;
    else if (bry > HUDT_MAX) bry = HUDT_MAX;

	saL = saR = saT = saB = saX = saXMax = saY = saYMax = 0;

	lastUpdate = 0;
}

//GMOK:  copy constructor initializes instance pointers and calls
//GMOK:  assignment operator
HUDTexture::HUDTexture(const HUDTexture& src) {

    if (!coordinator)
        error(L"HUDTexture::00 Couldn\'t access the HUD Coordinator");
    else if(!coordinator->add(this))
        error(L"HUDTexture::01 Couldn\'t add the HUDTexture to the HUD Coordinator");
	
	t = NULL;
	background = NULL;
	rCValue = NULL;

	*this = src;
}

//GMOK:  assignment operator discards old data and copies over data
//GMOK:  from src - does not copy over the texture object from src but
//GMOK:  creates a new texture object for the current HUDTexture object
HUDTexture& HUDTexture::operator=(const HUDTexture& src) {

	if (this != &src) {
		if (t)
			delete t;
        if (src.t)
            t = src.t->clone();
        else
            t = NULL;

		if (src.showBG)
		{
			if (background)
				delete background;
			if (src.background)
				background = src.background->clone();
			else
				background = NULL;
		}
		showBG = src.showBG;
		bgA = src.bgA;

		if (src.showText)
		{
			if (rCValue)
				delete rCValue;
			if (src.rCValue)
				rCValue = src.rCValue->clone();
			else
				rCValue = NULL;
		}
		showText = src.showText;

		tlx     = src.tlx;
		tly     = src.tly;
		brx     = src.brx;
		bry     = src.bry;

		a = src.a;

		maxValue = src.maxValue;
		curValue = src.curValue;

		type = src.type;

		saL = src.saL;
		saR = src.saR;
		saT = src.saT;
		saB = src.saB;

		saX = src.saX;
		saXMax = src.saXMax;

		saY = src.saY;
		saYMax = src.saYMax;

		lastUpdate = src.lastUpdate;
	}

	return *this;
}

//GMOK: sets the passed texture as the default texture
void HUDTexture::set(iTexture* tex) {

    if (t)
        delete t;
	else
		t = NULL;

	t = tex;
}

//GMOK: set the current value - first call will set max and current
//GMOK: NOTE: not yet implemented increasing progress bars
void HUDTexture::set(float cur) {

	if (cur > maxValue)
		maxValue = cur;
	else if (cur < 0)
		cur = 0;

	if (cur == 0)
		maxValue = 0;

	curValue = cur;

	//GMOK: updates the text of the progress bar if enabled
	if (showText && rCValue)
	{
		int temp;

		if (!curValue)
			temp = 0;
		else
			temp = (curValue/maxValue)*100;

		wchar_t str[25];
		wsprintf(str,  L"%d%%", temp);
		rCValue->set(str);
	}
}
// RYAN: Sets texture opacity
void HUDTexture::setAlpha(unsigned char recAlpha) {
	a = recAlpha;
}


//sets the sprite object for drawin
void  HUDTexture::setSprite(float l, float r, float tt, float b, 
	float xShift, float xMax, float yShift, float yMax,int now) 
{
	lastUpdate = now;

	saL = l;
	saR = r;
	saT = tt;
	saB = b;

	saX = xShift;
	saXMax = xMax;

	saY = yShift;
	saYMax = yMax;
}

//updates the sprite by moving the rectangle drawing area
void  HUDTexture::updateSprite(int now)
{
	if (now - lastUpdate > HUD_SPRITE_LATENCY)
	{
		saL+=saX;
		saR+=saX;

		if (saR > saXMax)
		{
			saL = 0;
			saR = saX;
		}
		lastUpdate = now;
	}
}

//enables and sets the background texture
void  HUDTexture::enableBackground(bool b, iTexture* bg, unsigned char aa)
{
	showBG = b;

	if (showBG && bg)
	{
		if (background)
			delete background;
		else
			background = NULL;

		background = bg;

		if (aa)
			bgA = aa;
	}
}

//GMOK: enables and sets the text report of current value
//GMOK: (progress bar)
void  HUDTexture::enableReport(bool b)
{
	showText = b;

	if (showText)
	{
		if (rCValue)
			delete rCValue;
		else
			rCValue = NULL;

		rCValue = CreateText(tlx, tly, brx, 1.0f, TXT_CENTER, L"ProgressValue");
	}
}

// topLeftX returns the relative top left x coordinate of the HUDTexutre
//
float HUDTexture::topLeftX() const { 
	
	return coordinator->topLeftX() + coordinator->width() * tlx; 
}

// topLeftY returns the relative top left y coordinate of the HUDTexutre
//
float HUDTexture::topLeftY() const { 
	
	return coordinator->topLeftY() + coordinator->height() * tly; 
}

// bottomRightX returns the relative bottom right x coordinate of the HUDTexutre
//
float HUDTexture::bottomRightX() const { 
	
	return coordinator->topLeftX() + coordinator->width() * (brx-tlx); 
}

// bottomRightY returns the relative bottom right y coordinate of the HUDTexutre
//
float HUDTexture::bottomRightY() const { 
	
	return coordinator->topLeftY() + coordinator->height() * (bry-tly); 
}

// draw draws the HUDTexture string using the texture object
//
void HUDTexture::draw() const {
	if (showBG && background)
		background->draw(topLeftX(), topLeftY(), bottomRightX(),bottomRightY(), bgA);

	if (t)
		if (type == HUDT_STATIC)
			t->draw(topLeftX(), topLeftY(), bottomRightX(),bottomRightY(), a);
		else if (type == HUDT_PROGRESS)
		{
			if (curValue)
				t->draw(topLeftX(), topLeftY(), bottomRightX(),bottomRightY(), a, (curValue/maxValue));
		}
		else if (type == HUDT_SPRITE)
		{
			t->draw(topLeftX(), topLeftY(), bottomRightX(),bottomRightY(), a, saL, saR, saT, saB, saXMax, saYMax);
		}
}

//GMOK:  suspends suspends the texture associated with the HUDTexture object
void HUDTexture::suspend() const {

	if (t)
		t->suspend();

	if (background)
		background->suspend();

	if (rCValue)
		rCValue->suspend();
}

//GMOK:  release releases the texture associated with the HUDTexture object
void HUDTexture::release() const {

	if (t)
		t->release();

	if (background)
		background->release();

	if (rCValue)
		rCValue->release();
}

//GMOK:  destructor destroys the texture associated with this HUDTexture object
//GMOK:  and the HUDTexture stored in the object and removes the HUDTexture object
//GMOK:  from the HUD
HUDTexture::~HUDTexture() {

    if (t)
        t->Delete();
	if (background)
		background->Delete();
    if (coordinator)
        coordinator->remove(this);
    else
        error(L"HUDTexture::90 Couldn\'t access the HUD Coordinator");
}
