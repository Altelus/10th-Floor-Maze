/* SoundCard Implementation - SoundCard Component - Direct Device Branch
 *
 * SoundCard.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"        // for the Context Interface
#include "iUtilities.h"      // for error()

#include "SoundCard.h"       // for the SoundCard class declaration
#include "Segment.h"         // for Segment::connectsThrough()
#include "MathDefinitions.h" // for Vector
#include "Configuration.h"   // for SOUND_DISTANCE_FACTOR

const GUID GUID_NULL = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };

//------------------------------- SoundCard -----------------------------------
//
// The SoundCard Portal manages the API connectivity for the SoundCard 
// Component
//
// CreateSound creates the SoundCard object, which implements the SoundCard 
// Portal
//
iSoundCard* CreateSoundCard(iContext* c) {

	return new SoundCard(c);
}

// constructor initializes the instance pointers and attaches the 
// SoundCard class to the Segment class
//
SoundCard::SoundCard(iContext* c) : context(c) {

    mperf              = NULL;
    loader             = NULL;
    listener           = NULL;
    ambientAudioPath   = NULL;
    listenerAudioPath  = NULL;
    buffer             = NULL;

    CoInitialize(NULL);

	// provides the API connectivity for the Segment objects
	Segment::connectsThrough(this);
}

// setup creates the performance object, the default audio path, the
// audio path for non-local sounds, the audio path for the listener, the
// loader for creating segments from sound files and extracts the buffer
// from the non-local audio path and the listener from the listener audio
// path
//
bool SoundCard::setup(void* hwnd) {

    bool rc = false;

    // obtain an Interface to the music performance object
    if (S_OK != CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
     CLSCTX_INPROC, IID_IDirectMusicPerformance8, (void **)&mperf)) {
        error(L"SoundCard::10 Couldn\'t make the music performance object");
    }
    // initialize the performance object, creating the default audio path
    else if (FAILED(mperf->InitAudio(NULL, NULL, (HWND)hwnd, 
     DMUS_APATH_DYNAMIC_MONO, 1, DMUS_AUDIOF_ALL, NULL))) {
        error(L"SoundCard::11 Couldn\'t initialize the performance object");
        release();
    }
    // create another audio path for the ambient (non-local) sounds
    else if (FAILED(mperf->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_MONO,
     1, TRUE, &ambientAudioPath))) {
        error(L"SoundCard::12 Couldn\'t make an audio path for ambient "
         L"sounds");
        release();
    }
    // extract the buffer from the audio path created for ambient sounds
    else if (FAILED(ambientAudioPath->GetObjectInPath(DMUS_PCHANNEL_ALL,
     DMUS_PATH_BUFFER, 0, GUID_NULL, 0, IID_IDirectSoundBuffer8,
     (void **)&buffer))) {
        error(L"SoundCard::13 Couldn\'t get the buffer from ambient audio "
         L"path");
        release();
    }
    // create another audio path for listening to local sounds
    else if (FAILED(mperf->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_3D,
     1, TRUE, &listenerAudioPath))) {
        error(L"SoundCard::14 Couldn\'t make an audio path for the listener");
        release();
    }
    // extract the listener from the audio path created for local sounds
    else if (FAILED(listenerAudioPath->GetObjectInPath(0,
     DMUS_PATH_PRIMARY_BUFFER, 0, GUID_NULL, 0, IID_IDirectSound3DListener8,
     (void **)&listener))) {
        error(L"SoundCard::15 Couldn\'t make a listener for the local sounds");
        release();
    }
    // create a music loader to read .WAV or MIDI files into segments
    else if (S_OK != CoCreateInstance(CLSID_DirectMusicLoader, NULL,
     CLSCTX_INPROC, IID_IDirectMusicLoader8, (void **)&loader)) {
        error(L"SoundCard::16 Couldn\'t create a music loader");
        release();
    }
    else {
        // set the number of meters in a vector unit - default is 1.0
        listener->SetDistanceFactor(SOUND_DISTANCE_FACTOR, DS3D_DEFERRED);

        DWORD freq;
        // extract the idle frequency of the ambient audio path
        buffer->GetFrequency(&freq);
        // set the frequency and volume range of the context
        context->set(GF_AU_FREQ, int(freq));
        context->set(GF_AU_MXVL, DSBVOLUME_MAX);
        context->set(GF_AU_MNVL, DSBVOLUME_MIN);

        rc = true;
    }

    return rc;
}

// update updates the buffer for the current frequency and volume and the 
// listener to reflect the current view - commits the deferred settings in
// preparation for implementing the updates
//
void SoundCard::update() {

    // check that the buffer has been created
    if (buffer) {
        // update the frequency of the ambient audio path
        buffer->SetFrequency(context->get(GF_AU_FREQ));

        // update the volume of the ambient audio path
        buffer->SetVolume(context->get(GF_AU_CVOL));
	}

	// check that the listener has been created
    if (listener) {
        // update the listener's position and orientation
        Vector p = context->get(GF_CA_POSN);
        Vector h = context->get(GF_CA_HEAD);
        Vector u = context->get(GF_CA_UP  );
        // DirectSound uses the lhs coordinate system
        listener->SetPosition(p.x, p.y, p.z, DS3D_DEFERRED);
        listener->SetOrientation(h.x, h.y, h.z, u.x, u.y, u.z, DS3D_DEFERRED);
        // commit all deferred settings
        listener->CommitDeferredSettings();
    }
}

// release disengages the Interfaces to the COM objects used for the
// performance and closes down the performance
//
void SoundCard::release() {

	// release the performance
	if (mperf) {
        if (listener) {
            listener->Release();
            listener = NULL;
        }
        if (listenerAudioPath) {
            listenerAudioPath->Release();
            listenerAudioPath = NULL;
        }
        if (buffer) {
            buffer->Release();
            buffer = NULL;
        }
        if (ambientAudioPath) {
            ambientAudioPath->Release();
            ambientAudioPath = NULL;
        }
        if (loader) {
            loader->Release();
            loader = NULL;
        }
        mperf->CloseDown();
        mperf->Release();
        mperf = NULL;
    }
}

// destructor stops the performance and releases the performance
// objects
//
SoundCard::~SoundCard() {

	// stop the entire performance
    if(mperf) mperf->Stop(NULL, NULL, 0, 0);
	// close down the performance
    release();
	// wrap up
    CoUninitialize();
}
