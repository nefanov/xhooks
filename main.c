#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

/* this function replaces an old symbol in the X keyboard map with the new one */
int chande_sym(const char* old,const char* new) {
    Display *display;
    if (!(display = XOpenDisplay("")) ) {
        fprintf(stderr, "Can't open display %s\n", XDisplayName(""));
        return 1;
    }
    
    int	nF2Keycode;

    KeySym oldsym = XStringToKeysym (old);
    KeySym symbol = XStringToKeysym (new);
    nF2Keycode = XKeysymToKeycode (display, oldsym);
    XChangeKeyboardMapping (display, nF2Keycode, 1, &symbol, 1);

    XFlush(display);
    XCloseDisplay(display);
    return 0;
}
