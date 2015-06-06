#ifndef _WINDOW_SETTINGS_H_
#define _WINDOW_SETTINGS_H_

/* Header for Configuring the Components of the Window Branch
 *
 * WindowSettings.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "Configuration.h" // application-wide configuration settings
#include "ModelSystem.h"   // for MODEL_Z_AXIS, NEAR_TO_FAR, FAR_TO_NEAR

// shared with dialog resource (follows windows conventions)
//
#define IDD_DLG 101
#define IDC_DIS 102
#define IDC_RES 103
#define IDC_GO  104
#define IDC_KEY 105
#define IDC_ACT 106
#define IDC_CNT 107
#define IDC_TRG 108
#define IDC_YRV 109
#define IDC_ZON 110
#define IDC_AUD 111
#define IDC_SFL 112

#define IDD_10THDLG 201
#define IDB_BGIMAGE 202
#define IDC_MOD 203


// Windowing parameters
//

#define CLASS_NAME    L"Tenth Floor Maze (powered by fwk4gps)"
#define RUN_IN_WINDOW -1
#define NO_CONTROLLER -1

// Window captions
//
#if Z_AXIS == NEAR_TO_FAR
#define WND_NAME L"Tenth Floor Maze (powered by fwk4gps - Z Axis Near to Far)"
#elif Z_AXIS == FAR_TO_NEAR
#define WND_NAME L"Tenth Floor Maze (powered by fwk4gps - Z Axis Far to Near)"
#endif
#define DLG_NAME L"Tenth Floor Maze - fwk4gps"

// Window styles
//
#define WND_STYLE_W   WS_OVERLAPPEDWINDOW
#define WND_EXSTYLE_W 0
#define WND_STYLE     WS_POPUP
#define WND_EXSTYLE   WS_EX_TOPMOST

#endif
