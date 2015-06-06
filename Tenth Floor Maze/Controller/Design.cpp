/* Design Implementation - Design Component - Model Branch
*
* Design.cpp
* fwk4gps version 1.0
* gam666/dps901
* August 30 2010
* copyright (c) 2010 Chris Szalwinski 
* distributed under TPL - see ../Licenses.txt
*
* Modification done by Ryan Wang (Responsibility: stage objects) 
* from October 21 to November 13 2010
*
*/

#include "iContext.h"        // for the Context Interface
#include "iText.h"           // for the Text Interface
#include "iSound.h"          // for the Sound Interface
#include "iLight.h"          // for the Light Interface
#include "iObject.h"         // for the Object Interface
#include "iTexture.h"        // for the Texture Interface
#include "iCamera.h"         // for the Camera Interface
#include "iUtilities.h"      // for strcpy()
#include "iHUD.h"
#include "iHUDTexture.h"     //GMOK: for the HUDTexture Interface
#include "iEnvironment.h"    //GMOK: for the Environment Interface

#include "Design.h"          // for the Design class declaration
#include "MathDefinitions.h" // for MODEL_Z_AXIS
#include "ModelSettings.h"   // for FLOOR, MOUSE_BUTTON_SCALE, ROLL_SPEED

#include "D3d9types.h"		 //GMOK: for D3DCOLOR_XRGB(255,255,255)

#include "Object.h"	// AKV - need for ProjectileType
#include <math.h>	// AKV

//-------------------------------- Design -------------------------------------
//
// The Design Component implements the design within the model branch
//
// CreateDesign creates the Design Object
//
iDesign* CreateDesign(iContext* c) {

	return new Design(c);
}

// constructor initializes the object and texture pointers and the reference
// time
//
Design::Design(iContext* c) : context(c) {
	environment = NULL;

	/* temporary variables/objects for debugging purpose */
	camera_text					= NULL;
	line1						= NULL;
	line2						= NULL;
	line3						= NULL;
	healthLine					= NULL;	// AKV

	speedUPBar					= NULL;
	dexterityBar				= NULL;
	revertCollapseBar			= NULL;
	stopCollapseBar				= NULL;
	healthBar					= NULL;	// AKV
	staminaDisplay				= NULL;	// AKV

	speedUpText = NULL; // RYAN: display text for the items
	dexterityText = NULL;
	revertCollapseText = NULL;
	stopCollapseText = NULL;
	speedUpIcon = NULL;
	dexterityIcon = NULL;
	revertCollapseIcon = NULL;
	stopCollapseIcon = NULL;
	itemTextInitialized = false;
	staminaDisplay = NULL; // RYAN: stamina information
	distanceDisplay = NULL; // RYAN: distance information
	timeDisplay = NULL; // RYAN: direction information

	testSprite					= NULL;
	torch1						= NULL;
	torch2						= NULL;
	/* temporary variables/objects for debugging purpose */

	lastUpdate					= 0;	// Reference time
	main_character				= NULL; // RYAN: Main character object
	main_character_camera		= NULL; // RYAN: Main character camera

	// Configurations 
	//
	isStaminaGame				= true; // RYAN: Slows down the speed when fainting
	startCoordinateX			= 0;	// RYAN: Start coordinate X
	startCoordinateZ			= 0;	// RYAN: Start coordinate Z
	startTileIndexX				= 0;	// RYAN: Starting tile index X
	startTileIndexZ				= 0;	// RYAN: Starting tile index Z
	previousTileIndexX			= 0;	// RYAN: Player location tile index 
	previousTileIndexZ			= 0;	//       of the previous frame
	stageHeight					= CONSTANT_STAGE_HEIGHT;	// RYAN: Default ceiling level.
	// AKV - added constant to handle stage height
	numTilesX					= 20;	// RYAN: Default number of tiles X
	numTilesZ					= 20;	// RYAN: Default number of tiles Z
	tileSize					= CONSTANT_TILE_SIZE;	// RYAN: Default tile size.
	// AKV - added constant to handle tile size
	tileHeight					= 0;	// RYAN: Default tile display height
	modifiedPlayerSpeed			= 1.0f; // RYAN: Tracks current player speed to simulate
	//       smooth acceleration/deceleration
	timerStarted				= false;// RYAN: Ceilings begin collapsing if true.
	timerStartedOn				= -1;	// RYAN: Tracks game play time.
	gameFinished				= false;
	timeElapsed					 = 0;
	// Breathing effect coordinate to get the 
	// sine (sinf) value for the brething/stepping effects.
	//
	breathingEffectCoordinate	= 0;	// RYAN: sinf() parameter for breathing effect
	walkingEffectCoordinate		= 0;	// RYAN: sinf() parameter for stepping effect
	breathingRadiusValue		= 0;	// RYAN: int value for the fast comparison
	steppingRadiusValue			= 0;	// RYAN: int vlaue for the fast comparison
	stepNumber					= 0;	// RYAN: Tracks number of steps to play
	//       different sounds
	breathingMagnitude			= MIN_BREATHING_MAG * MULTIPLY_BY;
	stamina						= STAMINA_UPPER_LIMIT * MULTIPLY_BY;
	bestRecord					= 3600000;
	// Initializing dynamic arrays.
	//
	stage_tile_codes			= (int**) malloc(numTilesZ * sizeof(int));
	stage_trap_codes			= (int**) malloc(numTilesZ * sizeof(int));

	for (int i = 0; i < numTilesZ; i++) { 
		stage_tile_codes[i] = (int*) malloc(numTilesX * sizeof(int));
		stage_trap_codes[i] = (int*) malloc(numTilesX * sizeof(int));
	}
	// Default map array used when no map data file is provided
	int sample_array[20][20] =	DEFAULT_MAP; // Specified in the ModelSettings.h
	for (int j = 0; j < numTilesZ; j++) {
		for (int k = 0; k < numTilesX; k++) { 
			stage_tile_codes[j][k] = sample_array[j][k]; 
			stage_trap_codes[j][k] = 0;
		}
	}

	// Sound pointers.
	FootStepTypeA = FootStepTypeB = NULL; // RYAN: Sound clips for
	FootStepTypeC = FootStepTypeD = NULL; // RYAN: Normal steps.
	FootStepTypeE = FootStepTypeF = NULL; // RYAN: Stepping sound when fainting.
	DoorClose				= NULL;		// RYAN: When game starts
	Haste					= NULL;		// RYAN: When timer started / haste item acquired.
	Environmental			= NULL;		// RYAN: When player approaches exit.
	CeilingCollapseDistant	= NULL;		// RYAN: Ceiling collapsing started
	MachineTurnedOn			= NULL;		// RYAN: Ceiling collapsing 25%
	CeilingCollapse			= NULL;		// RYAN: Ceiling collapsing 50%
	MachineTurnedOff		= NULL;		// RYAN: Ceiling collapsing 100%

	ceilingTiles			= NULL;		// RYAN: Holds pointers to the ceiling objects
	ceilingTile				= NULL;		// RYAN: Previous target ceiling
	ceilingTileCurLocArray	= NULL;		// RYAN: Current ceiling tile altitude
	ceilingTileMaxLocArray	= NULL;		// RYAN: Maximum collapsing altitude
	//       Randomly generated in the initialize()
	ceilingTileCollapseProgress = NULL; // RYAN: Holds current progress of the ceiling collapse.

	revisedPlayerEyeLevel			= 5.0f;	// RYAN: Previous camera level 
	revisedPlayerEyeLevelLowered	= 0.0f;	// RYAN: Amount camera lowered prev. frame.

	revertCollapseFor				= 0; // RYAN: ceiling tile moves upward if > 0
	stopCollapseFor					= 0; // RYAN: ceiling tile stops collapsing if > 0
	increaseSpeedFor				= 0; // RYAN: improves walking speed if > 0
	increaseDexterityFor			= 0; // RYAN: improves speed when passing collapsed area
	revertCollapseCastingWait		= 0; // RYAN: time required for the next casting.
	stopCollapseCastingWait			= 0;
	increaseSpeedCastingWait		= 0;
	increaseDexterityCastingWait	= 0;
	numSpeedItems					= 3; // RYAN: items remaining.
	numDexterityItems				= 3; //       these are initial quantities.
	numRevertCollapseItems			= 2;
	numStopCollapseItems			= 2;
	// Currently not being used.
	//
	GhostTricks=NULL; ScaryVoice=NULL; 
	ScaryVoiceFemale=NULL; ScaryVoiceMale=NULL; Scream=NULL;
	Deaf=NULL; DeafCured=NULL; Cure=NULL;
	StaminaGained=NULL; TimeOut=NULL; 
	InhaleA = InhaleB = ExhaleA = ExhaleB = NULL; 
	GameStart=NULL;
	GameClear=NULL;
	Dexterity=NULL;
	HealthLoss = NULL;
	HealthLossAlt = NULL;
	Death = NULL;
	// AKV - initialize the traps
	for (int i = 0; i < MAX_TRAPS; i++)
		traps[i] = NULL;

	//GMOK: For billboards
	tIndex = 0; //GMOK: torch
	billLastUpdate = 0;
}

// initialize creates the objects and textures in the initial scene
// and initializes the reference time
//

