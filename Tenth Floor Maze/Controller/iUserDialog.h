#ifndef _I_USER_DIALOG_H_
#define _I_USER_DIALOG_H_

/* UserDialog Interface - UserDialog Component - Windowing Branch
 *
 * iUserDialog.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iUserDialog --------------------------------
//
// iUserDialog is the Interface to the UserDialog Component
//
class iContext;

class iUserDialog {
  public:
	// initialization functions
    virtual void populateUserDialog(void*)           = 0;
    virtual void populateAdapterList(void*)          = 0;
    virtual void populateActionList(void*)           = 0;
	virtual void populateSoundFileList(void*)        = 0;
    virtual void populateControllerList(void*)       = 0;
	virtual void populateMappableKeyList(void*)      = 0;
	// execution functions
    virtual bool configureContext()                  = 0;
    virtual bool populateAdapterModeList(void*)      = 0;
    virtual void populateControllerObjectList(void*) = 0;
	virtual void showActionMapping(void*)            = 0;
	virtual void updateActionMapping(void*)          = 0;
	virtual void showSoundMapping(void*)             = 0;
	virtual void updateSoundMapping(void*)           = 0;
    virtual bool saveUserChoices(void*)              = 0;
	// termination function
    virtual void Delete() const                      = 0;
	virtual void drawBackgroundImage(void*, void*) = 0;
	virtual void onPaint(void*) = 0;
	virtual void onEraseBkgnd(void*) = 0;
};

extern "C"
iUserDialog* CreateUserDialog(void*, iContext*);

extern "C"
iUserDialog* UserDialogAddress();

#endif