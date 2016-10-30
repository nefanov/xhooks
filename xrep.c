#include <stdio.h>
#include <X11/Xlib.h>

/* this function replaces an old symbol in the X keyboard map with the new one */
int change_sym(char* old,char* new);

/* EP for table replace*/
int change_table(char** old, char** new, size_t len) {
    int i;
    for (i=0;i<len;i++)
        if(change_sym(old[i],new[i]))
            return 1;
    return 0;
}

/* change_sym implementation */
int change_sym(char* old,char* new) {
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
