#ifndef _ENGINE_H_
#define _ENGINE_H_

/* Engine Declaration
 *
 * Engine.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iEngine.h" // for the Engine Interface

//-------------------------------- Engine -------------------------------------
//
// The Engine controls execution flow amongst the Framework Components
//
// Window Component
class iUserDialog;
class iWindow;
// Model Components
class iDesign;
class iScene;
class iViewing;
class iLighting;
class iHUD;
class iAudio;
// Direct Device Components
class iKeyboard;
class iMouse;
class iJoystick;
class iDisplay;
class iSoundCard;

class Engine : public iEngine {

    static iEngine* address;   // points to this object

    bool         active;        // engine is active?
    bool         isSetup;       // engine is setup?
    unsigned     now;           // time that framecount was last reset to 0
    unsigned     framecount;    // number of frames since 'now'
    unsigned     fps;           // frame rate per sec
    void*        hwnd;          // points to the main application window

    // Window Component
	iUserDialog* userDialog;    // points to the UserDialog object
    iWindow*     window;        // points to the Window object
    // Model Components
    iDesign*     design;        // points to the Design object
    iScene*      scene;         // points to the Scene object
    iViewing*    Viewing;       // points to the Viewing object
    iLighting*   lighting;      // points to the Lighting object
	iHUD*        hud;           // points to the Heads Up Display object
    iAudio*      audio;         // points to the Audio object
    // Direct-Device Components
    iKeyboard*   keyboard;      // points to the Keyboard object
    iMouse*      mouse;         // points to the Mouse object
    iJoystick*   joystick;      // points to the Joystick object
    iDisplay*    display;       // points to the Display object
    iSoundCard*  soundCard;     // points to the SoundCard object

    Engine(void*, int, iContext*);
	Engine(const Engine& m);            // prevents copying
	Engine& operator=(const Engine& m); // prevents assignment
    virtual ~Engine();
    void    setup();

  public:
    friend iEngine* CreateEngine(void*, int, iContext*);
    static iEngine* Address() { return address; }
	// configuration functions
    void   interrogate(void*);
	void   reset();
	// initialization function
    void   restore();
	// execution functions
    bool   isActive() const         { return active; }
	int    run();
    void   resize() const           { display->resize(); }
	// termination functions
    void   suspend();
	void   Delete() const           { delete this; address = 0; }
};

iEngine* EngineAddress() { return Engine::Address(); }

#endif