void Design::initialize(int now) {

	environment = CreateEnvironment();
	Colour playerlight(1.0f, 1.0f, 1.0f);
	Colour playerdim(0.5f, 0.5f, 0.5f);
	Colour playerdimmer(0.25f, 0.25f, 0.25f);
	Colour white(1.0f, 1.0f, 1.0f);
	Colour yellow(0.7f, 0.7f, 0.7f);
	Colour black(0.0f, 0.0f, 0.0f);
	previousTileIndexX = startTileIndexX;
	previousTileIndexZ = startTileIndexZ;


	main_character = CreatePlayer(.0f, .0f, .0f, .0f, .0f, .0f, white);
	main_character_camera = CreateCamera(context);
	LoadMap(L"Stage2V2.txt");	// AKV - changed file name to use updated map file with trap related data
	LoadStandardSoundClips();


	context->set(GF_LT_BKGD, Vector(LIGHT_AMBIENT, LIGHT_AMBIENT, LIGHT_AMBIENT));
	// RYAN: Textures required to display map/tile components
	// - texture image for ceiling objects.
	iTexture* texture_floor		= CreateTexture(L"texture_floor.jpg");
	// - texture images for the floor tiles. 
	//   "floorZX.bmp" where 'Z' is z coordinate and 'X' is x coordinate.
	iTexture* texture_floor00	= CreateTexture(L"floor00.bmp");
	iTexture* texture_floor01	= CreateTexture(L"floor01.bmp");
	iTexture* texture_floor02	= CreateTexture(L"floor02.bmp");
	iTexture* texture_floor03	= CreateTexture(L"floor03.bmp");
	iTexture* texture_floor10	= CreateTexture(L"floor10.bmp");
	iTexture* texture_floor11	= CreateTexture(L"floor11.bmp");
	iTexture* texture_floor12	= CreateTexture(L"floor12.bmp");
	iTexture* texture_floor13	= CreateTexture(L"floor13.bmp");
	iTexture* texture_floor20	= CreateTexture(L"floor20.bmp");
	iTexture* texture_floor21	= CreateTexture(L"floor21.bmp");
	iTexture* texture_floor22	= CreateTexture(L"floor22.bmp");
	iTexture* texture_floor23	= CreateTexture(L"floor23.bmp");
	iTexture* texture_floor30	= CreateTexture(L"floor30.bmp");
	iTexture* texture_floor31	= CreateTexture(L"floor31.bmp");
	iTexture* texture_floor32	= CreateTexture(L"floor32.bmp");
	iTexture* texture_floor33	= CreateTexture(L"floor33.bmp");
	iTexture* texture_strip00	= CreateTexture(L"strip00.bmp");
	// - vertical cherry wood texture
	iTexture* texture_strip01	= CreateTexture(L"strip01.bmp");
	// - square cherry wood
	iTexture* texture_anchor00	= CreateTexture(L"anchor00.bmp");
	// - brick texture
	iTexture* texture_brick00	= CreateTexture(L"wall_brick.bmp");
	// - texture for the starting position.
	iTexture* texture_compass	= CreateTexture(L"compass.bmp");

	//iTexture *texture_torch     = CreateTexture(L"blackTorch.tga");//GMOK:Torch billboard texture

	//GMOK: Create the textures representing each frame of the billboard
	wchar_t str[25];
	for (int i = 0; i < 5 ; i ++)
	{
		wsprintf(str, L"bt-%d.tga", i);
		btTexture[i] = (CreateTexture(str));
	}

	// Initializing ceiling tile pointer array
	//
	ceilingTiles = NULL;
	ceilingTiles = (iObject***)calloc(numTilesZ, sizeof(iObject**));
	ceilingTileCurLocArray = (float**)calloc(numTilesZ, sizeof(float*));
	ceilingTileMaxLocArray = (float**)calloc(numTilesZ, sizeof(float*));
	ceilingTileCollapseProgress = (float**)calloc(numTilesZ, sizeof(float*));

	if (ceilingTile == NULL) {
		ceilingTile = CreateBox(0.0f, 0.0f, 0.0f, 
			float(tileSize), float(stageHeight), float(tileSize), white);
		ceilingTile->translate(0.0f, float(0 - stageHeight * 2), 0.0f);
		ceilingTile->attach(texture_floor);
	}
	srand ( int(time(NULL)) );
	for (int i = 0; i < numTilesZ; i++) {
		iObject** ceilingTiles_in_a_row = (iObject**)calloc(numTilesX, sizeof(iObject*));
		float* ceilingTileCurLocArray_row = (float*)calloc(numTilesX, sizeof(float));
		float* ceilingTileMaxLocArray_row = (float*)calloc(numTilesX, sizeof(float));
		float* ceilingTileCollapseProgress_row = (float*)calloc(numTilesX, sizeof(float));
		for (int j = 0; j < numTilesX; j++) {
			float dis_x = float(j * tileSize);
			float dis_z = float(i * tileSize);
			iObject* cloned_ceilingTile = Clone(ceilingTile);
			cloned_ceilingTile->translate(dis_x, float(stageHeight * 3), dis_z);
			ceilingTileCurLocArray_row[j] = cloned_ceilingTile->position().y;
			ceilingTileMaxLocArray_row[j] = float(5.0f + float(rand() % 100) / 20);
			ceilingTiles_in_a_row[j] = cloned_ceilingTile;
			ceilingTileCollapseProgress_row[j] = 0.0f;
		}
		ceilingTiles[i] = ceilingTiles_in_a_row;
		ceilingTileCurLocArray[i] = ceilingTileCurLocArray_row;
		ceilingTileMaxLocArray[i] = ceilingTileMaxLocArray_row;
		ceilingTileCollapseProgress[i] = ceilingTileCollapseProgress_row;
	}

	// RYAN: Creating map components: wall components and a floor tile
	iObject* floorTile = 
		CreateBox(0.0f, 0.0f, 0.0f, 
		float(tileSize), float(tileHeight), float(tileSize), Colour(1.0F, 1.0F, 1.0F, 1.0F));
	iObject* wall_anchor =		// RYAN: The anchor rod. Vertically long cherry wood.
		CreateBox(0.0f - float(tileSize) * 0.05f, 0.0f, 0.0f - float(tileSize) * 0.05f, 
		float(tileSize) * 0.05f, float(stageHeight), float(tileSize) * 0.05f, white);
	wall_anchor->attach(texture_strip01);	// RYAN: Attaches cherry wood texture.
	iObject* wall_x_bottom =	// RYAN: The one with 'DPS901/GAM666' text.
		CreateBox(float(tileSize) * 0.05f, 0.0f, 0.0f - float(tileSize) * 0.02f, 
		float(tileSize) * 0.95f, float(tileSize) * 0.1f, float(tileSize) * 0.025f, white);
	wall_x_bottom->attach(texture_strip00); // RYAN: Attaches 'DPS901' texture
	iObject* wall_x_surface =	// RYAN: The one with brick texture.
		CreateBox(float(tileSize) * 0.05f, 0.0f, 0.0f - float(tileSize) * 0.01f, 
		float(tileSize) * 0.95f, float(stageHeight), float(tileSize) * 0.01f,  white);

	// RYAN: Places the floor tile under the stage. Not visible to the player.
	floorTile->translate(float(startCoordinateX), 0.0f - float(stageHeight), float(startCoordinateZ));

	// Copies created walls and rotate 90 degrees.
	iObject* wall_y_bottom = Clone(wall_x_bottom); 
	wall_y_bottom->rotatey(3.14159265f / 2); 
	iObject* wall_y_surface = Clone(wall_x_surface);
	wall_y_surface->rotatey(3.14159265f / 2); 
	wall_y_bottom->translate(0.0f - float(tileSize) * 0.5f, 0, float(tileSize) * 0.5f);
	wall_y_surface->translate(0.0f - float(tileSize) * 0.5f, 0, float(tileSize) * 0.5f);
	wall_anchor->translate(float(startCoordinateX), float(0 - stageHeight), float(startCoordinateZ));
	wall_x_bottom->translate(float(startCoordinateX), float(0 - stageHeight), float(startCoordinateZ));
	wall_x_surface->translate(float(startCoordinateX), float(0 - stageHeight), float(startCoordinateZ));
	wall_y_bottom->translate(float(startCoordinateX), float(0 - stageHeight), float(startCoordinateZ));
	wall_y_surface->translate(float(startCoordinateX), float(0 - stageHeight), float(startCoordinateZ));


	// AKV - textures for traps
	iTexture* trpMetal4 = CreateTexture(L"metal4.png");	
	iTexture* trpMetal5 = CreateTexture(L"metal5.png");
	iTexture* trpCgMetal05 = CreateTexture(L"cgMetal05.jpg");
	iTexture* trpCgMetal09 = CreateTexture(L"cgMetal09.jpg");
	iTexture* trpCgMetal10 = CreateTexture(L"cgMetal10.jpg");
	iTexture* trpUdGrass = CreateTexture(L"udGrass.jpg");

	// AKV - colours of each type of trap components
	const Colour spikeColour = Colour(0.75f, 0.75f, 0.75f);
	const Colour prjtileColour = Colour(192/255.f, 192/255.f, 192/255.f);
	const Colour atomPrjColour = Colour(128/255.f, 255/255.f, 128/255.f);
	const Colour atomSpikesColour = Colour(255/255.f, 255/255.f, 0/255.f);

	// AKV - trap file row delimiter
	const char row_delimiter[] = ";";
	char* trapMap = GetTrapMapContents(TRAPS_MAP_FILE);	// get the entire contents of the trap file
	char* token = strtok(trapMap, row_delimiter);	// get next trap specifications

	// AKV - the current index of the traps array
	int trpIndx = 0;

	// AKV - testing - start
	Vector testPos;
	bool showTestPos = false;
	bool isTesting = false;

	if (showTestPos)
		main_character->attach(CreateText(0.0f, 0.75f, 4.f, 0.84f), playerBoundryDetails);	
	// AKV - testing - end

	// RYAN: This attaches different floor pattern textures
	// 
	for (int i = 0; i < numTilesZ; i++) {
		for (int j = 0; j < numTilesX; j++) {
			iObject* clonedTile = Clone(floorTile); 
			clonedTile->translate(float(tileSize * i), stageHeight, (float(tileSize * j)));
			int tile_code_y = j % 4;
			int tile_code_x = i % 4;


			// AKV - start trap creation

			// get the lower, close left position of the tile
			Vector floorTilePos = clonedTile->position();
			floorTilePos.x -= CONSTANT_TILE_SIZE/2.0f;
			floorTilePos.y = 0;
			floorTilePos.z -= CONSTANT_TILE_SIZE/2.0f;


			// start - testing
			// used for testing
			float x, y, z;
			char testMapFileEntry[20];
			int testI, testJ;

			// used for testing (if you know the position and want to determine the row and column entry in the map file)
			x = 200.f;
			y = 0.f;
			z = 160.f;

			// used for testing (if you know a row and column from the map file that you want to determine the position for)
			testI = -1;
			testJ = -1;
			static bool isChk = !(testI >= 0 && testJ >= 0);

			if ((i == testI - 1 && j == testJ - 1) || (floorTilePos.x >= x && floorTilePos.z == z && isChk))
			{
				sprintf(testMapFileEntry, "r=%d,c=%d", i + 1, j + 1);
				testPos = clonedTile->position();
				x = x;
				isChk = false;
				isTesting = false;
			}
			// end - testing


			int trapCode = stage_trap_codes[numTilesZ - i - 1][j];

			// get each trap specifications only if this tile has a trap associated to it
			if ( (trapCode == TRAPS_MAP_FILE_IS_TRAP)) {

				// parse the trap's specifications
				bool isTrap = false;
				int trapType = 0;
				int count = 1;
				char order;
				iObject* trp;

				// skip any comment lines
				while ((token != NULL) && sscanf_s(token, "%d%*s", &trapType) != 1)
					token = strtok(NULL, row_delimiter);

				/*
				determine the trap type and the order, then create the trap if it is a new trap for the tile or a a new trap
				creating for the same tile
				*/
				while ((token != NULL) && (sscanf_s(token, "%d|%c|%*s", &trapType, &order) == 2) &&
					(count == 1 || order == 'r'))
				{

					trp = NULL;	// set to NULL by default

					iTexture* prjtileTxt = trpMetal5;

					// create the trap based on the trap type
					switch (trapType)
					{						
					case TRAPS_MAP_FILE_FLOOR_SPIKE:	// floor spike
						trp = CreateTrapFloorSpike(floorTilePos, token, spikeColour, trpCgMetal09);
						isTrap = true;
						break;

					case TRAPS_MAP_FILE_PROJECTILE:	// projectile
						if (sscanf_s(token, "%*d|%*c|%d%*c", &trapType) == 1)
						{

							// get the texture associated to this projectile type
							switch (getPrjTypeFromIndx(trapType))
							{
							case DOUBLE_EDGE_SPEAR:
								prjtileTxt = trpMetal4;
								break;

							case CROSS:
								prjtileTxt = trpMetal5;
								break;

							case STAR:
								prjtileTxt = trpCgMetal10;
								break;

							case DIAGONAL_LTR:
							case DIAGONAL_RTL:
								prjtileTxt = trpMetal4;
								break;

							case PIECE_WISE:
								prjtileTxt = trpCgMetal05;
								break;
							}

							trp = CreateTrapProjectile(floorTilePos, token, prjtileColour, prjtileTxt);
							isTrap = true;
						}
						break;

					case TRAPS_MAP_FILE_ATOM:	// atom
						trp = CreateTrapAtom(floorTilePos, token, atomPrjColour, atomSpikesColour, trpUdGrass, trpCgMetal05);
						isTrap = true;
						break;
					}

					if (isTrap)
					{
						if (trp != NULL)
						{
							if (trpIndx < MAX_TRAPS)
							{
								traps[trpIndx++] = trp;

								// get next trap specifications only if the current entry was for a trap
								token = strtok(NULL, row_delimiter);

								// skip any comment lines
								while ((token != NULL) && sscanf_s(token, "%d%*s", &trapType) != 1)
									token = strtok(NULL, row_delimiter);
							}
							else
							{
								error(L"Maximum number of traps has been reached. Try increasing MAX_TRAPS value.");

								// ensure no more tokens are left
								while (token != NULL)
									token = strtok(NULL, row_delimiter);
							}
						}
						else
							logError(L"LoadTrapMap::1 - Unable to create the trap for the specs provided");						
					}

					count++;
				}
			}

			// AKV - end trap creation

			switch(tile_code_y) {
			case 0:
				if (tile_code_x == 0) clonedTile->attach(texture_floor00);
				else if (tile_code_x == 1) clonedTile->attach(texture_floor10);
				else if (tile_code_x == 2) clonedTile->attach(texture_floor20);
				else if (tile_code_x == 3) clonedTile->attach(texture_floor30);
				break;
			case 1: 
				if (tile_code_x == 0) clonedTile->attach(texture_floor01);
				else if (tile_code_x == 1) clonedTile->attach(texture_floor11);
				else if (tile_code_x == 2) clonedTile->attach(texture_floor21);
				else if (tile_code_x == 3) clonedTile->attach(texture_floor31);
				break;
			case 2: 
				if (tile_code_x == 0) clonedTile->attach(texture_floor02);
				else if (tile_code_x == 1) clonedTile->attach(texture_floor12);
				else if (tile_code_x == 2) clonedTile->attach(texture_floor22);
				else if (tile_code_x == 3) clonedTile->attach(texture_floor32);
				break;
			case 3: 
				if (tile_code_x == 0) clonedTile->attach(texture_floor03);
				else if (tile_code_x == 1) clonedTile->attach(texture_floor13);
				else if (tile_code_x == 2) clonedTile->attach(texture_floor23);
				else if (tile_code_x == 3) clonedTile->attach(texture_floor33);
				break;
			}
		}
	}



	for (int i = 0; i < numTilesZ; i++) {
		for (int j = 0; j < numTilesX; j++) {
			int cell_type = stage_tile_codes[i][j];
			// RYAN: If the current tile is the goal, attach wind howling sound locally.
			// RYAN: Goals have tile code greater than 7
			if (stage_trap_codes[i][j] >= 9 && Environmental != NULL) {
				iSound* exit_wind_howling_sound = Environmental->clone();
				exit_wind_howling_sound->translate(float(tileSize * j), 0, float(tileSize * i));
				exit_wind_howling_sound->forcePlay();
				goal_index_x = j;
				goal_index_z = i;
			}
			// RYAN: Creates walls
			if (cell_type == 1) {
				iObject* x_cloned_anchor = Clone(wall_anchor); 
				x_cloned_anchor->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* x_cloned_x_bottom = Clone(wall_x_bottom); 
				x_cloned_x_bottom->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* x_cloned_x_surface = Clone(wall_x_surface); 
				x_cloned_x_surface->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				x_cloned_x_surface->attach(texture_brick00);
			} else if (cell_type == 2) {
				iObject* y_cloned_anchor = Clone(wall_anchor); 
				y_cloned_anchor->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* y_cloned_y_bottom = Clone(wall_y_bottom); 
				y_cloned_y_bottom->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* y_cloned_y_surface = Clone(wall_y_surface); 
				y_cloned_y_surface->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				y_cloned_y_surface->attach(texture_brick00);
			} else if (cell_type == 3) {
				iObject* a_cloned_anchor = Clone(wall_anchor); 
				a_cloned_anchor->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* a_cloned_x_bottom = Clone(wall_x_bottom); 
				a_cloned_x_bottom->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* a_cloned_x_surface = Clone(wall_x_surface); 
				a_cloned_x_surface->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* a_cloned_y_bottom = Clone(wall_y_bottom); 
				a_cloned_y_bottom->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				iObject* a_cloned_y_surface = Clone(wall_y_surface); 
				a_cloned_y_surface->translate(float(tileSize * j), stageHeight, float(tileSize * i));
				a_cloned_x_surface->attach(texture_brick00);
				a_cloned_y_surface->attach(texture_brick00);
			} else {
				bool display_anchor = false;
				if ((i > 0 && (int(stage_tile_codes[i-1][j]) % 4 == 2 || int(stage_tile_codes[i-1][j]) % 4 == 3)) || 
					(j > 0 && (int(stage_tile_codes[i][j-1]) % 4 == 1 || int(stage_tile_codes[i][j-1]) % 4 == 3))) { 
						iObject* n_cloned_anchor = Clone(wall_anchor); 
						n_cloned_anchor->translate(float(tileSize * j), float(stageHeight), float(tileSize * i)); 
				}
			}
		}
	}



	// initializing items such as haste/dexterity/revert/stop collapsing.
	for (int i = 0; i < numTilesZ; i++) {
		for (int j = 0; j < numTilesX; j++) {
			switch(stage_trap_codes[i][j]) {
			case 1:
				// starting point. starts/resets timer. triggers ceiling collapse
				startTileIndexX = j;
				startTileIndexZ = i;
				iObject* compass = CreateBox(0.0f, 0.0f, 0.0f, 
					float(tileSize) * 0.7f, float(tileSize) * 0.7f, float(tileSize) * 0.7f, white);
				compass->attach(texture_compass);
				compass->translate(float(tileSize) * 0.15f + float(startTileIndexX * tileSize), 
					0.0f - float(tileSize) * 0.695f, float(tileSize) * 0.15f + float(startTileIndexZ * tileSize)); 
				break;
			}
		}
	}

	// AKV - set player's health to starting values
	((Player*)main_character)->setHealth(PLAYER_START_HEALTH);
	((Player*)main_character)->setTotalHealth(PLAYER_MAX_HEALTH);
	playerLivesLost = 0;	// lives lost is 0 indicating the start of the game

	main_character_camera->translate(.0f, .0f, -1.5f);
	//main_character_camera->translate(0.f, PLAYER_DIM_SIZE_Y / 2.5f, 0.f);	// AKV - added this to allow the camera to be at a higher level
	iLight* main_character_light = CreatePointLight(playerlight, playerlight, playerdimmer, 200.0f, true, 1.0f, 0.2f, 0.0f);
	main_character->attach(main_character_camera);
	main_character->attach(main_character_light);
	main_character->translate(startCoordinateX + float(tileSize) / 2, 5, startCoordinateZ + float(tileSize) / 2);


	// start - testing - continued 
	// moves to the specified position for quick testing of traps
	if (isTesting)
	{
		Vector p = main_character->position();
		main_character->translate(-p.x, 0, -p.z);	// move back to the origin
		main_character->translate(testPos.x, 0, testPos.z);
	}
	// end - testing - continued


	// RYAN: initialize hud components
	float icon_x = 0.54f;
	float icon_xx = 0.58f;
	speedUpText		= CreateText(0.6f, 0.03f, 1.0f, 0.25f, TXT_DEFAULT, L"Speed Up Text");
	dexterityText	= CreateText(0.6f, 0.23f, 1.0f, 0.45f, TXT_DEFAULT, L"Dexterity Text");
	stopCollapseText	= CreateText(0.6f, 0.43f, 1.0f, 0.65f, TXT_DEFAULT, L"Postpone Text");
	revertCollapseText	= CreateText(0.6f, 0.63f, 1.0f, 0.85f, TXT_DEFAULT, L"Revert Text");

	staminaDisplay = CreateText(0.01f, 0.35f, 0.6f, 0.57f, TXT_DEFAULT, L"Stamina Display");

	distanceDisplay = CreateText(0.01f, 0.63f, 0.6f, 0.85f, TXT_DEFAULT, L"Distance Display");
	timeDisplay = CreateText(0.01f, 0.73f, 0.6f, 0.95f, TXT_DEFAULT, L"Time Display");

	staminaBar = CreateHUDTexture(0.01f,0.47f,0.45f,0.54f,'\xFF',HUDT_PROGRESS);
	staminaBar->set(CreateTexture(HUD_PROGRESS_GREEN));
	staminaBar->set(100.0f);
	staminaBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x30');

	// AKV - added health bar and display
	healthBar = CreateHUDTexture(0.01f,0.23f,0.45f,0.3f,'\xFF',HUDT_PROGRESS);
	healthBar->set(CreateTexture(HUD_PROGRESS_GREEN));
	healthBar->set(100.0f);
	healthBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x30');
	healthDisplay = CreateText(0.01f, 0.13f, 0.6f, 0.35f, TXT_DEFAULT, L"Health Display");

	// RYAN: item status icons and texts
	// SCREEN SIZE: 800 X 600 
	// HUD SIZE:	800 X 120 (100%, 20%)
	// IF ICON SIZE ? 40 X 40 0.05F/0.3F
	speedUpIcon			= CreateHUDTexture(icon_x, 0.03f, icon_xx, 0.18f, '\xFF', 1);
	speedUpIcon->set(CreateTexture(L"item_spd_active.bmp"));
	speedUpIcon->setAlpha('\x80');
	speedUpIcon->set(1.0f);
	speedUpIcon->enableBackground(true, CreateTexture(L"item_spd_inactive.bmp"), '\x80');
	dexterityIcon		= CreateHUDTexture(icon_x, 0.23f, icon_xx, 0.38f, '\xFF', 1);
	dexterityIcon->set(CreateTexture(L"item_dex_active.bmp"));
	dexterityIcon->setAlpha('\x80');
	dexterityIcon->set(1.0f);
	dexterityIcon->enableBackground(true, CreateTexture(L"item_dex_inactive.bmp"), '\x80');
	revertCollapseIcon		= CreateHUDTexture(icon_x, 0.43f, icon_xx, 0.58f, '\xFF', 1);
	revertCollapseIcon->set(CreateTexture(L"item_revert_active.bmp"));
	revertCollapseIcon->setAlpha('\x80');
	revertCollapseIcon->set(1.0f);
	revertCollapseIcon->enableBackground(true, CreateTexture(L"item_revert_inactive.bmp"), '\x80');
	stopCollapseIcon		= CreateHUDTexture(icon_x, 0.63f, icon_xx, 0.78f, '\xFF', 1);
	stopCollapseIcon->set(CreateTexture(L"item_stop_active.bmp"));
	stopCollapseIcon->setAlpha('\x80');
	stopCollapseIcon->set(1.0f);
	stopCollapseIcon->enableBackground(true, CreateTexture(L"item_stop_inactive.bmp"), '\x80');

	//camera_text = CreateText(0, 0.3f, 1.0f, 0.4f, TXT_DEFAULT, L" Camera text ");
	//line1 = CreateText(.0f, 0.4f, 1.0f, 0.5f, TXT_DEFAULT, L" Camera text ");
	//line2 = CreateText(.0f, 0.5f, 1.0f, 0.6f, TXT_DEFAULT, L" Camera text ");
	//line3 = CreateText(.0f, 0.6f, 1.0f, 0.7f, TXT_DEFAULT, L" Camera text ");

	/*speedUPBar = CreateHUDTexture(.6f,0.34f,0.95f,0.37f,'\xFF',HUDT_PROGRESS);
	speedUPBar->set(CreateTexture(HUD_PROGRESS_GREEN));
	speedUPBar->set(10);
	speedUPBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\xFF');

	dexterityBar = CreateHUDTexture(.6f,0.44f,0.95f,0.47f,'\xFF',HUDT_PROGRESS);
	dexterityBar->set(CreateTexture(HUD_PROGRESS_BLUE));
	dexterityBar->set(10);
	dexterityBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x80');

	revertCollapseBar = CreateHUDTexture(.6f,0.54f,0.95f,0.57f,'\xFF',HUDT_PROGRESS);
	revertCollapseBar->set(CreateTexture(HUD_PROGRESS_PURPLE));
	revertCollapseBar->set(10);
	revertCollapseBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x60');

	stopCollapseBar = CreateHUDTexture(.6f,0.64f,0.95f,0.67f,'\xFF',HUDT_PROGRESS);
	stopCollapseBar->set(CreateTexture(HUD_PROGRESS_RED));
	stopCollapseBar->set(10);
	stopCollapseBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x40');
	stopCollapseBar->enableReport(true);*/



	speedUPBar = CreateHUDTexture(.6f,0.13f,0.95f,0.17f,'\xFF',HUDT_PROGRESS);
	speedUPBar->set(CreateTexture(HUD_PROGRESS_GREEN));
	speedUPBar->set(10);
	speedUPBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x30');

	dexterityBar = CreateHUDTexture(.6f,0.33f,0.95f,0.37f,'\xFF',HUDT_PROGRESS);
	dexterityBar->set(CreateTexture(HUD_PROGRESS_BLUE));
	dexterityBar->set(10);
	dexterityBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x30');

	revertCollapseBar = CreateHUDTexture(.6f,0.53f,0.95f,0.57f,'\xFF',HUDT_PROGRESS);
	revertCollapseBar->set(CreateTexture(HUD_PROGRESS_PURPLE));
	revertCollapseBar->set(10);
	revertCollapseBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x30');

	stopCollapseBar = CreateHUDTexture(.6f,0.73f,0.95f,0.77f,'\xFF',HUDT_PROGRESS);
	stopCollapseBar->set(CreateTexture(HUD_PROGRESS_RED));
	stopCollapseBar->set(10);
	stopCollapseBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x30');
	//	stopCollapseBar->enableReport(true);

	//testSprite = CreateHUDTexture(.5f,0.7f,0.95f,0.95f,'\xFF',HUDT_SPRITE);
	//testSprite->set(CreateTexture(HUD_SPRITE_TEST));
	//testSprite->setSprite(0, 64, 0, 64, 64, 256, 64, 128, now);

	//testSprite = CreateHUDTexture(.05f,0.7f,0.95f,0.95f,'\xFF',HUDT_SPRITE);
	//testSprite->set(CreateTexture(HUD_SPRITE_ARROW1));
	//testSprite->setSprite(0, 110, 0, 130, 110, 1540, 130, 130, now);

	//testSprite = CreateHUDTexture(.55f,0.75f,0.95f,0.95f,'\xFF',HUDT_SPRITE);
	//testSprite->set(CreateTexture(HUD_SPRITE_BLACKTORCH));
	//testSprite->setSprite(0, 58, 0, 128, 58, 348, 128, 128, now);

	// AKV MARK TODO
	// AKV - added health progress bar to HUD
	//healthBar = CreateHUDTexture(.6f,0.24f,0.95f,0.27f,'\xFF', HUDT_PROGRESS);
	//healthBar->set(CreateTexture(HUD_PROGRESS_GREEN));
	//healthBar->set(PLAYER_MAX_HEALTH);	// sets the max value of progress bar to max health of player
	//healthBar->enableBackground(true, CreateTexture(HUD_PROGRESS_WHITE), '\x60');

	// RYAN: after initializing objects:
	if (DoorClose != NULL) { DoorClose->forcePlay(); }

	//GMOK:Torch billboard
	torch1 = CreateBillboard(0.0f, 0.0f, 0.0f, 1.0f,  2.0f, Colour(1.0f, 1.0f, 1.0f, 0.1f));
	torch1->attach(btTexture[0]);
	torch2 = Clone(torch1);
	torch1->translate((float(tileSize) * 0.15f + float(startTileIndexX * tileSize)-0.4), 
		(0.0f - float(tileSize) * 0.695f)+float(tileSize), 
		(float(tileSize) * 0.15f + float(startTileIndexZ * tileSize))+1);

	torch2->translate((float(tileSize) * 0.15f + float(startTileIndexX * tileSize)+7.4), 
		(0.0f - float(tileSize) * 0.695f)+float(tileSize), 
		(float(tileSize) * 0.15f + float(startTileIndexZ * tileSize))+1);
}

