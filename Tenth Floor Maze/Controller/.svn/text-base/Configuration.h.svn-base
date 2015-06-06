#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

/* The Pre-Defined Configuration
 *
 * Configuration.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

// Timing Factors
//
// units of time per sec returned by timeGetTime()
#define UNITS_PER_SEC   1000
// fps maximum - should be > flicker fusion threshold
#define FPS_MAX          200
// minimum elapsed time for updating to the next frame
#define MIN_ELAPSED_TIME UNITS_PER_SEC/FPS_MAX

// Window Dimensions
#define WND_WIDTH  800   // minimum window width
#define WND_HEIGHT 600   // minimum window height

// Sound Directory
#define AUDIO_DIRECTORY L"..\\..\\audio"

// Texture Directory
#define TEXTURE_DIRECTORY L"..\\..\\textures"

// Map Directory
#define MAP_DIRECTORY L"..\\..\\maps"

// AKV
#define TRAPS_MAP_FILE L"Stage2V2-Traps.txt"

#define FONT_DIRECTORY L"..\\..\\fonts"

// NULL address
#define NULL 0

// Maximum string length throughout
#define MAX_DESC 255

// AKV - max number of traps
#define MAX_TRAPS 50

// Sizes of context arrays
//
#define MAX_INTEGERS     35
#define MAX_VECTORS       4
#define MAX_BOOL_ARRAYS   3
#define MAX_INT_ARRAYS    4
#define MAX_STR_ARRAYS    8
#define MAX_ADAPTERS     10
#define MAX_MODES        50
#define MAX_P_FORMATS    20
#define MAX_KEYS        256
#define MAX_M_BUTTONS     3
#define MAX_C_BUTTONS   128
#define MAX_CONTROLLERS  10

typedef enum Integer {
    GF_AU_FREQ,
    GF_AU_MXVL,
    GF_AU_MNVL,
    GF_AU_CVOL,
    GF_DS_ACNT,
    GF_DS_MCNT,
    GF_DS_PCNT,
    GF_DS_ADPT,
    GF_DS_MODE,
    GF_DS_PIXL,
    GF_DS_RINW,
    GF_DS_WDTH,
    GF_DS_HGHT,
    GF_DS_MXLT,
    GF_DS_PXFW,
    GF_WN_WDTH,
    GF_WN_HGHT,
    GF_MS_POSX,
    GF_MS_POSY,
    GF_MS_ORIZ,
    GF_CT_INDX,
    GF_CT_TGRB,
    GF_CT_FLGS,
    GF_CT_CCNT,
    GF_CT_BCNT,
    GF_CT_DSPX,
    GF_CT_DSPY,
    GF_CT_DSPZ,
    GF_CT_ROTZ,
    GF_NO_ACTS,
    GF_NO_KEYS,
    GF_NO_SNDS,
    GT_XX_XXXX
} Integer;

typedef enum VectorId {
    GF_CA_POSN,
    GF_CA_HEAD,
    GF_CA_UP,
    GF_LT_BKGD
} VectorId;

typedef enum BoolArray {
    GF_KB_KEYS, // key states
    GF_MS_BTNS, // mouse button states
    GF_CT_BTNS  // controller button states
} BoolArray;

typedef enum IntArray {
    GF_TRGRBUTN,  // trigger buttons
    GF_KEYCODES  // key codes
} IntArray;

typedef enum StrArray {
    GF_ADPDESC, // adapter descriptions
    GF_MDEDESC, // mode descriptions
    GF_CTRDESC, // controller descriptions
    GF_CTBDESC, // controller button descriptions
    GF_ACTDESC, // action descriptions
    GF_KEYDESC, // key descriptions
    GF_SNDDESC, // sound descriptions
    GF_SNDFILE  // sound file names
} StrArray;

// mappable keys for configurable actions (do not initialize these constants)
//
typedef enum Key { 
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_SPACE,
    KEY_ENTER,
    KEY_UP   ,
    KEY_DOWN, 
    KEY_PGUP, 
    KEY_PGDN, 
    KEY_LEFT, 
    KEY_RIGHT,
    KEY_NUM1,
    KEY_NUM2,
    KEY_NUM3,
    KEY_NUM4,
    KEY_NUM5,
    KEY_NUM6,
    KEY_NUM7,
    KEY_NUM8,
    KEY_NUM9,
    KEY_ESCAPE,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_O_BRACKET,
	KEY_C_BRACKET,
	KEY_BACKSLASH,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_TIMES,
	KEY_GRAVE,
	KEY_MINUS,
	KEY_UNDERSCORE,
	KEY_EQUALS,
	KEY_PLUS
} Key;

// mappable keys for configurable actions as listed in the user dialog
//
#define KEY_DESCRIPTIONS {\
	L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", \
	L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", L"T", \
	L"U", L"V", L"W", L"X", L"Y", L"Z", \
	L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"0", \
	L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", \
	L"F8", L"F9", L"F10", L"F11", L"F12", \
	L"Space", L"Enter", L"Up", L"Down", L"PageUp", L"PageDown", \
	L"Left", L"Right", \
	L"NumPad 1", L"NumPad 2", L"NumPad 3", L"NumPad 4", L"NumPad 5", \
	L"NumPad 6", L"NumPad 7", L"NumPad 8", L"NumPad 9", \
	L"Escape", L";", L"'", L"[", L"]", L"\\", L",", \
	L".", L"/", L"*", L"`", L"-", L"_", L"=", L"+" \
}

// Actions
//
// to add an action
// - add the enumeration constant for the new action
// - add the friendly description of the new action
// - reset MAX_DESC above if necessary 
// - add the default key for the new action
//
// enumeration constants
typedef enum Action {
	TENTH_FLOOR_STARTOVER,
	TENTH_FLOOR_TEST_HASTE,
	TENTH_FLOOR_TEST_DEXTERITY,
    TENTH_FLOOR_TEST_REVERT_COLLAPSING,
    TENTH_FLOOR_TEST_STOP_COLLAPSING,
    MDL_NEW_LIGHT,
	CAM_PITCH_UP,
	CAM_PITCH_DOWN,
	TENTH_FLOOR_PLAYER_TURN_LEFT,
	TENTH_FLOOR_PLAYER_TURN_RIGHT,
	TENTH_FLOOR_PLAYER_ADVANCE,
	TENTH_FLOOR_PLAYER_RETREAT,
	AUD_BKGRD,
	AUD_IMPLS,
	AUD_VOLUME_INC,
	AUD_VOLUME_DEC,
	AUD_SPEED_UP,
	AUD_SLOW_DOWN,
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_DISTANT,
    LIGHT_CLONE,
	HUD_DISPLAY,
	HUD_LEFT,
	HUD_RIGHT,
	HUD_UP,
	HUD_DOWN,
    CAMERA_SELECT
} Action;

// user friendly descriptions of actions
//
#define ACTION_DESCRIPTIONS {\
	L"Start Over",   \
	L"Test haste item",\
	L"Test dexterity item", \
    L"Test revert collapsing item", \
    L"Test stop collapsing item", \
    L"Clone SpotLight", \
	L"Pitch Up",     \
	L"Pitch Down",   \
	L"Yaw Left",     \
	L"Yaw Right",    \
	L"Move Camera Forward",     \
	L"Move Camera Backward",    \
	L"Toggle Background Sound", \
	L"Explosion Sound", \
	L"Increase Volume", \
	L"Decrease Volume", \
	L"Speed Up Sound",  \
	L"Slow Down Sound", \
	L"Toggle Point Light",   \
	L"Toggle Spot Light",    \
	L"Toggle Distant Light", \
    L"Toggle Cloned Light", \
	L"Toggle Heads Up Display",      \
	L"Heads Up Display - Move Left", \
	L"Heads Up Display - Move Right",\
	L"Heads Up Display - Move Up",   \
	L"Heads Up Display - Move Down",  \
    L"Select Camera" \
}

// initial mappings of actions to keys
//
#define ACTION_MAPPINGS {KEY_R, KEY_1, KEY_2, KEY_3, KEY_4, KEY_Z, KEY_PGUP, KEY_PGDN,\
	KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_F3, KEY_F4, KEY_F6, \
	KEY_F7, KEY_UP, KEY_DOWN, KEY_J, KEY_K, KEY_L, KEY_H, KEY_F, KEY_D,   \
	KEY_G, KEY_E, KEY_V, KEY_C}

// Mouse Buttons
//
typedef enum MouseButton {
    LEFT_BUTTON,
    RIGHT_BUTTON
} MouseButton;

// Controller Buttons
//
typedef enum CntlrButton {
    TRIGGER,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9,
    BUTTON_10,
    NORTH,
    EAST,
    WEST,
    SOUTH
} CntrlrButton;

// Graphics Primitive Types
//
typedef enum PrimitiveType {
    POINT_LIST     = 1,
    LINE_LIST      = 2,
    LINE_STRIP     = 3,
    TRIANGLE_LIST  = 4,
    TRIANGLE_STRIP = 5,
    TRIANGLE_FAN   = 6
} PrimitiveType;

// AKV - Projectile Types
//
typedef enum ProjectileType {
	DOUBLE_EDGE_SPEAR = 1,
    CROSS = 2,
	STAR = 3,
	DIAGONAL_LTR = 4,
	DIAGONAL_RTL = 5,
	PIECE_WISE = 6
} ProjectileType;

// Sound Types
//
typedef enum SoundType {
    LOCAL_SOUND,  // stationary 3D
	MOBILE_SOUND, // mobile 3D
    GLOBAL_SOUND  // ambient
} SoundType;

// Light Types
//
typedef enum LightType {
    POINT_LIGHT,
    SPOT_LIGHT,
    DIRECTIONAL_LIGHT
} LightType;

// Model Sounds
//
// to add a configurable sound
// - add its enumeration constant
// - add its description
// - add the default filename for the sound
// - reset MAX_DESC in Configuration.h if necessary 
//
typedef enum ModelSound {
	SND_CEILING_COLLAPSE,
	SND_CEILING_COLLAPSE_DISTANT,
	SND_CURE, 
	SND_DEAF, 
	SND_DEAF_CURED,
	SND_ENVIRONMENTAL,
	SND_FOOT_STEP_TYPE_A,
	SND_FOOT_STEP_TYPE_B,
	SND_FOOT_STEP_TYPE_C,
	SND_FOOT_STEP_TYPE_D,
	SND_FOOT_STEP_TYPE_E,
	SND_FOOT_STEP_TYPE_F,
	SND_GHOST_TRICKS,
	SND_HASTE,
	SND_MACHINE_TURNED_OFF_DISTANT,
	SND_MACHINE_TURNED_ON_DISTANT,
	SND_SCARY_VOICE,
	SND_SCARY_VOICE_FEMALE,
	SND_SCARY_VOICE_MALE,
	SND_SCREAM_FEMALE,
	SND_STAMINA_GAINED,
	SND_TIME_OUT
} ModelSound;

// friendly descriptions of configurable sounds as listed in the user dialog 
//
#define SOUND_DESCRIPTIONS {\
	L"Ceiling collapse near",\
	L"Ceiling collapse distant",\
	L"Player cured",\
	L"Player gets deaf",\
	L"Player cured from deaf",\
	L"Environmental sound - windy cave",\
	L"Player footstep left",\
	L"Player footstep right",\
	L"Player footstep strong left",\
	L"Player footstep strong right",\
	L"Player footstep weak left",\
	L"Player footstep weak right",\
	L"Ghost giggling",\
	L"Haste effect",\
	L"Machine turned off in distant",\
	L"Machine turned on in distant",\
	L"Scary voice",\
	L"Scary voice - female",\
	L"Scary voice - male",\
	L"Scream - female",\
	L"Time out"\
}

// initial selection of configurable sounds 
//
// include the authors name for CCS+ accreditation
//
#define SOUND_MAPPINGS {\
	L"TenthFloorCeilingCollapse.wav",\
	L"TenthFloorCeilingCollapseDistant.wav",\
	L"TenthFloorCure.wav",\
	L"TenthFloorDeaf.wav",\
	L"TenthFloorDeafCured.wav",\
	L"TenthFloorEnvironmental.wav",\
	L"TenthFloorFootStepTypeA.wav",\
	L"TenthFloorFootStepTypeB.wav",\
	L"TenthFloorFootStepTypeC.wav",\
	L"TenthFloorFootStepTypeD.wav",\
	L"TenthFloorFootStepTypeE.wav",\
	L"TenthFloorFootStepTypeF.wav",\
	L"TenthFloorGhostTricks.wav",\
	L"TenthFloorHaste.wav",\
	L"TenthFloorMachineTurnedOffDistant.wav",\
	L"TenthFloorMachineTurnedOnDistant.wav",\
	L"TenthFloorScaryVoice.wav",\
	L"TenthFloorScaryVoiceFemale.wav",\
	L"TenthFloorScaryVoiceMale.wav",\
	L"TenthFloorScreamFemale.wav",\
	L"TenthFloorStaminaGained.wav",\
	L"TenthFloorTimeOut.wav"\
}

// Dialog options
//
// default adapter selection
#define RUN_IN_WINDOW_DESC L"Run in a window"
#define RESOLUTION_DESC    L""
// default controller
#define NO_CONTROLLER_DESC L"No Controller"
#define TRIGGER_DESC       L""

// Text alignment flags
//
#define TXT_LEFT    1
#define TXT_RIGHT   2
#define TXT_CENTER  4
#define TXT_TOP     8
#define TXT_BOTTOM 16
#define TXT_MIDDLE 32
#define TXT_DEFAULT TXT_LEFT | TXT_TOP

// Texture filtering flags
//
#define TEX_MIN_POINT        1
#define TEX_MIN_LINEAR       2
#define TEX_MIN_ANISOTROPIC  4
#define TEX_MAG_POINT        8
#define TEX_MAG_LINEAR      16
#define TEX_MAG_ANISOTROPIC 32
#define TEX_DEFAULT TEX_MIN_LINEAR | TEX_MAG_LINEAR

// sprite modulation colour for the HUD texture [0,255]
//
#define SPRITE_R 255
#define SPRITE_G 255
#define SPRITE_B 255

// display background colour
//
#define BGROUND_R 200
#define BGROUND_G 200
#define BGROUND_B 200

// projection frustum properties
//
#define NEAR_CLIPPING 1.0f   // in model units
#define FAR_CLIPPING  2000.f // in model units 
#define FIELD_OF_VIEW 0.9f   // in radians

// font display colour [0,255]
//
#define TXT_R 255
#define TXT_G 255
#define TXT_B 255
#define TXT_A 255

// sound parameters
//
#define INTERIOR_CONE               0.67f // in radians
#define SOUND_DISTANCE_FACTOR       1.0f  // metres per model unit
#define ATTENUATION_DISTANCE_FACTOR 10    // where attenuation begins

// Fog settings
//

//fog start and end
#define FOGSTART_DEFAULT 10.0f //fog start distance from player
#define FOGEND_DEFAULT  50.0f //fog depth - lower value for thicker
#define FOGSTART_THICK 5.0f
#define FOGEND_THICK  10.0f
#define FOGSTART_THIN 10.0f
#define FOGEND_THIN  100.0f

//fog colors
#define FOGCOLOR_DEFAULT D3DCOLOR_XRGB(128,128,128)
#define FOGCOLOR_BLOODMIST D3DCOLOR_XRGB(51,0,0)

#define FOGCOLOR_BLACK D3DCOLOR_XRGB(0,0,0)
#define FOGCOLOR_WHITE D3DCOLOR_XRGB(255,255,255)
#define FOGCOLOR_BROWN D3DCOLOR_XRGB(102,51,0)

#define FOGCOLOR_RED D3DCOLOR_XRGB(255,0,0)
#define FOGCOLOR_ORANGE D3DCOLOR_XRGB(255,51,0)
#define FOGCOLOR_YELLOW D3DCOLOR_XRGB(255,255,0)
#define FOGCOLOR_GREEN D3DCOLOR_XRGB(0,255,0)
#define FOGCOLOR_BLUE D3DCOLOR_XRGB(0,0,255)
#define FOGCOLOR_PURPLE D3DCOLOR_XRGB(128,0,128)

#endif


