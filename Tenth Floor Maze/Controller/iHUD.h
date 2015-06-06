#ifndef _I_HUD_H_
#define _I_HUD_H_

/* HUD Interface - Heads Up Display Element - Model Branch
 *
 * iHUD.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iHUD ---------------------------------------
//
// iHUD is the Interface to the HUD Coordinator of the HUD Component
//
class iContext;
class iText;
class iTexture;
class iHUDTexture;

class iHUD {
  public:
	// initialization functions
    virtual void  initialize(int now)                    = 0;
	virtual bool  add(const iText* t)                    = 0;
    virtual bool  add(const iHUDTexture* t)              = 0;
	virtual void  reset(int now)                         = 0;
    virtual void  restore(int now)                       = 0;
	// execution functions
	virtual void  update(int now)                        = 0;
	virtual float topLeftX() const                       = 0;
	virtual float topLeftY() const                       = 0;
	virtual float width() const                          = 0;
	virtual float height() const                         = 0;
    virtual void  fps(int) const                         = 0;
    virtual void  draw() const                           = 0;
	// termination functions
    virtual void  suspend() const                        = 0;
	virtual void  release() const                        = 0;
	virtual bool  remove(const iText* t)                 = 0;
	virtual bool  remove(const iHUDTexture* t)           = 0;
    virtual void  Delete() const                         = 0;
};

extern "C"
iHUD* CreateHUD(iContext* c);

#endif