// reset changes the context if any change has been requested
// and reinitializes the reference time
//
void Design::reset(int now) {
	lastUpdate = now; // reset reference time
}

// restore re-initializes the reference time
//
void Design::restore(int now) {
	lastUpdate = now;  // reset reference time
}

// update updates the position and orientation of each object for time "now"
// according to the keys pressed - the coordinate system for user actions is
// the left handed system with the x axis to the right, the y axis to the top 
// and the z axis into the screen
//
void Design::update(int now) {

	int delta = now - lastUpdate;
	float float_delta = float(delta);
	if (main_character) {
		// calculate time remaining for the active items.
		if (increaseSpeedFor > 0) { increaseSpeedFor -= delta; increaseSpeedFor < 0 ? increaseSpeedFor = 0 : increaseSpeedFor; }
		if (increaseDexterityFor > 0) {increaseDexterityFor -= delta; increaseDexterityFor < 0 ? increaseDexterityFor = 0 : increaseDexterityFor; }
		if (stopCollapseFor > 0) {
			stopCollapseFor -= delta; 
			if (stopCollapseFor <= 0) { 
				if (CeilingCollapseDistant != NULL && timerStarted) CeilingCollapseDistant->forcePlay(); 
				stopCollapseFor = 0; 
			} 
		}
		if (revertCollapseFor > 0) {
			revertCollapseFor -= delta; 
			if (revertCollapseFor <= 0) { 
				if (CeilingCollapse != NULL && timerStarted) CeilingCollapse->forcePlay(); 
				revertCollapseFor = 0; 
			}
		}
		// process item re-casting wait time
		if (increaseSpeedCastingWait > 0) { increaseSpeedCastingWait -= delta; increaseSpeedCastingWait < 0 ? increaseSpeedCastingWait = 0 : increaseSpeedCastingWait; }
		if (increaseDexterityCastingWait > 0) {increaseDexterityCastingWait -= delta; increaseDexterityCastingWait < 0 ? increaseDexterityCastingWait = 0 : increaseDexterityCastingWait; }
		if (stopCollapseCastingWait > 0) {stopCollapseCastingWait -= delta; stopCollapseCastingWait < 0 ? stopCollapseCastingWait = 0 : stopCollapseCastingWait;}
		if (revertCollapseCastingWait > 0) {revertCollapseCastingWait -= delta; revertCollapseCastingWait < 0 ? revertCollapseCastingWait = 0 : revertCollapseCastingWait;}


		bool speedUpPressed = false;
		bool dexterityPressed = false;
		bool stopCollapsePressed = false;
		bool revertCollapsePressed = false;

		if (context->pressed(TENTH_FLOOR_TEST_HASTE) && increaseSpeedCastingWait == 0 && timerStarted && numSpeedItems > 0) {
			increaseSpeedFor += ITEM_HASTE_DURATION;
			increaseSpeedCastingWait = ITEM_CASTING_WAIT_TIME;
			numSpeedItems--;
			speedUpPressed = true;
			if (Haste != NULL) Haste->forcePlay();
		}
		if (context->pressed(TENTH_FLOOR_TEST_DEXTERITY) && increaseDexterityCastingWait == 0 && timerStarted && numDexterityItems > 0) {
			increaseDexterityFor += ITEM_HASTE_DURATION;
			increaseDexterityCastingWait = ITEM_CASTING_WAIT_TIME;
			numDexterityItems--;
			dexterityPressed = true;
			if (StaminaGained != NULL) StaminaGained->forcePlay();
		}
		if (context->pressed(TENTH_FLOOR_TEST_REVERT_COLLAPSING) && revertCollapseCastingWait == 0 && timerStarted && numRevertCollapseItems > 0) {
			revertCollapseFor += ITEM_REVERT_COLLAPSING_DURATION;
			revertCollapseCastingWait = ITEM_CASTING_WAIT_TIME;
			numRevertCollapseItems--;
			revertCollapsePressed = true;
			if (Cure != NULL) Cure->forcePlay();
		}
		if (context->pressed(TENTH_FLOOR_TEST_STOP_COLLAPSING) && stopCollapseCastingWait == 0 && timerStarted && numStopCollapseItems > 0) {
			stopCollapseFor += ITEM_STOP_COLLAPSING_DURATION;
			stopCollapseCastingWait = ITEM_CASTING_WAIT_TIME;
			numStopCollapseItems--;
			stopCollapsePressed = true;
			if (Cure != NULL) Cure->forcePlay();
		}

		//RYAN: update speed items information text if necessary. 
		if (speedUpPressed || itemTextInitialized == false) {
			wchar_t strSpeed[100];
			if (numSpeedItems > 0) { wsprintf(strSpeed,  L"SPEED-UP ITEM X %d (PRESS 1)", numSpeedItems);} 
			else {wsprintf(strSpeed,  L"SPEED-UP ITEM X %d", numSpeedItems);}
			if (speedUpText) speedUpText->set(strSpeed);
		}
		//RYAN: update num dexterity items remaining if necessary.
		if (dexterityPressed || itemTextInitialized == false) {
			wchar_t strDexterity[100];
			if (numDexterityItems > 0) { wsprintf(strDexterity, L"DEXTERITY ITEM X %d (PRESS 2)", numDexterityItems); }
			else {wsprintf(strDexterity, L"DEXTERITY ITEM X %d", numDexterityItems);}
			if (dexterityText) dexterityText->set(strDexterity);
		}
		//RYAN: update number of revert items remaining if necessary.
		if (revertCollapsePressed || itemTextInitialized == false) {
			wchar_t strPostpone[100];
			if (numRevertCollapseItems > 0) {wsprintf(strPostpone, L"REVERT ITEM X %d (PRESS 3)", numRevertCollapseItems); }
			else {wsprintf(strPostpone, L"REVERT COLLAPSE X %d", numRevertCollapseItems);}
			if (stopCollapseText) stopCollapseText->set(strPostpone);
		}
		// RYAN: update number of postpone items remaining if necessary.
		if (stopCollapsePressed || itemTextInitialized == false) {
			wchar_t strRevert[100];
			if (numStopCollapseItems > 0) {wsprintf(strRevert, L"POSTPONE ITEM X %d (PRESS 4)", numStopCollapseItems);}
			else {wsprintf(strRevert, L"POSTPONE COLLAPSE X %d", numStopCollapseItems);}
			if (revertCollapseText) revertCollapseText->set(strRevert);
		}
		itemTextInitialized = true;


		float	reduce_speed_by = 1.0;		// RYAN: reduces character displacement by. 
		int		current_tile_index_x = 0;	// RYAN: x-index of the current tile
		int		current_tile_index_z = 0;	// RYAN: z-index of the current tile

		float	lower_character_by = 0.0f;
		float	safe_display_margin = 2.5f;
		float	current_player_eye_level = 5.0f;
		float	prev_ceiling = float(stageHeight);
		float	maximum_possible_lowest_ceiling_level = 10.0f;

		// RYAN: Collision detection against collapsing ceiling tiles.
		if (ceilingTileCurLocArray != NULL && 
			ceilingTileMaxLocArray != NULL && 
			previousTileIndexZ < numTilesZ && 
			previousTileIndexX < numTilesX && 
			previousTileIndexZ >= 0 && 
			previousTileIndexX >= 0) {
				prev_ceiling = (float)ceilingTileCurLocArray[previousTileIndexZ][previousTileIndexX] - float(stageHeight) / 2 ;
				maximum_possible_lowest_ceiling_level = ceilingTileMaxLocArray[previousTileIndexZ][previousTileIndexX];
				// RYAN: If ceiling level is below the player's eye level, 
				//		 lowers the camera below the ceiling object.
				if (prev_ceiling < current_player_eye_level  + safe_display_margin) {
					lower_character_by = 
						current_player_eye_level - 
						(maximum_possible_lowest_ceiling_level - safe_display_margin);
					// RYAN: This value will be applied below.
				}
		}

		float should_lower_by_at_least = main_character->position().y -  prev_ceiling + 0.5f;
		if (should_lower_by_at_least < 0) { should_lower_by_at_least = 0; }
		if (lower_character_by < 0) { lower_character_by = 0; }


		//increaseSpeedFor = 1000; // haste testing
		//increaseDexterityFor = 1000; // dex testing

		int character_speed = 2;
		int breathing_intensity = 0;
		int rotation_x = 0, rotation_y = 0, rotation_z = 0, displacement = 0, cam_rotation_x = 0;
		float disp_x = 0.0f, disp_y = 0.0f, disp_z = 0.0f;
		int mouse_horizontal_displacement = context->get(GF_MS_POSX);
		int mouse_vertical_displacement = context->get(GF_MS_POSY);
		int mouse_wheel_displacement = context->get(GF_MS_ORIZ);
		if (mouse_horizontal_displacement) rotation_y -= (int)(mouse_horizontal_displacement * MOUSE_PANNING_SENSITIVITY);
		if (mouse_vertical_displacement) cam_rotation_x += (int)(mouse_vertical_displacement * MOUSE_PANNING_SENSITIVITY);
		if (context->pressed(TENTH_FLOOR_PLAYER_ADVANCE)) displacement += int(float_delta * CAMERA_ADVANCE_COEFFICIENT); 
		if (context->pressed(TENTH_FLOOR_PLAYER_RETREAT)) displacement -= int(float_delta * CAMERA_RETREAT_COEFFICIENT); 
		if (context->pressed(TENTH_FLOOR_PLAYER_TURN_LEFT)) rotation_y += int(float_delta * KEYBOARD_PANNING_SENSITIVITY); 
		if (context->pressed(TENTH_FLOOR_PLAYER_TURN_RIGHT)) rotation_y -= int(float_delta * KEYBOARD_PANNING_SENSITIVITY); 
		if (rotation_x) main_character->rotatex(rotation_x * ROT_SPEED);
		if (rotation_y) main_character->rotatey(rotation_y * ROT_SPEED);
		if (rotation_z) main_character->rotatez(rotation_z * ROT_SPEED);
		float cam_rot = main_character_camera->orientation('z').y; /* CAM DOWNWARD LIMIT: 75' / UPWARD LIMIT: 88' */
		if (cam_rotation_x && !((cam_rot < -0.83f && cam_rotation_x > 0) || (cam_rot > 0.95f && cam_rotation_x < 0) )) main_character_camera->rotatex(cam_rotation_x * ROT_SPEED); 
		if (displacement) {
			if (increaseSpeedFor > 0) reduce_speed_by /= 1.5f;
			if (isStaminaGame && (stamina - (MULTIPLY_BY * STAMINA_LOWER_LIMIT)) == 0) {
				reduce_speed_by *= 1.5f;
				character_speed = 1; 
			}
			if (lower_character_by > 0.0f && increaseDexterityFor == 0) { 
				float reduce_passing_speed_by = 1.0f + lower_character_by;
				reduce_passing_speed_by > 2.0f ? reduce_passing_speed_by = 2.0f : reduce_passing_speed_by;
				reduce_speed_by *= reduce_passing_speed_by;
			}
			int int_modifiedPlayerSpeed = int(modifiedPlayerSpeed * 100);
			int int_reduce_speed_by = int(reduce_speed_by * 100);
			if (int_modifiedPlayerSpeed < int_reduce_speed_by) { modifiedPlayerSpeed += CHARACTER_ACCELERATION * delta; }
			else if (int_modifiedPlayerSpeed > int_reduce_speed_by) { modifiedPlayerSpeed -= CHARACTER_ACCELERATION  * delta; }
			displacement = int(float(displacement) / modifiedPlayerSpeed);


			walkingEffectCoordinate += displacement;
			if (walkingEffectCoordinate > 628) { walkingEffectCoordinate %= 628; }
			Vector displacement_vector = (displacement * FORWARD_SPEED) * (Vector) main_character->orientation('z');
			disp_x += (float)displacement_vector.x;
			disp_y += (float)displacement_vector.y;
			disp_z += (float)displacement_vector.z;
			if (increaseSpeedFor == 0)  stamina	-= delta * 30; /*CONSUMES STAMINA*/
		} else { stamina += delta * 90; /*GAINS STAMINA*/ } 



		bool increase_magnitude = false;
		if (stamina < STAMINA_LOWER_LIMIT * MULTIPLY_BY) { stamina = STAMINA_LOWER_LIMIT * MULTIPLY_BY; increase_magnitude = true;} 
		else if (stamina > STAMINA_UPPER_LIMIT * MULTIPLY_BY) { stamina = STAMINA_UPPER_LIMIT * MULTIPLY_BY; } 
		if (increase_magnitude) {breathingMagnitude += delta * 200; } else { breathingMagnitude -= delta * 1000; }
		if (breathingMagnitude < MIN_BREATHING_MAG * MULTIPLY_BY) { breathingMagnitude = MIN_BREATHING_MAG * MULTIPLY_BY; } 
		else if (breathingMagnitude > MAX_BREATHING_MAG * MULTIPLY_BY) { breathingMagnitude = MAX_BREATHING_MAG * MULTIPLY_BY; }




		wchar_t strStamina[100];
		float stamina_display_value = (stamina - STAMINA_LOWER_LIMIT * MULTIPLY_BY) * 100 / ((STAMINA_UPPER_LIMIT - STAMINA_LOWER_LIMIT) * MULTIPLY_BY);
		if (staminaBar) { staminaBar->set(stamina_display_value); }
		wsprintf(strStamina, L"STAMINA: %d %%", int(stamina_display_value));
		if (staminaDisplay) staminaDisplay->set(strStamina);

		// AKV - update the health bar	
		if (healthBar && main_character)
		{
			wchar_t strHealth[100];
			Player* mPlayer = (Player*) main_character;
			float healthPercent = (mPlayer->health() / mPlayer->totalHealth()) * 100.f;	// determine current percentage of health

			healthBar->set(healthPercent);

			if (healthDisplay)
			{
				wsprintf(strHealth, L"HEALTH:    %d %% (LIVES LOST: %d)", int(healthPercent), playerLivesLost);
				healthDisplay->set(strHealth);
			}
		}

		// RYAN: BREATHING/STEPPING EFFECT
		breathingEffectCoordinate = 
			int(breathingEffectCoordinate + delta / (stamina / MULTIPLY_BY)) % 628;
		float CurrentBreathingDisplacementY = 
			sinf((float)breathingEffectCoordinate / 100) * breathingMagnitude / MULTIPLY_BY / 10;
		float CurrentSteppingDisplacementY = 
			sinf((float)walkingEffectCoordinate / 100) * STEPPING_MAGNITUDE;
		disp_y = CurrentBreathingDisplacementY + CurrentSteppingDisplacementY;
		// RYAN: This is the y position if not affected by the ceiling level.
		revisedPlayerEyeLevel = 5 + disp_y;
		// RYAN: Bring the eye level back to the default position, which is 5.
		main_character->translate(0, 5 - main_character->position().y, 0);
		if (lower_character_by > 0) {
			// RYAN: Does not apply the revised camera level directly for smooth rendering.
			//       The camera position gradually changes to the appropriate level.
			if (revisedPlayerEyeLevelLowered < lower_character_by) 
				revisedPlayerEyeLevelLowered += CHARACTER_COLLAPSE_RATIO;
			// RYAN: Force it to go below the ceiling, 
			//       if the eye level is above the bottom of ceiling object.
			if (revisedPlayerEyeLevelLowered < should_lower_by_at_least) 
				revisedPlayerEyeLevelLowered = should_lower_by_at_least;
			// RYAN: Apply changes
			main_character->translate(0, 0 - revisedPlayerEyeLevelLowered, 0); 
		} else { 
			if (revisedPlayerEyeLevelLowered > 0) 
				revisedPlayerEyeLevelLowered -= CHARACTER_COLLAPSE_RATIO * delta; 
			else revisedPlayerEyeLevelLowered = 0; 
		}
		breathing_intensity = int(breathingMagnitude / MULTIPLY_BY);
		// collision detection
		float probing_offset = float(tileSize) * 0.2f;
		//int safety_offset = (int)floor(probing_offset);
		Vector current_position = main_character->position();
		float current_x = current_position.x;
		float current_z = current_position.z;
		float target_x = current_x + disp_x;
		float target_z = current_z + disp_z;
		// RYAN: identifies if the player is on the edge of the tiles.
		bool is_on_right_end = false, is_on_left_end = false;
		bool is_on_top_end = false, is_on_bottom_end = false;
		if (fmod(current_x, float(tileSize)) <= probing_offset) is_on_left_end = true;
		if (fmod(current_x, float(tileSize)) >= float(tileSize) - probing_offset) is_on_right_end = true;
		if (fmod(current_z, float(tileSize)) <= probing_offset) is_on_bottom_end = true;
		if (fmod(current_z, float(tileSize)) >= float(tileSize) - probing_offset) is_on_top_end = true;
		// RYAN: applying offset. this prevents close objects not displayed appropriately.
		if (disp_x < 0) { target_x -= probing_offset; } else if (disp_x > 0) { target_x += probing_offset; }
		if (disp_z < 0) { target_z -= probing_offset; } else if (disp_z > 0) { target_z += probing_offset; }
		// RYAN: getting the indexes of the tile where the player is.
		current_tile_index_x = int(floor((current_x) / tileSize));
		current_tile_index_z = int(floor((current_z) / tileSize));
		// Getting tile type code of the nabouring cells.
		int nabour_tiles[3][3] = {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}}, i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				int cur_index_x = current_tile_index_x - 1 + j, cur_index_z = current_tile_index_z - 1 + i;
				if (cur_index_x >= 0 && cur_index_z >= 0 && cur_index_x < numTilesX && cur_index_z < numTilesZ) 
					nabour_tiles[i][j] = stage_tile_codes[cur_index_z][cur_index_x] % 4;
			}
		}
		int target_tile_index_x = int(floor((target_x) / tileSize));
		int target_tile_index_z = int(floor((target_z) / tileSize));
		// detects collision in x direction
		if (target_tile_index_x > current_tile_index_x) { // positive x direction
			if (nabour_tiles[1][2] == 2 || nabour_tiles[1][2] == 3 || nabour_tiles[1][2] == -1) { disp_x = 0; }
			else if (is_on_right_end && is_on_bottom_end && nabour_tiles[1][2] == 1) { disp_x = 0; }
			else if (is_on_right_end && is_on_top_end && nabour_tiles[2][2] == 1) { disp_x = 0; }
		} else if (target_tile_index_x < current_tile_index_x) { // negative x direction
			if (nabour_tiles[1][1] == 2 || nabour_tiles[1][1] == 3 || nabour_tiles[1][1] == -1) { disp_x = 0; }
			else if (is_on_left_end && is_on_bottom_end && nabour_tiles[1][0] == 1) { disp_x = 0; }
			else if (is_on_left_end && is_on_top_end && nabour_tiles[2][0] == 1) { disp_x = 0; }
		}
		// detects collision in z direction
		if (target_tile_index_z > current_tile_index_z) { // positive z direction (retreat)
			if (nabour_tiles[2][1] == 1 || nabour_tiles[2][1] == 3 || nabour_tiles[2][1] == -1) { disp_z = 0; }
			else if (is_on_right_end && is_on_top_end && nabour_tiles[2][2] == 2) { disp_z = 0; }
			else if (is_on_left_end && is_on_top_end && nabour_tiles[2][1] == 2) { disp_z = 0;  }
		} else if (target_tile_index_z < current_tile_index_z) { // negative z direction (forward)
			if (nabour_tiles[1][1] == 1 || nabour_tiles[1][1] == 3 || nabour_tiles[1][1] == -1) { disp_z = 0; }
			else if (is_on_right_end && is_on_bottom_end && nabour_tiles[0][2] == 2) { disp_z = 0; }
			else if (is_on_left_end && is_on_bottom_end && nabour_tiles[0][1] == 2) { disp_z = 0; }
		}


		if (context->pressed(TENTH_FLOOR_STARTOVER) && (timerStarted || gameFinished)) {
			if (gameFinished) {
				gameFinished = false;
				// RYAN: Give bonus items
				numSpeedItems += 1; 
				numDexterityItems += 1; 
				numRevertCollapseItems += 1;
				numStopCollapseItems += 1;
			}
			timerStarted = false;
			Vector cur_position = (Vector)main_character->position();
			main_character->translate(float(tileSize) * 0.5f - cur_position.x, 0, float(tileSize) * 0.5f - cur_position.z);
		} else { main_character->translate(disp_x, disp_y, disp_z); }

		if (walkingEffectCoordinate < 314 && steppingRadiusValue >= 314) { PlaySteppingSound(character_speed, now); }
		steppingRadiusValue = walkingEffectCoordinate;
		int inhale = 1;
		int breath_when = 50;
		PlayBreathingSound(breathing_intensity, now);

		breathingRadiusValue = breathingEffectCoordinate;
		// RYAN: Starts timer if not started.
		if (timerStarted == false && 
			current_tile_index_x == startTileIndexX && 
			current_tile_index_z == startTileIndexZ && 
			(previousTileIndexX != startTileIndexX || 
			previousTileIndexZ != startTileIndexZ)) {
				timerStartedOn = now;
				timerStarted = true;
				//gameFinished = false;
				// RYAN: Plays sound that notifies game start
				if (GameStart != NULL) {
					Vector start_sound_position = GameStart->position();
					GameStart->translate(0 - start_sound_position.x, 0 - start_sound_position.y, 0 - start_sound_position.z);
					GameStart->translate((float(startTileIndexX) + 0.5f) * float(tileSize), 5, (float(startTileIndexZ) + 0.5f) * float(tileSize));
					GameStart->forcePlay(); 
				}
		}

		// RYAN: ceiling collapse effect
		if (ceilingTiles != NULL && ceilingTileCurLocArray != NULL) {
			iObject* target_ceiling = ceilingTiles[current_tile_index_z][current_tile_index_x];
			float current_ceiling_position = target_ceiling->position().y - float(stageHeight) / 2;
			float target_ceiling_position = ceilingTileMaxLocArray[current_tile_index_z][current_tile_index_x];
			float previous_progress = ceilingTileCollapseProgress[current_tile_index_z][current_tile_index_x];
			float _progress_remaining = 1.0f - previous_progress;
			if (_progress_remaining > 0 && timerStarted && stopCollapseFor == 0 && revertCollapseFor == 0) {
				float _collapsing_ratio = 
					CEILING_COLLAPSE_RATIO * float_delta * (0.05f + 0.95f * (_progress_remaining ));
				target_ceiling->translate(0, 0 - _collapsing_ratio, 0);
			} else if (timerStarted && revertCollapseFor > 0 && previous_progress > 0.1f) {
				float _collapsing_ratio = 
					CEILING_COLLAPSE_RATIO * float_delta * (0.05f + 0.95f * (_progress_remaining ));
				target_ceiling->translate(0, _collapsing_ratio, 0);
			}
			float current_progress = (float(stageHeight) - current_ceiling_position) / (float(stageHeight) - target_ceiling_position);
			float phaseA = 0.45f, phaseB = 0.75f, phaseC = 0.9f;
			if (revertCollapseFor == 0) {
				if (previous_progress < 1.0f && current_progress >= 1.0f) {
					if (MachineTurnedOff != NULL) { MachineTurnedOff->forcePlay(); }
				} else if (previous_progress < phaseC && current_progress >= phaseC) {
					if (CeilingCollapse != NULL) { CeilingCollapse->forcePlay(); }
				} else if (previous_progress < phaseB && current_progress >= phaseB) {
					if (CeilingCollapseDistant != NULL) { CeilingCollapseDistant->forcePlay(); }
				} else if (previous_progress < phaseA && current_progress >= phaseA) {
					if (MachineTurnedOn != NULL) { MachineTurnedOn->forcePlay(); }
				} else if (previous_progress <= 0 && current_progress > 0) {
					if (CeilingCollapseDistant != NULL) { CeilingCollapseDistant->forcePlay(); }
				}
			} else {
				// RYAN: NOT IMPLEMENTED YET.
				//       IF PLAYER ACQUIRES 'REVERT' ITEM, CEILING STOPS COLLAPSING.
			}
			ceilingTileCurLocArray[current_tile_index_z][current_tile_index_x] = target_ceiling->position().y;
			// RYAN: Storing current ceiling collapse progress
			//		 This will be required for displaying game map in the later development phase.
			ceilingTileCollapseProgress[current_tile_index_z][current_tile_index_x] = current_progress;

		}

		if(current_tile_index_x != previousTileIndexX || current_tile_index_z != previousTileIndexZ && timerStarted) {
			if (stage_trap_codes[current_tile_index_z][current_tile_index_x] == 9) {
				// Stage Clear!!!
				gameFinished = true;
				timerStarted = false;
				if (GameClear != NULL) GameClear->forcePlay();
			}
		}

		previousTileIndexX = current_tile_index_x;
		previousTileIndexZ = current_tile_index_z;


		//if (camera_text) camera_text->set(str);
		//if (line1) line1->set(str1);
		//if (line2) line2->set(str2);
		//if (line3) line3->set(str3);


		if (speedUPBar) speedUPBar->set(increaseSpeedFor);
		if (dexterityBar) dexterityBar->set(increaseDexterityFor);
		if (revertCollapseBar) revertCollapseBar->set(revertCollapseFor);
		if (stopCollapseBar) stopCollapseBar->set(stopCollapseFor);
		if (testSprite) testSprite->updateSprite(now);
		if (increaseSpeedFor > 0) { speedUpIcon->setAlpha('\xFF'); } else { speedUpIcon->setAlpha('\x30'); }
		if (increaseDexterityFor > 0) { dexterityIcon->setAlpha('\xFF'); } else { dexterityIcon->setAlpha('\x30'); }
		if (revertCollapseFor > 0) { revertCollapseIcon->setAlpha('\xFF'); } else { revertCollapseIcon->setAlpha('\x30'); }
		if (stopCollapseFor > 0) { stopCollapseIcon->setAlpha('\xFF'); } else { stopCollapseIcon->setAlpha('\x30'); }

		int distance_disp = 0;
		wchar_t strDistance[100];
		if (timerStarted) {
			float distance_x = float(goal_index_x + 0.5) * tileSize  - main_character->position().x;
			float distance_z = float(goal_index_z) * tileSize - main_character->position().z;
			float root = sqrt(distance_x * distance_x + distance_z * distance_z);
			int distance_disp = int(root);
			if (distance_disp < 0) { distance_disp = 0; }
			int metres = int(floor(double(distance_disp) / 10));
			int decimalPoints = int(distance_disp % 10);
			wsprintf(strDistance, L"DISTANCE: %d.%d METRES", metres, decimalPoints);
		} else if (gameFinished) {
			wsprintf(strDistance, L"STAGE CLEAR! PRESS 'R' TO REPLAY.", distance_disp);
		} else {
			wsprintf(strDistance, L"GAME NOT STARTED", distance_disp);
		}

		if (distanceDisplay) distanceDisplay->set(strDistance);


		wchar_t strDispTime[100];
		if (timerStarted) {
			timeElapsed = now - timerStartedOn;
			int seconds = int(floor(long double(timeElapsed / 1000)));
			int miliseconds = int((timeElapsed % 1000) / 100);
			if (bestRecord >= 3600000) {
				wsprintf(strDispTime, L"TIME ELAPSED: %d.%d SEC.", seconds, miliseconds);
			} else {
				int bestSeconds = int(floor(long double(bestRecord / 1000)));
				int bestMiliseconds = int((bestRecord % 1000) / 100);
				wsprintf(strDispTime, L"TIME ELAPSED: %d.%d SEC. (BEST: %d.%d SEC.)", seconds, miliseconds, bestSeconds, bestMiliseconds);
			}
		} else if (gameFinished) {
			// RYAN: display time taken
			if (bestRecord > timeElapsed) { bestRecord = timeElapsed; }
			int seconds = int(floor(long double(timeElapsed / 1000)));
			int miliseconds = int((timeElapsed % 1000) / 100);
			if (bestRecord == timeElapsed) {
				wsprintf(strDispTime, L"BEST RECORD! CLEAR TIME: %d.%d SECONDS", seconds, miliseconds);
			} else {
				int bestSeconds = int(floor(long double(bestRecord / 1000)));
				int bestMiliseconds = int((bestRecord % 1000) / 100);
				wsprintf(strDispTime, L"TOTAL TIME ELAPSED: %d.%d SEC. (BEST: %d.%d SEC.)", seconds, miliseconds, bestSeconds, bestMiliseconds);
			}
		} else { 
			wsprintf(strDispTime, L"TIMER NOT SET");
		}
		if (timeDisplay) { timeDisplay->set(strDispTime); }


		//static float speedMax = 0;

		//GMOK: fog testing, while speed item is used, fog turns green
		// RYAN: ryan changed colour settings for each item activation
		if (increaseSpeedFor && increaseDexterityFor) {
			environment->setFogColor(FOGCOLOR_GREEN); 
		}
		else if (increaseSpeedFor) 
		{
			//if (!speedMax || increaseSpeedFor > speedMax)
			//	speedMax += increaseSpeedFor;
			//float r = 128 + (127* (increaseSpeedFor/ speedMax));
			//float g = 128 + (127* (increaseSpeedFor/ speedMax));
			//float b = 128 + (127* (increaseSpeedFor/ speedMax));

			//environment->setFogColor(D3DCOLOR_XRGB(0,(int)r,0));
			environment->setFogColor(FOGCOLOR_YELLOW);
		} 
		else if (increaseDexterityFor) 
		{

			environment->setFogColor(FOGCOLOR_BLUE);
			//environment->setFogStartEnd(FOGSTART_THICK, FOGEND_THICK);
		}
		else 
		{
			//speedMax = 0;
			environment->setFogColor(FOGCOLOR_DEFAULT);
		}

		//GMOK: fog testing, while revert item is used, fog becomes thin
		if (revertCollapseFor) 
		{

			environment->setFogStartEnd(FOGSTART_THIN, FOGEND_THIN);
		}
		else 
		{
			environment->setFogStartEnd(FOGSTART_DEFAULT, FOGEND_DEFAULT);
		}

		//GMOK: fog testing, while stop item is used, fog disappears
		if (stopCollapseFor) 
		{

			environment->toggleFog(false);
		}
		else 
		{
			environment->toggleFog(true);
		}

		// AKV - update all traps
		updateTraps(now);
	}

	//GMOK: Update next frame of billboard
	if (now - billLastUpdate > BILLBOARD_LATENCY)
	{
		torch1->attach(btTexture[tIndex]);
		torch2->attach(btTexture[tIndex++]);

		if (tIndex>4)
			tIndex = 0;
		billLastUpdate = now;
	}

	//GMOK: Orient torch billboard to always face player
	torch1->orient(main_character->world());
	torch2->orient(main_character->world());

	lastUpdate = now;
}


