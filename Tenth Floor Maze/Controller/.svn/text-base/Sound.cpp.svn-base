/* Sound Implementation - Audio Component - Model Branch
 *
 * Sound.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iAudio.h"           // for Audio Interface
#include "iText.h"            // for Text Interface
#include "iSegment.h"         // for Segment Interface
#include "iFrame.h"           // for Frame Interface
#include "iUtilities.h"       // for nameWithDir(), error()

#include "Sound.h"            // for Sound class declaration
#include "MathDeclarations.h" // for Vector
#include "ModelSystem.h"      // for MODEL_Z_AXIS
#include "ModelSettings.h"    // for AUDIO_DIRECTORY

//------------------------------- Sound ------------------------------------
//
// The Sound Primitive represents a sound in the Audio Component
//
// The Audio Coordinator manages the Sound Instances
//
iAudio* Sound::coordinator = NULL;

// CreateSound creates a sound object associated with file f in directory
// AUDIO_DIRECTORY and with the following properites: type t, continuous c, 
// on o, sound cone q in degrees
//
iSound* CreateSound(const wchar_t* f, SoundType t, bool c, bool o, 
 float q) {

	return new Sound(f, t, c, o, q);
}

iSound* Clone(const iSound* src) { 
    
    return src->clone();
}

// constructor adds the sound to the Audio Component, creates the sound
// segment, stores the name of the sound file relative to the execution
// directory, positions the sound, if local or mobile, at the origin of
// world space and initializes the reference time
//
Sound::Sound(const wchar_t* f, SoundType t, bool c, bool o, float q) : 
 type(t), continuous(c), on(o), cone(q), frame(NULL), text(NULL),
 overwrite(false) {

    if (!coordinator)
        error(L"Sound::00 Couldn\'t access the Audio Coordinator");
    else if(!coordinator->add(this))
        error(L"Sound::01 Couldn\'t add the sound to the Audio Coordinator");

    // sound segment on the sound device
	segment = CreateSegment();

	// store filename (without/with path)
	int len = strlen(f);
	relFile = new wchar_t[len + 1];
	strcpy(relFile, f, len);
	// add the directory to create the relative filename
	len += strlen(AUDIO_DIRECTORY) + 1;
	dirFile = new wchar_t[len + 1];
	nameWithDir(dirFile, AUDIO_DIRECTORY, f, len);

	// prepare to start playing
    setToStart = continuous && on;
    setToStop  = false;

	// initialize reference time
	lastToggle = 0;
}

// copy constructor initializes the instance variables and calls the
 // assignment operator
//
Sound::Sound(const Sound& src) {

    if (!coordinator)
        error(L"Sound::00 Couldn\'t access the Audio Coordinator");
    else if(!coordinator->add(this))
        error(L"Sound::01 Couldn\'t add the sound to the Audio Coordinator");

	segment = NULL;
	relFile = NULL;
	dirFile = NULL;
	*this   = src;
}

// assignment operator discard old sound segment and copies over
// data from src - does not copy over the Segment object from src
// but instead creates a new Segment object for the current sound
// object - does not copy over the Frame or the Text objects attached
// to the current object but instead initializes them to NULL
//
Sound& Sound::operator=(const Sound& src) {

	if (this != &src) {
        *((Frame*)this) = src;
		if (segment)
			segment->Delete();
		if (relFile)
			delete [] relFile;
		if (dirFile)
			delete [] dirFile;
        if (src.segment)
		    segment = src.segment->clone();
        else    
            segment = NULL;
		int len    = strlen(src.relFile);
		relFile    = new wchar_t[len + 1];
		strcpy(relFile, src.relFile, len);
		len        = strlen(src.dirFile);
		dirFile    = new wchar_t[len + 1];
		strcpy(dirFile, src.dirFile, len);
		type       = src.type == MOBILE_SOUND ? LOCAL_SOUND : src.type;
		on         = false;
		continuous = src.continuous;
		cone       = src.cone;
		overwrite  = src.overwrite;
		setToStart = src.on;
		setToStop  = false;
		lastToggle = 0;
        if (src.frame)
            integrate(src.frame);
    	frame      = NULL;
		text       = NULL;
	}

	return *this;
}

// attach attaches Frame *f to the sound
//
void Sound::attach(const iFrame* f) {

	if (type == MOBILE_SOUND)
		frame = f;
}

// attach attaches Text* t to the sound
//
void Sound::attach(const iText* t) {

	text = t;
}

// change changes the source file for the sound
//
void Sound::change(const wchar_t* f) {

	if (f) {
		//stop the current sound
		if (segment) {
			const_cast<iSegment*>(segment)->stop(this);
			const_cast<iSegment*>(segment)->release();
		}
		// store filename (without/with path)
		int len = strlen(f);
		if (relFile) 
			delete [] relFile;
		relFile = new wchar_t[len + 1];
		strcpy(relFile, f, len);
		// add the directory to create the relative filename
		if (dirFile) 
			delete [] dirFile;
		len += strlen(AUDIO_DIRECTORY) + 1;
		dirFile = new wchar_t[len + 1];
		nameWithDir(dirFile, AUDIO_DIRECTORY, f, len);
	}
}

// restore reinitializes the time of the last toggle
//
void Sound::restore(int now) {

	// reference time
	lastToggle = now;
}

// position returns the position of the Sound in world space
//
Vector Sound::position() const {

    Vector v;

    if (frame)
        v = Frame::position() * frame->world();
    else
        v = Frame::position();

    v.z *= MODEL_Z_AXIS;

    return v;
}

// orientation returs the heading of the Sound in world space
//
Vector Sound::orientation() const {

    Vector h;

    if (frame)
        h = Frame::orientation('z') * frame->rotation();
    else
        h = Frame::orientation('z');

    h.z *= MODEL_Z_AXIS;

    return h;
}

// toggle toggles the sound if the latency period has elapsed
//
bool Sound::toggle(int now) {
	//bool rc = true;
	//setToStop = true;
	//setToStart = true;
	bool rc = false;

    if (now - lastToggle > SOUND_LATENCY) {
        if (on)
            setToStop = true;
        else
            setToStart = true;
        lastToggle = now;
		rc = true;
    }

	return rc;
}
void Sound::forcePlay() {
	setToStop = true;
	setToStart = true;
}

// update updates the position and orientation of the Sound Instance
//
void Sound::update() const {

	if (segment)
		if (type == MOBILE_SOUND && frame || type == LOCAL_SOUND) 
			const_cast<iSegment*>(segment)->update(this);
}

// play starts or stops the playing of the sound segment
//
void Sound::play(int now) {

	if (setToStart) {
		if (segment) 
			const_cast<iSegment*>(segment)->play(this, type == GLOBAL_SOUND, continuous);
		setToStart = false;
		setToStop  = false;
		on         = true;
		overwrite  = !continuous;
	}
	else if (setToStop) {
		if (segment) const_cast<iSegment*>(segment)->stop(this);
		setToStart = false;
		on         = false;
	}

	// overwrite associated text if sufficient time has elapsed
	//
	if (overwrite && now > lastToggle + SND_OVERWRITE * SOUND_LATENCY) {
		const_cast<iSegment*>(segment)->status(this);
		overwrite = false;
	}
}

// report sets the text string associated with the status of the sound
//
void Sound::report(bool on) const {

	if (text)
		const_cast<iText*>(text)->set(on ? SND_TXT_ON : SND_TXT_OFF);
}

// suspend stops the playing of the sound segment and prepares the sound
// to start playing upon restoration if the sound is continuous and set 
// to start or on
//
void Sound::suspend() {

	if (segment) 
		const_cast<iSegment*>(segment)->stop(this);
	setToStart = continuous && (setToStart || on);
	on         = false;
}

// destructor deletes the sound segment and removes the sound
// from the Audio Component
//
Sound::~Sound() {

	if (dirFile)
		delete [] dirFile;
	if (relFile)
		delete [] relFile;
    if (segment) 
		segment->Delete();
    if (coordinator)
        coordinator->remove(this);
    else
        error(L"Sound::90 Couldn\'t access the Audio Coordinator");
}


