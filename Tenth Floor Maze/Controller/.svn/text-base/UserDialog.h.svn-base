#ifndef _USER_DIALOG_H_
#define _USER_DIALOG_H_

/* UserDialog Declaration - UserDialog Component - Windowing Branch
 *
 * UserDialog.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iUserDialog.h"   // for the UserDialog Interface
#include "Configuration.h" // for MAX_DESC

//-------------------------------- UserDialog ---------------------------------
//
// The UserDialog Component collects configuration information from the user
//
class UserDialog : public iUserDialog {

    static iUserDialog* address; // points to this object

    void*      hinst;         // points to the application Instance
    iContext*  context;       // points to the Context object
    void*      hwnd;          // points to the Dialog Window

    // memory of most recent configuration
    wchar_t display   [MAX_DESC + 1];
    wchar_t resolution[MAX_DESC + 1];
    wchar_t controller[MAX_DESC + 1];
    wchar_t trigger   [MAX_DESC + 1];
    bool    reversey;
    bool    zAxisOn;
    int     action;
    int     sound;
    int     flags;
    UserDialog(void*, iContext* c);
	UserDialog(const UserDialog&);            // prevent copies
	UserDialog& operator=(const UserDialog&); // prevent assignments
	

  public:
    friend iUserDialog* CreateUserDialog(void*, iContext*);
    static iUserDialog* Address() { return address; }
    bool   configureContext();
	// initialization functions
    void   populateUserDialog(void*);
    void   populateAdapterList(void*);
    void   populateActionList(void*);
	void   populateSoundFileList(void*);
    void   populateControllerList(void*);
	void   populateMappableKeyList(void*);
	// execution functions
    bool   populateAdapterModeList(void*);
    void   populateControllerObjectList(void*);
	void   showActionMapping(void*);
	void   updateActionMapping(void*);
	void   showSoundMapping(void*);
	void   updateSoundMapping(void*);
    bool   saveUserChoices(void*);
    void   error(const wchar_t*) const;
	// termination function
	void   Delete() const { delete this; }
	void drawBackgroundImage(void*, void*);
	void onPaint(void*);
	void onEraseBkgnd(void*);
};

iUserDialog* UserDialogAddress() { return UserDialog::Address(); }

#endif