/*
AKV - used to handle collision detection on all traps, update player's health in response to a collision, manage constant
motion for all traps (if applicable), and update all traps
*/
void Design::updateTraps(int now)
{
	int delta = now - lastUpdate;

	// AKV - traps collision detection start	////////////////////////////////////////////////////////////

	/*
	check if a collision has occurred with the player and the "trap" and if so update the player's health reducing/increasing it by the
	trap's damage amount; otherwise, move the trap (constant movement)
	Note: if the player has lost all health, then move the player back to the starting position and restore the full health and increment
	the number of lives lost
	*/	

	// get the player's minimum and maximum boundry
	Vector pMin, pMax, p;
	float playerOffsetX = PLAYER_DIM_SIZE_X / 2.0f,
		playerOffsetY = PLAYER_DIM_SIZE_Y / 2.0f,
		playerOffsetZ = PLAYER_DIM_SIZE_Z / 2.0f;

	Trap* trp;
	float damage, pHealth;
	Player* mPlayer = (Player*)main_character;

	p = mPlayer->position();

	// determine the boundry based on the current position and offset values
	pMin = Vector(p.x - playerOffsetX, p.y - playerOffsetY, p.z - playerOffsetZ);
	pMax = Vector(p.x + playerOffsetX, p.y + playerOffsetY, p.z + playerOffsetZ);

	pHealth = mPlayer->health();	// get current health of player

	// traps collision detection
	for (int i = 0; i < MAX_TRAPS; i++)
	{
		if (traps[i])
		{
			trp = (Trap*) traps[i];

			if (trp)
			{
				if (trp->checkCollision(now, pMin, pMax))
				{
					// collision has occurred

					// update player's health
					// Note: damage if < 0 is destructive, > 0 bonus (one time only; object no longer exists after collision), or = 0 no change

					damage = trp->damage();	// trap's damage amount					

					// health bonus
					if (damage > 0)
					{

						// check if the player needs the health bonus (note if health is full, then nothing happens)
						if (pHealth != PLAYER_MAX_HEALTH)
						{

							// ensure the health bonus does not exceed the max health of the player
							if (pHealth + damage > PLAYER_MAX_HEALTH)
								pHealth = PLAYER_MAX_HEALTH;
							else
								pHealth += damage;

							mPlayer->setHealth(pHealth);

							// destroy the bonus (only one time collision allowed)
							traps[i]->Delete();

							// set value indicating it was deleted
							traps[i] = NULL;
							trp = NULL;

							// AKV TODO SOUND - play a sound indicating that the player has received a health bonus
							PlayHealthGainSound(); // RYAN->AKV: Sound added.
						}						
					}
					else if (pHealth + damage > 0.f)
					{

						// health loss but can still continue the game (i.e. has remaining health after collision)

						mPlayer->setHealth(mPlayer->health() + trp->damage());

						// indicate that the current collision has occurred
						trp->setCollision(now);

						// update player's current health
						pHealth = mPlayer->health();

						// AKV TODO SOUND - play a sound indicating that the player has received a health lost due to collision with a trap
						bool isMajorDamage = false;
						if (damage < -10.0f) isMajorDamage = true;
						PlayHealthLossSound(isMajorDamage); // RYAN->AKV: Sound added.
					}
					else
					{
						// player's health after collision is negative (i.e. has lost all health) and is game over

						// move to the initial position and reset the health
						mPlayer->setHealth(PLAYER_START_HEALTH);
						p = mPlayer->position();
						mPlayer->translate(-p.x, -p.y, -p.z);	// move back to the origin

						// move to the starting position
						main_character->translate(startCoordinateX + float(tileSize) / 2, 5, startCoordinateZ + float(tileSize) / 2);

						// increment the number of lives lost
						playerLivesLost++;
						// RYAN->AKV: Sound added.
						PlayGameOverSound();
					}
				}

				// perform constant movement (if the trap still exists)
				if (trp)
					trp->move(delta);
			}			
		}
	}

	// AKV - traps collision detection end  	////////////////////////////////////////////////////////////
}

