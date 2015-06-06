/* Segment Implementation - SoundCard Component - Direct Device Branch
 *
 * Segment.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iAudio.h"           // for the Audio Interface
#include "iSound.h"           // for the Sound Interface
#include "iUtilities.h"       // for error()

#include "Segment.h"          // for Segment class declaration
#include "SoundCard.h"        // for SoundCard instance variables
#include "MathDeclarations.h" // for Vector, MODEL_Z_AXIS
#include "Configuration.h"    // for INTERIOR_CONE, ATTENUATION_DISTANCE_FACTOR

const GUID GUID_NULL = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };

//-------------------------------- Segment ------------------------------------
//
// The Segment Primitive represents a Sound in the Sound Card Component
//
// The SoundCard object provides the API connectivity for the Segment objects
//
SoundCard* Segment::soundCard = NULL; 

// CreateSegment creates a Segment object, which implements the Segment Primitive
//
iSegment* CreateSegment() {

	return new Segment();
}

// constructor initializes the instance pointers
//
Segment::Segment() {

    segment   = NULL;
    audioPath = NULL;
    buffer    = NULL;
}

Segment::Segment(const Segment& src) {

    segment   = NULL;
    audioPath = NULL;
    buffer    = NULL;
    *this = src;
}

Segment& Segment::operator=(const Segment& src) {

    if (this != &src) {
        release();
        segment   = NULL;
        audioPath = NULL;
        buffer    = NULL;
    }

    return *this;
}

// setup creates the sound segment from the sound file and in the
// case of a non-global sound creates a 3d audio path and extracts 
// the 3d buffer from that path 
//
bool Segment::setup(const iSound* sound, bool global, bool continuous) {

    bool rc = true;

    // if this is a global sound use the ambient audio path
    if (global) {
        audioPath = soundCard->ambientAudioPath;
        audioPath->AddRef();
    }
    // if this is a local sound create a separate 3d audio path and 
    // extract its buffer
	//
    else if (!audioPath && FAILED(soundCard->mperf->CreateStandardAudioPath(
	 DMUS_APATH_DYNAMIC_3D, 1, TRUE, &audioPath))) {
        error(L"Segment::10 Couldn\'t make audio path for sound file ",
		 sound->relFileName());
        release();
		rc = false;
    }
    // extract the 3d buffer from the 3d audio path
    else if (!buffer && FAILED(audioPath->GetObjectInPath(
	 DMUS_PCHANNEL_ALL, DMUS_PATH_BUFFER, 0, GUID_NULL, 0, 
	 IID_IDirectSound3DBuffer, (void **)&buffer))) {
        error(L"Segment::11 Couldn\'t get the buffer for sound file ", 
		 sound->relFileName());
        release();
		rc = false;
    }

    // create the sound segment from the sound file
    //
	if (rc && !segment && FAILED(soundCard->loader->LoadObjectFromFile(
	 CLSID_DirectMusicSegment, IID_IDirectMusicSegment8, 
	 const_cast<WCHAR*>(sound->dirFileName()), (void **)&segment))) {
        error(L"Segment::14 Couldn\'t load sound file ",
		 sound->relFileName());
        rc = false;
    }
    else if (rc) {
        // download the segment to the music performance
        segment->Download(soundCard->mperf);
        if (continuous)
            segment->SetRepeats(DMUS_SEG_REPEAT_INFINITE);

        // initialize the 3d parameters through the 3d buffer
        if (buffer) {
            // distance from listener at which attenuation of sound begins
            buffer->SetMinDistance(DS3D_DEFAULTMINDISTANCE *
             ATTENUATION_DISTANCE_FACTOR, DS3D_DEFERRED);
            // attenuation outside cone (DSBVOLUME_MIN < < DSBVOLUME_MAX)
            buffer->SetConeOutsideVolume(DSBVOLUME_MIN, DS3D_DEFERRED);
            // sound cones - interior, outside - in degrees - default is
            // 360 for both if sound cone is 0
            if (sound->coneAngle())
                buffer->SetConeAngles(unsigned(INTERIOR_CONE * 
				 sound->coneAngle()), unsigned(sound->coneAngle()), 
				 DS3D_DEFERRED);
            // implement the sound's position and orientation
			sound->update();
        }
    }

    return rc;
}

// update updates the position and the orientation of the segment
//
void Segment::update(const iSound* sound) {

    if (buffer) {
        Vector p = sound->position();
        Vector h = sound->orientation();
        // DirectSound uses lhs coordinate system 
        buffer->SetPosition(p.x, p.y, p.z, DS3D_DEFERRED);
        buffer->SetConeOrientation(h.x, h.y, h.z, DS3D_DEFERRED);
        // settings are committed through listener in soundCard
		// immediately after all Segments have been updated
    }
}

// play starts playing the segment on the audioPath, sets up the
// segment if necessary
//
void Segment::play(const iSound* sound, bool global, bool continuous) {

    // create the segment if it doesn't yet exist
    if (!segment) setup(sound, global, continuous);

	if (segment) {
		soundCard->mperf->PlaySegmentEx(segment, NULL, NULL, 
		 DMUS_SEGF_SECONDARY, 0, NULL, NULL, audioPath);
		sound->report(true);
	}
}

// status checks if the sound is playing and reports that it is off once
// it stops playing
//
void Segment::status(const iSound* sound) const {

	sound->report(false);
}

// stop stops playing the segment
//
void Segment::stop(const iSound* sound) {

	if(segment) {
        soundCard->mperf->StopEx(segment, 0, 0);
		sound->report(false);
	}
}

// release releases the segment, the pointer to its audiopath
// and the dedicated buffer
//
void Segment::release() {

    if (segment) {
        segment->Release();
        segment = NULL;
    }
    if (buffer) {
        buffer->Release();
        buffer = NULL;
    }
    if (audioPath) {
        audioPath->Release();
        audioPath = NULL;
    }
}

// destructor deactivates the audio path, unloads the segment and
// closes down the segment
//
Segment::~Segment() {

    // unload the segment from its audio path
	if(audioPath) {
        audioPath->Activate(FALSE);
        if(segment) segment->Unload(audioPath);
    }
	// close down the segment
    release();
}


