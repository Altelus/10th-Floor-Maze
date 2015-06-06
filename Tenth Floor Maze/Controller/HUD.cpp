/* HUD Implementation - Heads Up Display Element - Model Branch
 *
 * HUD.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"      // for the Context Interface
#include "iTexture.h"      // for the Texture Interface
#include "iHUDTexture.h"   // for HUDTexture Interface
#include "iUtilities.h"    // for error()

#include "HUD.h"           // for the HUD class declaration
#include "Text.h"          // for Text::isCoordinatedBy
#include "HUDTexture.h"    // for HUDTexture::isCoordinatedBy

//-------------------------------- HUD ----------------------------------------
//
// The HUD Coordinator manages the text items in the HUD Component
//
// CreateHUD creates the HUD object, which implements the HUD Coordinator
//
iHUD* CreateHUD(iContext* c) {

	return new HUD(c);
}

// constructor initializes the pointers to the Text Instances, sets the HUD size
// and position, initializes the reference time and attaches the HUD object to
// the Text class
//
HUD::HUD(iContext* c) : context(c) {

	// initialize the Text object pointers
	noTexts = 0;
    for (int i = 0; i < MAX_TEXTS; i++)
        text[i] = NULL;

	//GMOK: initial the HUDTextures
	noHUDTextures = 0;
	for (int i = 0; i < MAX_HUDTEXTURES; i++){
		hTexture[i] = NULL;
	}

	tlx        = HUD_X;
	tly        = HUD_Y;
	rw         = HUD_W;
	rh         = HUD_H;
	validate();

	on         = true;

	// reference time
    lastUpdate = 0;
	lastToggle = 0;

	// coordinates the Objects
	Text::isCoordinatedBy(this);
	HUDTexture::isCoordinatedBy(this);
}

// validate keeps the HUD within the client area
//
void HUD::validate() {

	if (tlx < TL_MIN) 
		tlx = TL_MIN;
    else if (tlx > TL_MAX) 
		tlx = TL_MAX;
    if (tly < TL_MIN) 
		tly = TL_MIN;
    else if (tly > TL_MAX) 
		tly = TL_MAX;
    if (rw < R_MIN) 
		rw = R_MIN;
    else if (rw + tlx > TL_MAX && rw < TL_MAX) 
		tlx = TL_MAX - rw;
    else if (rw + tlx > TL_MAX) 
		rw = TL_MAX - tlx;
    if (rh < R_MIN) 
		rh = R_MIN;
    else if (rh + tly > TL_MAX && rh < TL_MAX) 
		tly = TL_MAX - rh;
    else if (rh + tly > TL_MAX) 
		rh = TL_MAX - tly;
}

// add adds to the HUD Coordinator a pointer to Text *t
// and returns true if successful, false otherwise
//
bool HUD::add(const iText* t) {

    int i;
    bool rc = false;

    for (i = 0; i < noTexts; i++)
        if (!text[i]) {
            text[i] = t;
            i = noTexts + 1;
            rc = true;
        }
    if (i == noTexts && noTexts < MAX_TEXTS) {
        text[noTexts++] = t;
        rc = true;
    }

    return rc;
}

//GMOK:  add adds to the HUD Coordinator a pointer to HUDTexture
//GMOK:  and returns true if successful, false otherwise
//
bool HUD::add(const iHUDTexture* t) {

    int i;
    bool rc = false;

    for (i = 0; i < noHUDTextures; i++)
        if (!hTexture[i]) {
            hTexture[i] = t;
            i = noHUDTextures + 1;
            rc = true;
        }
    if (i == noHUDTextures && noHUDTextures < MAX_HUDTEXTURES) {
        hTexture[noHUDTextures++] = t;
        rc = true;
    }

    return rc;
}

// initialize sets the reference time
//
void HUD::initialize(int now) {

    lastUpdate = now;
	lastToggle = now;
	
	//Create background texture
	//iHUDTexture *bground =  CreateHUDTexture(0.0f,0.0f,1.0f,1.0f,HUD_A_DEFAULT, HUDT_STATIC);
	//bground->set(CreateTexture(HUD_PROGRESS_BLUE));

	fpsText    = CreateText(0, 0, 1.0f, 0.1f, TXT_DEFAULT);
}

// restore restores the Text objects within the HUD Component and
// re-initializes the reference time
//
void HUD::restore(int now) {

    for (int i = 0; i < noTexts; i++)
        if (text[i])
			text[i]->restore();

    lastUpdate = now;
}

// reset reinitializes the reference time 
//
void HUD::reset(int now) {

    lastUpdate = now;
}

// update toggles the on/off state of the HUD Component and translates the HUD
// image with its Text objects according to the user's interventions
//
void HUD::update(int now) {

	int dx = 0, dy = 0;
	int delta = now - lastUpdate;
	lastUpdate = now;

	// update the on/off state
	if (context->pressed(HUD_DISPLAY) && now - lastToggle > MODEL_LATENCY) {
        on         = !on;
        lastToggle = now;
    }

	if (on) {
		// translate the HUD only if it is on
		if (context->pressed(HUD_RIGHT))
			dx += delta;
		if (context->pressed(HUD_LEFT))
			dx -= delta;
		if (context->pressed(HUD_UP))
			dy -= delta;
		if (context->pressed(HUD_DOWN))
			dy += delta;
		tlx += dx * HUD_SPEED;
		tly += dy * HUD_SPEED;
		validate();
	}
}

// resetFps resets the Text string that reports the frame rate
//
void HUD::fps(int fps) const {

	wchar_t str[MAX_DESC + 1];
	sprintf(str, fps, L" fps");
	fpsText->set(str);
}

// draw draws the HUD background and all of the Text objects
//
void HUD::draw() const {

	if (on) {
		//GMOK:  draw each HUDTexture object
		for (int i = 0; i < noHUDTextures; i++)
			if (hTexture[i]) 
				hTexture[i]->draw();

		// draw each Text object
		for (int i = 0; i < noTexts; i++) if (text[i]) text[i]->draw();
	}
}

// suspend suspends the Text objects
//
void HUD::suspend() const {
    // suspend the Text objects
    for (int i = 0; i < noTexts; i++) if (text[i]) text[i]->suspend();

	//GMOK: suspend the HUDTextures
	for (int i = 0; i < noHUDTextures; i++)
		if (hTexture[i])
			hTexture[i]->suspend();
}

// remove removes the pointer to Text *t from the HUD Coordinator
// and returns true if successful, false otherwise
//
bool HUD::remove(const iText* t) {
    bool rc = false;
    for (int i = 0; i < noTexts; i++)
        if (text[i] == t) {
            text[i] = NULL;
            rc = true;
        }
    while (!text[noTexts - 1]) noTexts--;
    return rc;
}

//GMOK: remove removes the pointer to HUDTexture from the HUD Coordinator
//GMOK: and returns true if successful, false otherwise
//
bool HUD::remove(const iHUDTexture* t) {

    bool rc = false;

    for (int i = 0; i < noHUDTextures; i++)
        if (hTexture[i] == t) {
            hTexture[i] = NULL;
            rc = true;
        }
    while (!hTexture[noHUDTextures - 1])
        noHUDTextures--;

    return rc;
}


// release releases the objects within the HUD Component
//
void HUD::release() const {
    for (int i = 0; i < noTexts; i++) {
        if (text[i]) text[i]->release();
    }

    for (int i = 0; i < noHUDTextures; i++) {
        if (hTexture[i]) 
			hTexture[i]->release();
    }
}

// destructor destroys the objects within the HUD Component
//
HUD::~HUD() {

    suspend(); 

    // destroy each text item
	for (int i = 0; i < noTexts; i++)
        if (text[i]) 
			text[i]->Delete();

	//GMOK: destroy each HUDTexture
	for (int i = 0; i < noHUDTextures; i++)
		if (hTexture[i]) {
			hTexture[i]->Delete();
		}
}
