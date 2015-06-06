#ifndef _DESIGN_H_
#define _DESIGN_H_

/* Design Declaration - Model Branch
 *
 * Design.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iDesign.h" // for the Design Interface
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "Configuration.h"	// for MAX_TRAPS...

//-------------------------------- Design -------------------------------------
//
// The Design Component holds the game design proper
//
class iObject;
class iLight;
class iSound;
class iText;
class iHUDTexture;
class iEnvironment;

class Design : public iDesign {

	iContext* context;         // points to the Context object

	iEnvironment* environment; //GMOK: adjust environment (IE. fog)
	
	/* temporary variables/objects for debugging purpose */
	iText*		camera_text;
	iText*		line1;
	iText*		line2;
	iText*		line3;
	iText*		healthLine;	// AKV

	iHUDTexture* speedUPBar;
	iHUDTexture* dexterityBar;
	iHUDTexture* revertCollapseBar;
	iHUDTexture* stopCollapseBar;
	iHUDTexture* healthBar;		// AKV - player's health bar
	iText*		 healthDisplay;	// AKV - player's health display

	//GMOK: HUD animated sprite
	iHUDTexture* testSprite;

	//GMOK: Billboard
	int tIndex;				//GMOK: index of texture to be displayed
	int billLastUpdate;		//GMOK: last update of billboard animation
	iTexture* btTexture[5]; //GMOK: each texture represents a frame of movement for the billboard

	iObject*	torch1;		//GMOK: Torch billboard
	iObject*	torch2;

	iHUDTexture*	speedUpIcon;	//RYAN: added icon textures
	iHUDTexture*	dexterityIcon;
	iHUDTexture*	revertCollapseIcon;
	iHUDTexture*	stopCollapseIcon;
	iText*			speedUpText;	//RYAN: added item status texts 
	iText*			dexterityText;
	iText*			revertCollapseText;
	iText*			stopCollapseText;
	bool			itemTextInitialized;
	iText*			staminaDisplay;
	iText*			distanceDisplay;
	iText*			timeDisplay;
	iHUDTexture*	staminaBar;
	int				goal_index_x;
	int				goal_index_z;

	/* temporary variables/objects for debugging purpose */

	iObject*	main_character;			// RYAN: Main character object
	iCamera*	main_character_camera;	// RYAN: Main character camera
	bool		isStaminaGame;			// RYAN: Slows down the speed when fainting
	
	int			startCoordinateX;		// RYAN: Start coordinate X
	int			startCoordinateZ;		// RYAN: Start coordinate Z
	int			startTileIndexX;		// RYAN: Starting tile index X
	int			startTileIndexZ;		// RYAN: Starting tile index Z
	int			previousTileIndexX;		// RYAN: Previous tile index X
	int			previousTileIndexZ;		// RYAN: Previous tile index Z
	float		stageHeight;			// RYAN: Ceiling level.
	int			numTilesX;				// RYAN: Number of tiles X
	int			numTilesZ;				// RYAN: Number of tiles Z
	
	
	
	int			breathingEffectCoordinate;	// RYAN: Tracks breathing effect
	int			breathingMagnitude;			// RYAN: Holds breathing magnitude
	int			walkingEffectCoordinate;	// RYAN: Tracks stepping effect
	int			stamina;					// RYAN: Tracks player stamina

	int			tileSize;				// RYAN: Tile size 
	int			tileHeight;				// RYAN: Tile height
	float		revisedPlayerEyeLevel;			// RYAN: Prev frame cam level
	float		revisedPlayerEyeLevelLowered;	// RYAN: Prev frame cam lowered

	int**		stage_tile_codes;		// RYAN: tile code array
	int**		stage_trap_codes;		// RYAN: trap code array
	iObject***	ceilingTiles;			// RYAN: pointers to ceiling objects
	iObject*	ceilingTile;			// RYAN: pointer to the current ceiling
	float**		ceilingTileCurLocArray;	// RYAN: 2D array of cur. ceiling positions
	float**		ceilingTileMaxLocArray;	// RYAN: 2D array of max ceiling positions
	float**		ceilingTileCollapseProgress; // RYAN: Current collapse progress
	int			timerStartedOn;			// RYAN: Tracks game play time.
	bool		timerStarted;			// RYAN: Ceilings begin collapsing if true.
	float		modifiedPlayerSpeed;	// RYAN: Current player speed.
	int			timeElapsed;
	bool		gameFinished;
	int			bestRecord;

	int breathingRadiusValue;	// RYAN: int value for the fast comparison
	int steppingRadiusValue;	// RYAN: int vlaue for the fast comparison
	int stepNumber;				// RYAN: number of steps so far. Max=30000
	int revertCollapseFor;				// RYAN: Active item remaining time
	int revertCollapseCastingWait;
	int stopCollapseFor;
	int stopCollapseCastingWait;
	int increaseSpeedFor;				// RYAN: Item casting wait time
	int increaseSpeedCastingWait;		
	int increaseDexterityFor;
	int increaseDexterityCastingWait;
	int numSpeedItems;					// RYAN: Number of items remaining
	int numDexterityItems;
	int numRevertCollapseItems;
	int numStopCollapseItems;


	// RYAN: Sound mapping can be changed time to time. 
	//       See the code file for details.
	iSound*		CeilingCollapse;
	iSound*		CeilingCollapseDistant;
	iSound*		Cure;
	iSound*		Deaf;
	iSound*		DeafCured;
	iSound*		DoorClose;
	iSound*		Environmental;
	iSound*		FootStepTypeA;
	iSound*		FootStepTypeB;
	iSound*		FootStepTypeC;
	iSound*		FootStepTypeD;
	iSound*		FootStepTypeE;
	iSound*		FootStepTypeF;
	iSound*		GhostTricks;
	iSound*		Haste;
	iSound*		Dexterity;
	iSound*		GameStart;
	iSound*		GameClear;
	iSound*		MachineTurnedOff;
	iSound*		MachineTurnedOn;
	iSound*		ScaryVoice;
	iSound*		ScaryVoiceFemale;
	iSound*		ScaryVoiceMale;
	iSound*		Scream;
	iSound*		StaminaGained;
	iSound*		TimeOut;
	iSound*		InhaleA;
	iSound*		InhaleB;
	iSound*		ExhaleA;
	iSound*		ExhaleB;
	iSound*		HealthLoss;
	iSound*		HealthLossAlt;
	iSound*		Death;
	// AKV - trap related
	iObject* traps[MAX_TRAPS]; // array of traps
	int playerLivesLost;	// the number of lives lost (restarts)

    int       lastUpdate;      // time that the model was last updated

    Design(iContext* c);
    Design(const Design& s);            // prevents copying
    Design& operator=(const Design& s); // prevents assignment
    virtual ~Design() {}


	/*
	 AKV - creates a Floor Spike from the initial position of the floor tile (bottom left close point) and the specifications for the trap
	 from the trap file entry (returns NULL if specifications is invalid)
	*/
	iObject* CreateTrapFloorSpike(Vector floorTilePos, const char* trapSpec, Colour c, iTexture* t);

	/*
	 AKV - creates an Atom from the initial position of the floor tile (bottom left close point) and the specifications for the Atom
	 from the trap file entry (returns NULL if specifications is invalid)
	*/
	iObject* CreateTrapAtom(Vector floorTilePos, const char* trapSpec, Colour cPrj, Colour cSpikes, iTexture* tBox, iTexture* tSpike);

	/*
	 AKV - creates a Projectile from the initial position of the floor tile (bottom left close point) and the specifications for the Projectile
	 from the trap file entry (returns NULL if specifications is invalid)
	*/
	iObject* CreateTrapProjectile(Vector floorTilePos, const char* trapSpec, Colour c, iTexture* t);

	ProjectileType getPrjTypeFromIndx(int indx);

	/*
	 Gets the entire string contents of the file specified.
	 Note: the caller of this method must remember to deallocate the memory used for the file contents when finished since this method
		   dynamically allocates memory but does not free it when execution of this method is completed
	*/
	char* GetTrapMapContents(wchar_t* file_name);

	void updateTraps(int now);	// AKV - updates all traps

  public:
	friend iDesign* CreateDesign(iContext* c);
	// initialization functions
    void   initialize(int now);
	void   reset(int now);
    void   restore(int now);
	// execution function
    void   update(int now);
	// termination functions
	void   Delete() const { delete this; }
	void LoadMap(wchar_t* file_name);	// RYAN: Initializes map array with file
	void LoadStandardSoundClips();		// RYAN: Initializes sound clips
	void PlaySteppingSound(int speed, int now);		// RYAN: Triggers step sounds
	void PlayBreathingSound(int intensity, int now);// RYAN: Triggers breath sounds
	void PlayHealthGainSound();
	void PlayHealthLossSound(bool greatIntensity);
	void PlayGameOverSound();
};

#endif