void Design::PlayHealthGainSound() { DeafCured->forcePlay();}
void Design::PlayHealthLossSound(bool greatIntensity) { 
	// RYAN: Plays different sound clips
	//       in accordance of damage intensity.
	if (greatIntensity) {
		if (HealthLoss) HealthLoss->forcePlay(); 
	} else {
		if (HealthLossAlt) HealthLossAlt->forcePlay(); 
	}
}
void Design::PlayGameOverSound() { if (Death) Death->forcePlay(); }

// RYAN: This code initializes sounds from the specified files.
//
void Design::LoadStandardSoundClips() {

	if (FootStepTypeA==NULL) { FootStepTypeA = CreateSound(L"TenthFloorFootStepTypeA.wav", MOBILE_SOUND, false, false); main_character->attach(FootStepTypeA); }
	if (FootStepTypeB==NULL) { FootStepTypeB = CreateSound(L"TenthFloorFootStepTypeB.wav", MOBILE_SOUND, false, false); main_character->attach(FootStepTypeB); }
	if (FootStepTypeC==NULL) { FootStepTypeC = CreateSound(L"TenthFloorFootStepTypec.wav", MOBILE_SOUND, false, false); main_character->attach(FootStepTypeC); }
	if (FootStepTypeD==NULL) { FootStepTypeD = CreateSound(L"TenthFloorFootStepTypeD.wav", MOBILE_SOUND, false, false); main_character->attach(FootStepTypeD); }
	if (FootStepTypeE==NULL) { FootStepTypeE = CreateSound(L"TenthFloorFootStepTypeE.wav", MOBILE_SOUND, false, false); main_character->attach(FootStepTypeE); }
	if (FootStepTypeF==NULL) { FootStepTypeF = CreateSound(L"TenthFloorFootStepTypeF.wav", MOBILE_SOUND, false, false); main_character->attach(FootStepTypeF); }
	if (InhaleA == NULL) { InhaleA = CreateSound(L"TenthFloorBreathingInhale.wav", MOBILE_SOUND, false, false); }
	if (ExhaleA == NULL) { ExhaleA = CreateSound(L"TenthFloorBreathingExhale.wav", MOBILE_SOUND, false, false); }
	if (Environmental == NULL) { Environmental = CreateSound(L"TenthFloorEnvironmental.wav", LOCAL_SOUND, true, false); }
	if (DoorClose == NULL) { DoorClose = CreateSound(L"TenthFloorDoorClose.wav", LOCAL_SOUND, false, false); }
	if (Haste == NULL) { Haste = CreateSound(L"TenthFloorHaste.wav", MOBILE_SOUND, false, false); main_character->attach(Haste); }
	if (Dexterity == NULL) { Dexterity = CreateSound(L"TenthFloorDexterity.wav", MOBILE_SOUND, false, false); main_character->attach(Dexterity); }
	if (Cure==NULL) { Cure = CreateSound(L"TenthFloorCure.wav", MOBILE_SOUND, false, false); main_character->attach(Cure); }
	if (StaminaGained==NULL) { StaminaGained = CreateSound(L"TenthFloorStaminaGained.wav", MOBILE_SOUND, false, false); main_character->attach(StaminaGained); }
	if (TimeOut==NULL) { TimeOut = CreateSound(L"TenthFloorTimeOut.wav", GLOBAL_SOUND, false, false); }
	if (GhostTricks==NULL) { GhostTricks = CreateSound(L"TenthFloorGhostTricks.wav", MOBILE_SOUND, false, false); }
	if (ScaryVoice==NULL) { ScaryVoice = CreateSound(L"TenthFloorScaryVoice.wav", MOBILE_SOUND, false, false); }
	if (ScaryVoiceFemale==NULL) { ScaryVoiceFemale = CreateSound(L"TenthFloorScaryVoiceFemale.wav", MOBILE_SOUND, false, false); }
	if (ScaryVoiceMale==NULL) { ScaryVoiceMale = CreateSound(L"TenthFloorScaryVoiceMale.wav", MOBILE_SOUND, false, false); }
	if (Scream==NULL) { Scream = CreateSound(L"TenthFloorScreamFemale.wav", MOBILE_SOUND, false, false); }


	// RYAN: Global sounds
	if (GameStart==NULL) { GameStart = CreateSound(L"TenthFloorStart.wav", GLOBAL_SOUND, false, false); }
	if (GameClear==NULL) { GameClear = CreateSound(L"TenthFloorClear.wav", GLOBAL_SOUND, false, false); }
	if (MachineTurnedOff == NULL) { MachineTurnedOff = CreateSound(L"TenthFloorMachineTurnedOffDistant.wav", GLOBAL_SOUND, false, false); }
	if (MachineTurnedOn == NULL) { MachineTurnedOn = CreateSound(L"TenthFloorMachineTurnedOnDistant.wav", GLOBAL_SOUND, false, false); }
	if (CeilingCollapse == NULL) { CeilingCollapse = CreateSound(L"TenthFloorCeilingCollapse.wav", GLOBAL_SOUND, false, false); }
	if (CeilingCollapseDistant == NULL) { CeilingCollapseDistant = CreateSound(L"TenthFloorCeilingCollapseDistant.wav", GLOBAL_SOUND, false, false); }
	if (HealthLoss==NULL) { HealthLoss = CreateSound(L"TenthFloorHurt.wav", GLOBAL_SOUND, false, false); }
	if (HealthLossAlt==NULL) { HealthLossAlt = CreateSound(L"TenthFloorHurt2.wav", GLOBAL_SOUND, false, false); }
	if (Death==NULL) { Death = CreateSound(L"TenthFloorDead.wav", GLOBAL_SOUND, false, false); }
	if (Deaf==NULL) { Deaf = CreateSound(L"TenthFloorDeaf.wav", GLOBAL_SOUND, false, false); }
	if (DeafCured==NULL) { DeafCured = CreateSound(L"TenthFloorDeafCured.wav", GLOBAL_SOUND, false, false); }

}
// RYAN: This function triggers sounds when character is moving.
//
void Design::PlaySteppingSound(int speed, int now) {
	if (speed == 1) {
		if (FootStepTypeE != NULL && (stepNumber%8 == 2 || stepNumber%8 == 6)) { FootStepTypeE->forcePlay(); }
		else if (FootStepTypeF != NULL && (stepNumber%8 == 1 || stepNumber%8 == 4)) { FootStepTypeF->forcePlay(); }
		else if (FootStepTypeC != NULL && (stepNumber%8 == 0 || stepNumber%8 == 5)) { FootStepTypeC->forcePlay(); }
		else if (FootStepTypeD != NULL && (stepNumber%8 == 3 || stepNumber%8 == 7)) { FootStepTypeD->forcePlay(); }
	} else if (speed == 2) {
		if (FootStepTypeA != NULL && (stepNumber%8 == 0 || stepNumber%8 == 4)) { FootStepTypeA->forcePlay(); }
		else if (FootStepTypeB != NULL && (stepNumber%8 == 1 || stepNumber%8 == 6)) { FootStepTypeB->forcePlay(); }
		else if (FootStepTypeC != NULL && (stepNumber%8 == 2 || stepNumber%8 == 5)) { FootStepTypeC->forcePlay(); }
		else if (FootStepTypeD != NULL && (stepNumber%8 == 3 || stepNumber%8 == 7)) { FootStepTypeD->forcePlay(); }
	} else { }
	stepNumber++;
	if (stepNumber > 30000) {stepNumber = 0; }
}
// RYAN: Sound for fainting effect. Not being used. 
//
void Design::PlayBreathingSound(int intensity, int now) {
	if (intensity > 1) {
		//if (InhaleA != NULL && inhale) { InhaleA->forcePlay(now); }
		//else if (ExhaleA != NULL && !inhale) { ExhaleA->forcePlay(now); }
	}
}
// RYAN: This code loads map from the game board file and 
//       initializes tile information array with the new values.
//
void Design::LoadMap(wchar_t* file_name) {

	int cur_num_tiles_x = 0;
	int cur_num_tiles_z = 0;
	int len = strlen(MAP_DIRECTORY) + strlen(file_name) + 1;
	wchar_t* file = new wchar_t[len + 1];
	nameWithDir(file, MAP_DIRECTORY, file_name, len);
	char* converted_file_name = new char[len + 1];
	strcpyFromWC(converted_file_name, file, len + 1);
	FILE * stage_file;
	long stage_file_size;
	char* stage_file_buffer;
	size_t result;
	stage_file = fopen(converted_file_name, "rb" );
	if (stage_file != NULL) {
		fseek(stage_file, 0, SEEK_END);
		stage_file_size = ftell(stage_file);
		rewind(stage_file);
		stage_file_buffer = (char*)malloc(sizeof(char) * stage_file_size);
		result = fread (stage_file_buffer, 1, stage_file_size, stage_file);
		fclose (stage_file);


		const char row_delimiter[] = ";";
		const char column_delimiter[] = "|";
		const char data_delimiter[] = ",";
		char* duplicated_stage_file_buffer = (char*)calloc(strlen(stage_file_buffer) + 1, sizeof(char));
		strcpyCharToChar(duplicated_stage_file_buffer, stage_file_buffer, strlen(stage_file_buffer));
		char* token = strtok(stage_file_buffer, row_delimiter);
		int num_rows = 0;
		while(token != NULL) {
			num_rows++;
			token = strtok(NULL, row_delimiter);
		}
		char **buffer = (char**)calloc(num_rows, sizeof(char*));
		token = strtok(duplicated_stage_file_buffer, row_delimiter);
		char* first_token_cpy = (char*)calloc(strlen(token) + 1, sizeof(char));
		strcpyCharToChar(first_token_cpy, token, strlen(token));
		buffer[0] = (char*)first_token_cpy;
		for (int i = 1; i < num_rows; i++) {
			token = strtok(NULL, row_delimiter);
			char* cur_token_cpy = (char*)calloc(strlen(token) + 1, sizeof(char));
			strcpyCharToChar(cur_token_cpy, token, strlen(token));
			buffer[i] = (char*)cur_token_cpy;
		}
		char ***map_info = (char***)calloc(num_rows, sizeof(char**));
		int *num_columns_array = (int*)calloc(num_rows, sizeof(int));
		for (int j = 0; j < num_rows; j++) {
			if (strlen(buffer[j]) > 0) {
				char* row_info = (char*)calloc(strlen(buffer[j]) + 1, sizeof(char));
				char* duplicated_row_info = (char*)calloc(strlen(buffer[j]) + 1, sizeof(char));
				strcpyCharToChar(row_info, buffer[j], strlen(buffer[j]));
				strcpyCharToChar(duplicated_row_info, buffer[j], strlen(buffer[j]));

				char* row_token = strtok(row_info, column_delimiter);
				int num_columns = 0;
				while(row_token != NULL) {
					num_columns++;
					row_token = strtok(NULL, column_delimiter);
				}
				char **row_buffer = (char**)calloc(num_columns, sizeof(char*));
				row_token = strtok(duplicated_row_info, column_delimiter);
				char* first_row_token_cpy = (char*)calloc(strlen(row_token) + 1, sizeof(char));
				strcpyCharToChar(first_row_token_cpy, row_token, strlen(row_token));
				row_buffer[0] = (char*)first_row_token_cpy;
				for(int k = 1; k < num_columns; k++) {
					row_token = strtok(NULL, column_delimiter);
					char* cur_row_token_cpy = (char*)calloc(strlen(row_token) + 1, sizeof(char));
					strcpyCharToChar(cur_row_token_cpy, row_token, strlen(row_token));
					row_buffer[k] = (char*)cur_row_token_cpy;
				}
				map_info[j] = (char**)row_buffer;
				num_columns_array[j] = num_columns;
			}
		}
		char ****tile_info = (char****)calloc(num_rows, sizeof(char***));
		int **num_data_array = (int**)calloc(num_rows, sizeof(int*));
		cur_num_tiles_z = num_rows;
		for (int l = 0; l < num_rows; l++) {
			if (map_info[l] != NULL) {
				char** row_data = (char**)map_info[l];
				int num_cur_columns = num_columns_array[l];
				if (num_cur_columns > cur_num_tiles_x) { cur_num_tiles_x = num_cur_columns; }
				char ***tile_level_info = (char***)calloc(num_cur_columns, sizeof(char**));
				int *num_data_tile_level = (int*)calloc(num_cur_columns, sizeof(int));
				for (int m = 0; m < num_cur_columns; m++) {
					char* column_data = (char*)calloc(strlen((char*)row_data[m]) + 1, sizeof(char));
					char* duplicated_column_data = (char*)calloc(strlen((char*)row_data[m]) + 1, sizeof(char));
					strcpyCharToChar(column_data, (char*)row_data[m], strlen((char*)row_data[m]));
					strcpyCharToChar(duplicated_column_data, (char*)row_data[m], strlen((char*)row_data[m]));
					char* tile_token = strtok(column_data, data_delimiter);
					int num_data = 0;
					while(tile_token != NULL) {
						num_data++;
						tile_token = strtok(NULL, data_delimiter);
					}
					char **data_buffer = (char**)calloc(num_data, sizeof(char*));
					tile_token = strtok(duplicated_column_data, data_delimiter);
					char* first_data_token_cpy = (char*)calloc(strlen(tile_token) + 1, sizeof(char));
					strcpyCharToChar(first_data_token_cpy, tile_token, strlen(tile_token));
					data_buffer[0] = (char*)first_data_token_cpy;
					for (int n = 1; n < num_data; n++) {
						tile_token = strtok(NULL, data_delimiter);
						char* cur_data_token_cpy = (char*)calloc(strlen(tile_token) + 1, sizeof(char));
						strcpyCharToChar(cur_data_token_cpy, tile_token, strlen(tile_token));
						data_buffer[n] = (char*)cur_data_token_cpy;
					}
					tile_level_info[m] = (char**)data_buffer;
					num_data_tile_level[m] = num_data;
				}
				tile_info[l] = (char***)tile_level_info;
				num_data_array[l] = (int*)num_data_tile_level;
			}
		}
		numTilesX = cur_num_tiles_x;
		numTilesZ = cur_num_tiles_z;
		stage_tile_codes = (int**) malloc(numTilesZ * sizeof(int));
		stage_trap_codes = (int**) malloc(numTilesZ * sizeof(int));
		for (int i = 0; i < numTilesZ; i++) { 
			stage_tile_codes[i] = (int*) malloc(numTilesX * sizeof(int));
			stage_trap_codes[i] = (int*) malloc(numTilesX * sizeof(int));
		}
		for (int a = 0; a < numTilesZ; a++) {
			int cur_row_index = numTilesZ - a - 1;
			char*** row_data_read = (char***)tile_info[cur_row_index];
			int* num_column_data = (int*)num_data_array[a];
			for (int b = 0; b < numTilesX; b++) {
				char** column_data_read = (char**) row_data_read[b];
				int num_tile_data = num_column_data[b];
				for (int c = 0; c < num_tile_data; c++) {
					char* tile_data_read = (char*)column_data_read[c];
					switch(c) {
					case 0:
						if (tile_data_read != NULL) {
							int tile_type = 0;
							tile_type = atoi(tile_data_read);
							stage_tile_codes[a][b] = tile_type;
						}
						break;
					case 1:
						if (tile_data_read != NULL) {
							int trap_type = 0;
							trap_type = atoi(tile_data_read);
							stage_trap_codes[a][b] = trap_type;
						}
						break;
					case 2:
						break;
					}
				}
			}
		}
	} else { error(L"Error loading map data."); }
}


