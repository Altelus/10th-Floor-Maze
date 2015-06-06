#ifndef _INPUT_H_
#define _INPUT_H_

/* Input Declaration - Input Component - Direct Device Branch
 *
 * consists of Keyboard declaration
 *             Mouse    declaration
 *             Joystick declaration
 *
 * Input.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iInput.h"        // for the Keyboard, Mouse, and Joystick Interfaces

#define  WIN32_LEAN_AND_MEAN
#define  INITGUID          // enables access to GUIDs used by DirectInput
#include <dinput.h>        // for basic Direct Input
#undef   INITGUID

#include "Configuration.h" // for MAX_DESC

//------------------------------- Keyboard ------------------------------------
//
// The Keyboard Component represents the keyboard device amongst the Input 
// Components
//
class Keyboard : public iKeyboard {

	static const int SAMPLE_BUFFER_SIZE =  30;

    iContext*            context;      // points to the Context object
    LPDIRECTINPUT8       di;           // points to Direct Input object
    LPDIRECTINPUTDEVICE8 keyboard;     // points to Direct Input Keyboard

    Keyboard(void*, iContext*);
	Keyboard(const Keyboard& k);            // prevents copying
	Keyboard& operator=(const Keyboard& k); // prevents assignment
    virtual ~Keyboard();

  public:
	friend iKeyboard* CreateKeyboard(void*, iContext*);
	// initialization functions
    bool   setup(void*);
    bool   restore();
	// execution function
    void   retrieveInput();
	// termination functions
    void   suspend();
    void   release();
	void   Delete() const { delete this; }
};

//------------------------------- Mouse ---------------------------------------
//
// The Mouse Component represents the mouse device amonst the Input Components
//
class Mouse : public iMouse {

	static const int SAMPLE_BUFFER_SIZE = 30;

    iContext*            context;  // points to the Context object
	LPDIRECTINPUT8       di;       // points to the Direct Input object
    LPDIRECTINPUTDEVICE8 mouse;    // points to the Direct Input mouse

    Mouse(void*, iContext*);
	Mouse(const Mouse& m);            // prevents copying
	Mouse& operator=(const Mouse& m); // prevents assignment
    virtual ~Mouse();

  public:
	friend iMouse* CreateMouse(void*, iContext*);
	// initialization functions
    bool   setup(void*);
    bool   restore();
	// execution function
    void   retrieveInput();
    // termination functions
    void   suspend();
    void   release();
	void   Delete() const { delete this; }
};

//---------------------------------- Joystick ---------------------------------
//
// The Joystick Components represents the joystick device amongst the Input 
// Components
//
struct Controller {
	GUID    guid;
	wchar_t desc[MAX_DESC + 1];
    static int count;
};

class Joystick : public iJoystick {

    iContext*            context;  // points to the Context object
    LPDIRECTINPUT8       di;       // points to the Direct Input object
    LPDIRECTINPUTDEVICE8 joystick; // points to the Direct Input joystick

	// interrogation
	Controller* attached;          // holds descriptions of the attached 
								   // controllers

    // execution
    bool axisIsActive[4];          // is axis active?
    bool povIsActive;              // point of view is active?
    int  pointOfView[4];           // point of view
    bool reversey;                 // reverse direction of y axis

    Joystick(void*, iContext*);
	Joystick(const Joystick& j);            // prevents copying
	Joystick& operator=(const Joystick& j); // prevents assignment
    virtual ~Joystick();

  public:
	friend iJoystick* CreateJoystick(void*, iContext*);
	// interrogation functions
    bool   interrogate(void*);
    // initialization functions
    bool   setup(void*);
    bool   restore();
	// execution function
    void   retrieveInput();
    // termination functions
    void   suspend();
    void   release();
	void   Delete() const { delete this; }
};

#endif
