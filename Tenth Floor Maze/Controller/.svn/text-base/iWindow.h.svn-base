#ifndef _I_WINDOW_H_
#define _I_WINDOW_H_

/* Window Interface - Window Component - Windowing Branch
 *
 * iWindow.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

//-------------------------------- iWindow -------------------------------
//
// iWindow is the Interface to the Window Component
//
class iContext;

class iWindow {
  public:
	// initialization function
    virtual void* setup()                                    = 0;
	// execution functions
	virtual bool  handleMessage(int& rc, bool& done) const   = 0;
	virtual void  wait() const                               = 0;
	virtual void  resize() const                             = 0;
	virtual void  moveToForeground() const                   = 0;
    virtual void  messageBox(const wchar_t*) const           = 0;
	// termination functions
    virtual void  release()                                  = 0;
    virtual void  Delete() const                             = 0;
};

extern "C"
iWindow* CreateMainWindow(void*, int, iContext*);

extern "C"
iWindow* WindowAddress();

int time();
const wchar_t* itowc(wchar_t* s, int a);
#endif