/*
AKV
Gets the entire string contents of the file specified.
Note: the caller of this method must remember to deallocate the memory used for the file contents when finished since this method
dynamically allocates memory but does not free it when execution of this method is completed
*/
char* Design::GetTrapMapContents(wchar_t* file_name) {

	int len = strlen(MAP_DIRECTORY) + strlen(file_name) + 1;
	wchar_t* file = new wchar_t[len + 1];
	nameWithDir(file, MAP_DIRECTORY, file_name, len);
	char* converted_file_name = new char[len + 1];
	strcpyFromWC(converted_file_name, file, len);
	FILE * trap_file;
	long trap_file_size;
	char* trap_file_buffer = NULL;
	size_t result;
	trap_file = fopen(converted_file_name, "rb" );

	if (trap_file != NULL) {

		// retrieve the entire contents of the file
		fseek(trap_file, 0, SEEK_END);
		trap_file_size = ftell(trap_file);
		rewind(trap_file);
		trap_file_buffer = new char[trap_file_size];
		result = fread (trap_file_buffer, 1, trap_file_size, trap_file);
		fclose (trap_file);
	}
	else { 
		error(L"Error loading trap map data."); 
	}

	// free up the memory used (except the memory used to hold the file contents)
	if (file)
		delete file;

	if (converted_file_name)
		delete converted_file_name;

	return trap_file_buffer;
}


