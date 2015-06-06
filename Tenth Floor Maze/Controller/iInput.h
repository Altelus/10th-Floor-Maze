#ifndef _I_INPUT_H_
#define _I_INPUT_H_

/* Input Interface - Input Component - Direct Device Branch
 *
 * consists of iKeyboard Interface
 *             iMouse Interface
 *             iJoystick Interface
 *
 * Input.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//------------------------------- iKeyboard -----------------------------------
//
// iKeyboard is the Interface to the Keyboard Component
//
class iContext;

class iKeyboard {
  public:
	// initialization functions
    virtual bool  setup(void* hwnd)                   = 0;
    virtual bool  restore()                           = 0;
	// execution function
    virtual void  retrieveInput()                     = 0;
	// termination functions
    virtual void  suspend()                           = 0;
    virtual void  release()                           = 0;
    virtual void  Delete() const                      = 0;
};

extern "C"
iKeyboard* CreateKeyboard(void*, iContext*);

//------------------------------- iMouse --------------------------------------
//
// iMouse is the Interface to the Mouse Component
//
class iMouse {
  public:
	// initialization functions
    virtual bool setup(void* hwnd)                                   = 0;
    virtual bool restore()                                           = 0;
	// execution functions
    virtual void retrieveInput()                                     = 0;
	// termination functions
    virtual void suspend()                                           = 0;
    virtual void release()                                           = 0;
    virtual void Delete() const                                      = 0;
};

extern "C"
iMouse* CreateMouse(void*, iContext*);

//---------------------------------- iJoystick --------------------------------
//
// iJoystick is the Interface to the Joystick Component
//
class iJoystick {
  public:
	// interrogation functions
    virtual bool interrogate(void*)                                = 0;
	// initialization functions
    virtual bool setup(void*)                                      = 0;
    virtual bool restore()                                         = 0;
	// execution function
    virtual void retrieveInput()                                   = 0;
	// termination functions
    virtual void suspend()                                         = 0;
    virtual void release()                                         = 0;
    virtual void Delete() const                                    = 0;
};

extern "C"
iJoystick* CreateJoystick(void*, iContext*);

#endif
