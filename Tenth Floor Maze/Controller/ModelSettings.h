#ifndef _MODEL_SETTINGS_H_
#define _MODEL_SETTINGS_H_

/* Header for Configuring the Components of the Model Branch
 *
 * ModelSettings.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "Configuration.h" // framework-wide configuration settings

#define CONSTANT_TILE_SIZE 10		// AKV
#define CONSTANT_STAGE_HEIGHT 30	// AKV
#define ITEM_HASTE_DURATION					10000
#define ITEM_DEXTERITY_DURATION				10000
#define ITEM_REVERT_COLLAPSING_DURATION		50000
#define ITEM_STOP_COLLAPSING_DURATION		50000
#define ITEM_CASTING_WAIT_TIME				1000
#define CEILING_COLLAPSE_RATIO 0.01f
#define CHARACTER_COLLAPSE_RATIO 0.05f
#define CHARACTER_ACCELERATION 0.02f
#define MOUSE_PANNING_SENSITIVITY 10.0f
#define KEYBOARD_PANNING_SENSITIVITY 7.0f
#define CAMERA_ADVANCE_COEFFICIENT 2.0f
#define CAMERA_RETREAT_COEFFICIENT 1.5f
#define STEPPING_MAGNITUDE 0.4f
#define DEFAULT_BREATHING_FREQUENCY 0.05f 
#define MAXIMUM_BREATHING_FREQUENCY 0.2f
#define DEFAULT_breathing_effect_magnitude 0.005f
#define MAXIMUM_breathing_effect_magnitude 0.03f
#define BREATHING_FREQUENCY 0.2f
#define breathing_effect_magnitude 0.05f
#define MAX_BREATHING_MAG 10
#define MIN_BREATHING_MAG 1
#define STAMINA_LOWER_LIMIT 1
#define STAMINA_UPPER_LIMIT 4
#define MULTIPLY_BY 200000
#define DEFAULT_MAP		{{ 3, 3, 3, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 3}, \
						{ 2, 2, 1, 1, 1, 2, 2, 0, 2, 0, 0, 1, 2, 0, 0, 3, 2, 2, 0, 2}, \
						{ 2, 2, 1, 1, 2, 2, 2, 0, 1, 1, 1, 2, 2, 0, 0, 2, 2, 2, 0, 2}, \
						{ 2, 1, 1, 1, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2}, \
						{ 2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 2, 1, 2, 3, 0, 2, 2, 0, 2}, \
						{ 3, 1, 1, 1, 1, 2, 3, 1, 1, 2, 2, 1, 2, 2, 2, 3, 0, 2, 0, 2}, \
						{ 2, 0, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, 2}, \
						{ 2, 0, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 3, 1, 2}, \
						{ 2, 0, 1, 1, 1, 0, 2, 0, 0, 2, 0, 1, 1, 0, 1, 0, 1, 2, 0, 2}, \
						{ 3, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 3, 1, 1, 1, 2, 2, 2, 0, 2}, \
						{ 3, 1, 1, 2, 3, 2, 0, 0, 0, 2, 2, 2, 3, 1, 2, 2, 2, 0, 0, 2}, \
						{ 2, 3, 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 3, 1, 1, 2}, \
						{ 2, 2, 0, 2, 3, 0, 1, 1, 1, 0, 2, 2, 2, 2, 2, 2, 2, 3, 0, 2}, \
						{ 2, 1, 1, 0, 2, 3, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2}, \
						{ 2, 3, 1, 2, 2, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 2, 2, 2, 2}, \
						{ 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 2, 2, 2, 2, 2, 2}, \
						{ 2, 3, 1, 1, 1, 1, 1, 2, 0, 0, 2, 2, 1, 1, 0, 1, 0, 2, 2, 2}, \
						{ 2, 2, 1, 1, 1, 2, 0, 2, 0, 0, 2, 2, 1, 1, 3, 1, 2, 2, 2, 2}, \
						{ 2, 2, 0, 0, 0, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 2, 2}, \
						{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 3}};



#define RYAN_MOUSE_PANNING_SENSITIVITY 10.0f
#define RYAN_KEYBOARD_PANNING_SENSITIVITY 7.0f
#define RYAN_CAMERA_ADVANCE_COEFFICIENT 2.0f
#define RYAN_CAMERA_RETREAT_COEFFICIENT 1.5f
#define RYAN_STEPPING_FREQUENCY 2
#define RYAN_STEPPING_MAGNITUDE 0.03f
#define RYAN_DEFAULT_BREATHING_FREQUENCY 0.05f
#define RYAN_MAXIMUM_BREATHING_FREQUENCY 0.2f
#define RYAN_DEFAULT_breathing_effect_magnitude 0.005f
#define RYAN_MAXIMUM_breathing_effect_magnitude 0.03f
#define RYAN_BREATHING_FREQUENCY_COEFFICIENT 0.0001f
#define RYAN_breathing_effect_magnitude_COEFFICIENT 0.0002f

// latency - keystroke time interval in system time units (UNITS_PER_SEC)
#define LIGHT_LATENCY (UNITS_PER_SEC / 2)
#define SOUND_LATENCY (UNITS_PER_SEC / 2000)
#define MODEL_LATENCY (UNITS_PER_SEC / 2)
#define SND_OVERWRITE 4 // factor on SOUND_LATENCY for overwriting status
#define SND_TXT_ON  L"+" // symbol for on
#define SND_TXT_OFF L"o" // symbol for off

// lighting parameters
//
// initial light settings
#define LIGHT_POINT_0   false
#define LIGHT_SPOT_0    false
#define LIGHT_DISTANT_0 false
#define LIGHT_AMBIENT   0.2f  // all three colour components [0.0f,1.0f]
#define LGT_TXT_ON  L"+" // symbol for on
#define LGT_TXT_OFF L"o" // symbol for off
#define LIGHT_ROLL      0.0002f

// camera parameter
//
// lowest possible y value in world space
#define FLOOR  -50

// scene parameters
//
// motion factors applied to the time interval
#define FORWARD_SPEED 10.0f / UNITS_PER_SEC
#define ROT_SPEED     0.03f * FORWARD_SPEED
#define CONSTANT_ROLL 10.0f * ROT_SPEED
#define PI_CONSTANT 3.14159265f	// AKV

// AKV - traps related settings
#define TRAPS_COLLISION_LATENCY 1200 // (in seconds) how much time is passed for another collision from last collision
#define TRAPS_CONSTANT_ROLL 200.f * ROT_SPEED

// AKV - following are the trap type indicators for each trap specification entry in the trap map text file
#define TRAPS_MAP_FILE_FLOOR_SPIKE 10
#define TRAPS_MAP_FILE_PROJECTILE 20
#define TRAPS_MAP_FILE_ATOM 30

// AKV - used in the map text file to indicate that a trap is at current tile and retrieve from trap map text file
#define TRAPS_MAP_FILE_IS_TRAP 5

// AKV - player related
#define PLAYER_DIM_SIZE_X CONSTANT_TILE_SIZE * 0.4f
#define PLAYER_DIM_SIZE_Y CONSTANT_TILE_SIZE * 0.7f
#define PLAYER_DIM_SIZE_Z CONSTANT_TILE_SIZE * 0.4f
#define PLAYER_START_HEALTH 100.f
#define PLAYER_MAX_HEALTH 100.f

// audio controls
//
// initial sound settings
#define DELTA_VOLUME     200  // increment within [10000,10000]
#define FREQ_RANGE      5000  // in Hertz (cycles per sec)
#define FREQ_DROP_VELOCITY 8  // rate of fall to idle frequency
#define FREQ_RISE_VELOCITY 4  // rate of rise to maximum frequency

// input device motion conversion factors - 
//
// mouse motion conversion factors



#define MOUSE_DISPLACEMENT_TO_WORLD_ROTATION     80
#define MOUSE_DISPLACEMENT_TO_WORLD_DISPLACEMENT 5.f
#define MOUSE_ROTATION_TO_WORLD_ROTATION		 .1f
#define MOUSE_BUTTON_SCALE                       10
// controller conversion factors
#define CTR_DISPLACEMENT_FACTOR 0.015f 
#define CTR_ROTATION_FACTOR     0.015f 

// hud and text parameters
//
// hud location within window [0,1]
#define HUD_X     0.0f
#define HUD_Y     0.0f
#define HUD_W     1.0f
#define HUD_H     0.4f
// hud background degree of transparency [\x00,\xff]
#define HUD_A_DEFAULT     '\x20'
//GMOK: HUDTexture images
#define HUD_BGROUND L"hudBackground.bmp"
#define HUD_PROGRESS_RED L"hudProgressBarRed.bmp"
#define HUD_PROGRESS_ORANGE L"hudProgressBarOrange.bmp"
#define HUD_PROGRESS_YELLOW L"hudProgressBarYellow.bmp"
#define HUD_PROGRESS_GREEN L"hudProgressBarGreen.bmp"
#define HUD_PROGRESS_BLUE L"hudProgressBarBlue.bmp"
#define HUD_PROGRESS_PURPLE L"hudProgressBarPurple.bmp"
#define HUD_PROGRESS_WHITE L"hudProgressBarWhite.bmp"
#define HUD_PROGRESS_BLACK L"hudProgressBarBlack.bmp"

#define HUD_SPRITE_ARROW1 L"arrow.bmp"
#define HUD_SPRITE_BLACKTORCH L"blackTorch.bmp"

#define HUD_SPRITE_LATENCY (UNITS_PER_SEC / 10)
#define BILLBOARD_LATENCY (UNITS_PER_SEC / 15)
#define HUD_SPEED (0.5f /* screen units per sec */ / UNITS_PER_SEC) 

#define HUDT_MAX    1.00f
#define HUDT_MIN    0.00f

//GMOK: HUDTexture type
#define HUDT_STATIC 0
#define HUDT_PROGRESS 1
#define HUDT_SPRITE 2
// text limits within the hud [0,1]
#define TL_MAX    0.99f
#define TL_MIN    0.01f
#define R_MIN     0.20f
// Reporting text - maximum number of items
#define MAX_RPTS  5

#endif