/*
AKV - creates a Floor Spike from the initial position of the floor tile (bottom left close point) and the specifications for the trap
from the trap file entry (returns NULL if specifications is invalid)
*/
iObject* Design::CreateTrapFloorSpike(Vector floorTilePos, const char* trapSpec, Colour c, iTexture* t)
{
	iObject* trpFlrSpike = NULL;

	// delimiters
	const char column_delimiter[] = "|";
	const char data_delimiter[] = ",";

	bool isError = false;

	if (trapSpec)
	{

		// trap specification temporary data
		const int MAX_COLUMN_COUNT = 7;

		int trapSubType;
		float px, py, pz;	// percentage of the x, y, and z size for the trap
		float posx, posy, posz;	// percentage of the x, y, and z translation for the trap from origin
		float pctDamage;	// the percentage to player's health the trap inflicts upon collision
		int noSpikes;	// number of spikes for the floor spike trap

		char* columnToken;	// current column in the entire specs
		char* spec = new char[strlen(trapSpec) + 1];	// copy of the specifications		
		int colCount = 1;
		char* contextToken = NULL;

		strcpyCharToChar(spec, trapSpec, strlen(spec));

		columnToken = strtok_s(spec, column_delimiter, &contextToken);

		/*
		Sample format would be: 
		trapType|order|trapSubType|px,py,pz|posx,posy,posz|pctDamage|mvx,mvy,mvz|rx,ry|rz|pminx,pmax,pimy,pmaxy,pminz,pmaxz
		*/
		// get the data from each column
		while(columnToken != NULL && !isError && (colCount <= MAX_COLUMN_COUNT)) {

			switch(colCount)
			{
			case 1:	// do nothing since this is the trap type (skip this)
				break;

			case 2:	// do nothing since this is whether the trap is for the same tile (skip this)
				break;

			case 3:	// get the floor spike subtype value
				if (sscanf_s(columnToken, "%d", &trapSubType) == 1)
				{
					if (trapSubType < 1 || trapSubType > 8)
						isError = true;
				}
				else
					isError = true;
				break;

			case 4:	// percentage of the trap's size x, y, and z
				if (sscanf_s(columnToken, "%f,%f,%f", &px, &py, &pz) != 3)
					isError = true;
				break;

			case 5:	// percentage of translation of trap from initial origin
				if (sscanf_s(columnToken, "%f,%f,%f", &posx, &posy, &posz) != 3)
					isError = true;
				break;

			case 6:	// get the percentage (positive or negative) for the damage to the player
				if (sscanf_s(columnToken, "%f", &pctDamage) != 1)
					isError = true;
				break;

			case 7:	// get the number of spikes
				if (sscanf_s(columnToken, "%d", &noSpikes) != 1)
					isError = true;
			}

			colCount++;

			columnToken = strtok_s(NULL, column_delimiter, &contextToken);

		}	// end while

		if (!isError)
		{			
			const float PADDING_PCT = 0.95f;
			const float PADDED_CONSTANT_TILE_SIZE = (CONSTANT_TILE_SIZE * PADDING_PCT);
			const float PADDED_CONSTANT_STAGE_HEIGHT = (CONSTANT_STAGE_HEIGHT * PADDING_PCT);

			float sizeX, sizeY, sizeZ;

			sizeX = PADDED_CONSTANT_TILE_SIZE * px;
			sizeY = PADDED_CONSTANT_STAGE_HEIGHT * py;
			sizeZ = PADDED_CONSTANT_TILE_SIZE * pz;

			// create the floor spike with the specifications obtained
			trpFlrSpike = CreateFloorSpike(0, 0, 0, sizeX, sizeZ, noSpikes, sizeY, pctDamage * PLAYER_MAX_HEALTH, c);

			if (t)
				trpFlrSpike->attach(t);

			Vector lb;
			Vector ub;

			// move it to the correct position
			switch(trapSubType)
			{
				// 1 - farway edge x-axis
			case 1:
				floorTilePos.x += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);			
				trpFlrSpike->translate(floorTilePos.x, floorTilePos.y, floorTilePos.z + PADDED_CONSTANT_TILE_SIZE - sizeZ);
				break;

				// 2 - close edge x-axis
			case 2:
				floorTilePos.x += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				floorTilePos.z += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				trpFlrSpike->translate(floorTilePos.x, floorTilePos.y, floorTilePos.z);
				break;

				// 3 - edge left z-axis
			case 3:
				floorTilePos.x += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				trpFlrSpike->translate((floorTilePos.x - PADDED_CONSTANT_TILE_SIZE/2.0f) + sizeZ,
					floorTilePos.y, floorTilePos.z + PADDED_CONSTANT_TILE_SIZE/2.0f);					
				trpFlrSpike->rotatey(PI_CONSTANT * (90/180.f));

				// recalculate the dimensions of the floor spike after rotation
				lb = Vector(0, 0, 0);
				ub = Vector(sizeZ, sizeY, sizeX);
				((FloorSpike*)trpFlrSpike)->setDimensions(lb, ub);
				break;

				// 4 - edge right z-axis
			case 4:
				floorTilePos.x += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				trpFlrSpike->translate((floorTilePos.x + PADDED_CONSTANT_TILE_SIZE/2.0f) - sizeZ,
					floorTilePos.y, floorTilePos.z + PADDED_CONSTANT_TILE_SIZE/2.0f);
				trpFlrSpike->rotatey(PI_CONSTANT * (90/180.f));

				// recalculate the dimensions of the floor spike after rotation
				lb = Vector(0, 0, 0);
				ub = Vector(sizeZ, sizeY, sizeX);
				((FloorSpike*)trpFlrSpike)->setDimensions(lb, ub);
				break;

				// 5 - middle x-axis
			case 5:
				floorTilePos.x += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				floorTilePos.z += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				trpFlrSpike->translate(floorTilePos.x, floorTilePos.y, floorTilePos.z);
				trpFlrSpike->translate(0, 0, PADDED_CONSTANT_TILE_SIZE/2.0f);
				break;

				// 6 - middle z-axis
			case 6:
				floorTilePos.x += (CONSTANT_TILE_SIZE - PADDED_CONSTANT_TILE_SIZE);
				trpFlrSpike->translate(floorTilePos.x, floorTilePos.y, floorTilePos.z + PADDED_CONSTANT_TILE_SIZE/2.0f);
				trpFlrSpike->rotatey(PI_CONSTANT * (90/180.f));

				// recalculate the dimensions of the floor spike after rotation
				lb = Vector(0, 0, 0);
				ub = Vector(sizeZ, sizeY, sizeX);
				((FloorSpike*)trpFlrSpike)->setDimensions(lb, ub);
				break;

				// 7 - diagonal from farway left to close right
			case 7:
				trpFlrSpike->translate(floorTilePos.x, floorTilePos.y, floorTilePos.z + PADDED_CONSTANT_TILE_SIZE/2.0f);
				trpFlrSpike->rotatey(PI_CONSTANT * (-45/180.f));
				break;

				// 8 - diagonal from farway right to close left
			case 8:
				trpFlrSpike->translate(floorTilePos.x, floorTilePos.y, floorTilePos.z + PADDED_CONSTANT_TILE_SIZE/2.0f);
				trpFlrSpike->rotatey(PI_CONSTANT * (45/180.f));
				break;
			}

			// apply the translation for the trap with respect to the origin based on percentage of the tile size
			trpFlrSpike->translate(posx * CONSTANT_TILE_SIZE, posy * CONSTANT_TILE_SIZE, posz * CONSTANT_TILE_SIZE);
		}
	}

	return trpFlrSpike;
}


