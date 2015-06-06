/* Engine Implementation  
 *                       
 * Engine.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iUserDialog.h"   // for the UserDialog Interface
#include "iWindow.h"       // for the Window Interface
#include "iInput.h"        // for the Keyboard, Mouse and Joystick Interfaces
#include "iHUD.h"          // for the HUD Interface
#include "iScene.h"        // for the Scene Interface
#include "iLighting.h"     // for the Lighting Interface
#include "iAudio.h"        // for the Audio Interface
#include "iDesign.h"       // for the Design Interface
#include "iViewing.h"      // for the Viewing Interface
#include "iDisplay.h"      // for the Display Interface
#include "iSoundCard.h"    // for the SoundCard Interface
#include "iUtilities.h"    // for error()

#include "Engine.h"        // for the Engine class declaration
#include "Configuration.h" // for NULL, MIN_ELAPSED_TIME, UNITS_PER_SEC

//-------------------------------- Engine -------------------------------------
//
// The Engine manages the flow of control through the Framework Components
//
iEngine* Engine::address = 0;

// CreateEngine creates the Engine Object and returns the address to its
// Interface
//
iEngine* CreateEngine(void* hinst, int show, iContext* context) {

    return Engine::address ? Engine::address : new Engine(hinst, show, context);
}

// Engine constructor creates the Model, Direct-Device and Windowing Components
//
Engine::Engine(void* hinst, int show, iContext* context) {

    address    = this;
 
	userDialog = CreateUserDialog(hinst, context);
    window     = CreateMainWindow(hinst, show, context);
    keyboard   = CreateKeyboard(hinst, context);
    mouse      = CreateMouse(hinst, context);
    joystick   = CreateJoystick(hinst, context);
    display    = CreateDisplay(context);
    soundCard  = CreateSoundCard(context);
    scene      = CreateScene(context);
    Viewing    = CreateViewing(context);
    lighting   = CreateLighting(context);
    audio      = CreateAudio(context);
	hud        = CreateHUD(context);
    design     = CreateDesign(context);

    now        = 0;
    framecount = 0;
    fps        = 0;
    active     = false;
    hwnd       = NULL;

    // set up the Engine
    setup();
}

// interrogate interrogates the Direct-Devices for available configurations 
//
void Engine::interrogate(void* hwnd) {

    display->interrogate(hwnd);
    joystick->interrogate(hwnd);
}

// setup configures the context for the user's choices, sets up the
// main application window, sets up the Direct-Device Components and 
// initializes the Model Components

void Engine::setup() {

    // configure the context using the user's selections
    if(userDialog->configureContext()) {

        // setup the main application window
        if (!(hwnd = window->setup()))
		    error(L"Engine::10 Failed to setup the Window Component");

        else {
	        // setup the Mouse Component - optional
	        if (!mouse->setup(hwnd))
		        error(L"Engine::11 Failed to setup the Mouse Component");

	        // setup the Joystick Component - optional
	        if (!joystick->setup(hwnd))
		        error(L"Engine::12 Failed to setup the Joystick Component");

	        // setup the Keyboard Component - necessary
	        if (!keyboard->setup(hwnd))
		        error(L"Engine::13 Failed to setup the Keyboard Component");

	        // setup the GraphicsCard Component - necessary
	        else if (!display->setup(hwnd))
		        error(L"Engine::14 Failed to set up the GraphicsCard Component");

	        // setup the Sound Card Component - necessary
	        else if (!soundCard->setup(hwnd))
		        error(L"Engine::15 Failed to set up the Sound Card Component");

	        else {
                // initialize the Model Components
                now = time();
                design->initialize(now);
                Viewing->initialize(now);
                hud->initialize(now);
                audio->initialize(now);
		        active = true;
                window->moveToForeground();
	        }
        }
    }
}

// restore restores the Model and Direct-Device Components
//
void Engine::restore() {

	// Direct-Device Components
    keyboard->restore();
	mouse->restore();
	joystick->restore();
	display->restore();

    // Model Components
    now = time();
	lighting->restore(now);
    Viewing->restore(now);
	hud->restore(now);
    design->restore(now);
	audio->restore(now);
	framecount = 0;
	active     = true;
}

// reset resets the Model, Direct-Device and Windowing Components
//
void Engine::reset() {

    // retrieve the user's choices and configure the context
    if(userDialog->configureContext()) {

        // release the device interfaces
        hud->release();
        scene->release();
        display->release();
        window->release();

        // set the configuration for the new window
        display->setConfiguration();

        // setup the main application window
        if (!(hwnd = window->setup()))
		    error(L"Engine::80 Failed to setup the Window Component");

        else {
	        // setup the Mouse Component - optional
	        if (!mouse->setup(hwnd))
		        error(L"Engine::81 Failed to reset the Mouse Component");

	        // setup the Joystick Component - optional
	        if (!joystick->setup(hwnd))
		        error(L"Engine::82 Failed to reset the Joystick Component");

	        // setup the Keyboard Component - necessary
	        if (!keyboard->setup(hwnd))
		        error(L"Engine::83 Failed to reset the Keyboard Component");

	        // setup the Graphics Card Component - necessary
	        if (!display->setup(hwnd))
		        error(L"Engine::84 Failed to reset the GraphicsCard Component");

	        else {
		        // reset the Model Components
                now = time();
                design->reset(now);
                Viewing->reset(now);
		        hud->reset(now);
		        audio->reset(now);
                // reset the frame count
		        framecount = 0;
                fps        = 0;
                active     = true;
                window->moveToForeground();
	        }
        }
    }
}

// run handles system messages, retrieves user input, updates the model 
// components, renders the new frame, and plays/stops any sounds that 
// are ready to start/stop
//
// asks the Window Component if there is a message in the message queue
// if there is, lets the Window Component handle the message
// if there isn't and the Engine is inactive, adopts a waiting state
// if there isn't and the Engine is active, performs an event cycle
//
int Engine::run() {

	int  rc        = 0;
    bool keepgoing = active;

	while (keepgoing) {
        // all system messages have priority
		if (window->handleMessage(rc, keepgoing)) 
			; // intentional
        // shift into a waiting state
		else if (!active) 
			window->wait(); 
        // room to create a frame
		else {
	        // if sufficient time has elapsed since the last frame
            int rightNow = time();
	        if (rightNow - now >= MIN_ELAPSED_TIME) {
		        // create a new frame
		        //
		        // (Re)compute the frame rate every second or so
		        if (rightNow - now <= UNITS_PER_SEC) 
			        framecount++;
		        else {
                    // report the average
                    int fpsnew = (framecount * UNITS_PER_SEC) / (rightNow - now);
                    fps        = (fps + fpsnew) / 2;
                    hud->fps(fps);
                    fps        = fpsnew;
			        framecount = 0;
			        now        = rightNow;
		        }
                // retrieve user input, if any
	            keyboard->retrieveInput();
	            mouse->retrieveInput();
	            joystick->retrieveInput();

                // update the model components
                design->update(rightNow);
	            Viewing->update(rightNow);
	            audio->update(rightNow);
	            lighting->update();
	            hud->update(rightNow);

	            // draw the scene
                display->beginDraw();
                // draw the opaque scene objects
                scene->draw(true);
                // then the translucent/transparent objects
                display->alphaBlendOn();
                scene->draw(false);
                display->alphaBlendOff();

                // draw the HUD
                display->beginSuperimpose();
                hud->draw();
                display->endDraw();

	            // update the listener
                soundCard->update();
	            // play the audio
                audio->play(rightNow);
	        }
        }
	}

    return rc;
}

// suspend suspends the Model and Direct-Device Components
//
void Engine::suspend() {

	// Model Components
    hud->suspend();
	audio->suspend();
	lighting->suspend();
	scene->suspend();

    // Direct-Device Components
	display->suspend();
	joystick->suspend();
	mouse->suspend();
	keyboard->suspend();

    active = false;
}

// destructor deletes the Model and Direct-Device Components
//
Engine::~Engine() {

	// Model Components
    design->Delete();
    hud->Delete();
    audio->Delete();
    lighting->Delete();
    Viewing->Delete();
    scene->Delete();

    // Direct-Device Components
    soundCard->Delete();
    display->Delete();
    joystick->Delete();
    mouse->Delete();
    keyboard->Delete();

    // Windowing Components
	window->Delete();
	userDialog->Delete();
}

