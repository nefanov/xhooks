#include <stdio.h>
#include <X11/Xlib.h>
#include "xrep.h"

/* this function replaces an old symbol in the X keyboard map with the new one */
int change_sym(char* old,char* curr);

/* EP for table replace*/
int change_table(vector<char*> old, vector<char*> curr, size_t len) {
    for (int i=0;i<len;i++)
        if(change_sym(old[i],curr[i]))
            return 1;
    return 0;
}

/* change_sym implementation */
int change_sym(char* old,char* curr) {
    Display *display;
    if (!(display = XOpenDisplay("")) ) {
        fprintf(stderr, "Can't open display %s\n", XDisplayName(""));
        return 1;
    }

    int	nrepKeycode;
    KeySym oldsym = XStringToKeysym (old);
    KeySym symbol = XStringToKeysym (curr);
    nrepKeycode = XKeysymToKeycode (display, oldsym);
    XChangeKeyboardMapping (display, nrepKeycode, 1, &symbol, 1);

    XFlush(display);
    XCloseDisplay(display);
    return 0;
}