/*
AKV - creates a Projectile from the initial position of the floor tile (bottom left close point) and the specifications for the Projectile
from the trap file entry (returns NULL if specifications is invalid)
*/
iObject* Design::CreateTrapProjectile(Vector floorTilePos, const char* trapSpec, Colour c, iTexture* t)
{
	iObject* trpPrjtile = NULL;

	// delimiters
	const char column_delimiter[] = "|";
	const char data_delimiter[] = ",";

	bool isError = false;

	if (trapSpec)
	{

		// trap specification temporary data
		const int MAX_COLUMN_COUNT = 9;

		ProjectileType prjType;	// the type of projectile to create
		int trapSubType;
		float px, py, pz;	// percentage of the x, y, and z size for the trap
		float posx, posy, posz;	// percentage of the x, y, and z translation for the trap from origin
		float pctDamage;	// the percentage to player's health the projectile inflicts upon collision
		Vector mv;	// the speed for constant movement
		Vector rot;	// the rotation for constant movement
		float pminx, pmaxx, pminy, pmaxy, pminz, pmaxz;	// percentage of movement with respect to a single tile size in the respective axis

		char* columnToken;	// current column in the entire specs
		char* spec = new char[strlen(trapSpec) + 1];	// copy of the specifications		
		int colCount = 1;
		char* contextToken = NULL;

		strcpyCharToChar(spec, trapSpec, strlen(spec));

		columnToken = strtok_s(spec, column_delimiter, &contextToken);

		// Sample format would be:	2|3|0.1,0.1,0.1|-0.3|1,0,0|0,1,0|-0.5,0.5,0,0,0,0;
		// get the data from each column
		while(columnToken != NULL && !isError && (colCount <= MAX_COLUMN_COUNT)) {

			switch(colCount)
			{
			case 1:	// do nothing since this is the trap type (skip this)
				break;

			case 2:	// do nothing since this is whether the trap is for the same tile (skip this)
				break;

			case 3:	// get the atom embedded projectile subtype value
				if (sscanf_s(columnToken, "%d", &trapSubType) == 1)
				{
					if (trapSubType < 1 || trapSubType > 6)
						isError = true;
					else
						prjType = getPrjTypeFromIndx(trapSubType);
				}
				else
					isError = true;
				break;

			case 4:	// percentage of the trap's size x, y, and z
				if (sscanf_s(columnToken, "%f,%f,%f", &px, &py, &pz) != 3)
					isError = true;
				break;

			case 5:	// percentage of translation of trap from initial origin
				if (sscanf_s(columnToken, "%f,%f,%f", &posx, &posy, &posz) != 3)
					isError = true;
				break;

			case 6:	// get the percentage (positive or negative) for the damage to the player
				if (sscanf_s(columnToken, "%f", &pctDamage) != 1)
					isError = true;
				break;

			case 7:	// get the percentage of speed for constant movement
				if (sscanf_s(columnToken, "%f,%f,%f", &mv.x, &mv.y, &mv.z) != 3)
					isError = true;
				break;

			case 8:	// get the percentage of rotation for constant movement
				if (sscanf_s(columnToken, "%f,%f,%f", &rot.x, &rot.y, &rot.z) != 3)
					isError = true;
				break;

			case 9:	// get the percentage of minimum and maximum boundries in the respective axises
				if (sscanf_s(columnToken, "%f,%f,%f,%f,%f,%f", &pminx, &pmaxx, &pminy, &pmaxy, &pminz, &pmaxz) != 6)
					isError = true;
				break;
			}

			colCount++;

			columnToken = strtok_s(NULL, column_delimiter, &contextToken);

		}	// end while

		if (!isError)
		{
			const float PADDING_PCT = 0.03f;	// 3% away from the walls
			const float PADDED_CONSTANT_TILE_SIZE = (CONSTANT_TILE_SIZE * 1.f - PADDING_PCT);
			const float PADDED_CONSTANT_STAGE_HEIGHT = (CONSTANT_STAGE_HEIGHT * 1.f - PADDING_PCT);

			float sizeX, sizeY, sizeZ;

			sizeX = PADDED_CONSTANT_TILE_SIZE * px;
			sizeY = PADDED_CONSTANT_STAGE_HEIGHT * py;
			sizeZ = PADDED_CONSTANT_TILE_SIZE * pz;

			// create the projectile spike with the specifications obtained
			trpPrjtile = CreateProjectile(0, 0, 0, sizeX, sizeY, sizeZ, PLAYER_MAX_HEALTH * pctDamage, c, prjType);

			// attach the texture
			if (t)
				trpPrjtile->attach(t);

			// move it to the centered position in all directions
			trpPrjtile->translate(floorTilePos.x + CONSTANT_TILE_SIZE/2.0f, floorTilePos.y + CONSTANT_STAGE_HEIGHT/2.0f,
				floorTilePos.z + CONSTANT_TILE_SIZE/2.0f);

			// apply the translation for the trap with respect to the origin based on percentage of the tile size
			trpPrjtile->translate(posx * CONSTANT_TILE_SIZE, posy * CONSTANT_STAGE_HEIGHT, posz * CONSTANT_TILE_SIZE);

			// apply constant rotation
			rot *= TRAPS_CONSTANT_ROLL;	// get the actual rotation from the percentage multipled by the constant roll for traps
			((Projectile*)trpPrjtile)->setRotation(rot);

			// apply constant movement
			Vector lowerBound, upperBound;	// the boundries for the movement

			lowerBound = upperBound = Vector(floorTilePos.x + CONSTANT_TILE_SIZE/2.0f, floorTilePos.y + CONSTANT_STAGE_HEIGHT/2.0f,
				floorTilePos.z + CONSTANT_TILE_SIZE/2.0f);

			if (pminx)
				lowerBound.x += (CONSTANT_TILE_SIZE * pminx);
			else
				lowerBound.x -= sizeX;

			if (pminy)
				lowerBound.y += (CONSTANT_STAGE_HEIGHT * pminy);
			else
				lowerBound.y -= sizeY;

			if (pminz)
				lowerBound.z += (CONSTANT_TILE_SIZE * pminz);
			else
				lowerBound.z -= sizeZ;

			if (pmaxx)
				upperBound.x += (CONSTANT_TILE_SIZE * pmaxx);
			else
				upperBound.x += sizeX;

			if (pmaxy)
				upperBound.y += (CONSTANT_STAGE_HEIGHT * pmaxy);
			else
				upperBound.y += sizeY;

			if (pmaxz)
				upperBound.z += (CONSTANT_TILE_SIZE * pmaxz);
			else
				upperBound.z += sizeZ;

			// apply the translation of the projectile to the lower and upper vector boundries

			// lower bound
			lowerBound.x += (CONSTANT_TILE_SIZE * posx);
			lowerBound.y += (CONSTANT_TILE_SIZE * posy);
			lowerBound.z += (CONSTANT_TILE_SIZE * posz);

			// upper bound
			upperBound.x += (CONSTANT_TILE_SIZE * posx);
			upperBound.y += (CONSTANT_TILE_SIZE * posy);
			upperBound.z += (CONSTANT_TILE_SIZE * posz);

			mv *= FORWARD_SPEED;	// get the actual speed for constant movement from the percentage multipled by the forward speed
			((Projectile*)trpPrjtile)->setMovement(lowerBound, upperBound, mv);
		}
	}

	return trpPrjtile;
}


/*
AKV - creates an Atom from the initial position of the floor tile (bottom left close point) and the specifications for the Atom
from the trap file entry (returns NULL if specifications is invalid)
*/
iObject* Design::CreateTrapAtom(Vector floorTilePos, const char* trapSpec, Colour cBox, Colour cSpikes, iTexture* tBox, iTexture* tSpike)
{
	iObject* trpAtom= NULL;

	// delimiters
	const char column_delimiter[] = "|";
	const char data_delimiter[] = ",";

	bool isError = false;

	if (trapSpec)
	{

		// trap specification temporary data
		const int MAX_COLUMN_COUNT = 6;

		int trapSubType;
		float px, py, pz;	// percentage of the x, y, and z size for the trap
		float posx, posy, posz;	// percentage of the x, y, and z translation for the trap from origin
		float pctDamage;	// the percentage to player's health the atom inflicts upon collision
		ProjectileType prjType;	// the value for the embedded projectile type

		char* columnToken;	// current column in the entire specs
		char* spec = new char[strlen(trapSpec) + 1];	// copy of the specifications		
		int colCount = 1;
		char* contextToken = NULL;

		strcpyCharToChar(spec, trapSpec, strlen(spec));

		columnToken = strtok_s(spec, column_delimiter, &contextToken);

		// Sample format would be:	trapType|order|trapSubType|px,py,pz|posx,posy,posz|pctDamage
		// get the data from each column
		while(columnToken != NULL && !isError && (colCount <= MAX_COLUMN_COUNT)) {

			switch(colCount)
			{
			case 1:	// do nothing since this is the trap type (skip this)
				break;

			case 2:	// do nothing since this is whether the trap is for the same tile (skip this)
				break;

			case 3:	// get the atom embedded projectile subtype value
				if (sscanf_s(columnToken, "%d", &trapSubType) == 1)
				{
					if (trapSubType < 1 || trapSubType > 6)
						isError = true;
					else
						prjType = getPrjTypeFromIndx(trapSubType);

				}
				else
					isError = true;
				break;

			case 4:	// percentage of the trap's size x, y, and z
				if (sscanf_s(columnToken, "%f,%f,%f", &px, &py, &pz) != 3)
					isError = true;
				break;

			case 5:	// percentage of translation of trap from initial origin
				if (sscanf_s(columnToken, "%f,%f,%f", &posx, &posy, &posz) != 3)
					isError = true;
				break;

			case 6:	// get the percentage (positive or negative) for the damage to the player
				if (sscanf_s(columnToken, "%f", &pctDamage) != 1)
					isError = true;
				break;
			}

			colCount++;

			columnToken = strtok_s(NULL, column_delimiter, &contextToken);

		}	// end while

		if (!isError)
		{
			float paddingX, paddingY, paddingZ;
			const float PADDING_PCT = 0.03f;	// 3% away from the walls
			const float PADDED_CONSTANT_TILE_SIZE = (CONSTANT_TILE_SIZE * 1.f - PADDING_PCT);
			paddingX = paddingY = paddingZ = CONSTANT_TILE_SIZE * PADDING_PCT;

			float sizeX, sizeY, sizeZ;

			sizeX = (CONSTANT_TILE_SIZE - paddingX) * px;
			sizeY = (CONSTANT_TILE_SIZE - paddingY) * py;
			sizeZ = (CONSTANT_TILE_SIZE - paddingZ) * pz;

			// create the floor spike with the specifications obtained
			trpAtom = CreateAtom(0, 0, 0, sizeX, sizeY, sizeZ, PLAYER_MAX_HEALTH * pctDamage, cBox, cSpikes, prjType,
				(pctDamage <= 0.f ? 0.25f : pctDamage));

			// attach appropriate textures
			if (tBox)
				((Atom*)trpAtom)->attachBoxTexture(tBox);

			if (tSpike)
				((Atom*)trpAtom)->attachSpikeTexture(tSpike);

			// move it to the centered position in all directions
			trpAtom->translate(floorTilePos.x + CONSTANT_TILE_SIZE/2.0f - sizeX/2.0f, floorTilePos.y + CONSTANT_TILE_SIZE/2.0f + sizeY/2.0f,
				floorTilePos.z + CONSTANT_TILE_SIZE/2.0f + sizeZ/2.0f);

			// apply the translation for the trap with respect to the origin based on percentage of the tile size
			trpAtom->translate(posx * CONSTANT_TILE_SIZE, posy * CONSTANT_TILE_SIZE, posz * CONSTANT_TILE_SIZE);

			// apply constant rotation
			((Atom*)trpAtom)->setBoxRotation(Vector(0, TRAPS_CONSTANT_ROLL / 2, 0));
			((Atom*)trpAtom)->setSpikeRotation(Vector(0, TRAPS_CONSTANT_ROLL, TRAPS_CONSTANT_ROLL));

		}
	}

	return trpAtom;
}


/*
AKV
Converts an integer value to a enum of ProjectileType.
*/
ProjectileType Design::getPrjTypeFromIndx(int indx)
{
	ProjectileType ret;

	switch (indx)
	{
	case 2:
		ret = CROSS;
		break;

	case 3:
		ret = STAR;
		break;

	case 4:
		ret = DIAGONAL_LTR;
		break;

	case 5:
		ret = DIAGONAL_RTL;
		break;

	case 6:
		ret = PIECE_WISE;
		break;

	case 1:
	default:
		ret = DOUBLE_EDGE_SPEAR;
		break;
	}

	return ret;
}