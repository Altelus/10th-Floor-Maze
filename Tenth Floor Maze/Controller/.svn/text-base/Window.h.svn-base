#ifndef _WINDOW_H_
#define _WINDOW_H_

/* Window Declaration - Window Component - Windowing Branch
 *
 * Window.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iWindow.h" // for the Window Interface

//-------------------------------- Window -------------------------------------
//
// The Window Component manages the main application window
//
class Window : public iWindow {

    static iWindow* address; // points to this object

    iContext* context;       // points to the Context object
    void*     hinst;         // points to application Instance
    void*     hwnd;          // points to the main application window
	int       show;          // how to display the application window
    int       width;         // window width
    int       height;        // window height
    int       wndStyle;      // window style
    int       wndExStyle;    // window style extension

    Window(void*, int, iContext*);
	Window(const Window&);
	Window& operator=(const Window&);
    virtual ~Window();

  public:
    friend iWindow* CreateMainWindow(void*, int, iContext*);
    static iWindow* Address() { return address; }
	// initialization function
    void*  setup();
	// execution functions
	bool   handleMessage(int& rc, bool& keepgoing) const;
	void   wait() const;
	void   resize() const;
	void   moveToForeground() const;
    void   messageBox(const wchar_t*) const;
	// termination functions
    void   release();
	void   Delete() const { delete this; }
};

iWindow* WindowAddress() { return Window::Address(); }

#endif