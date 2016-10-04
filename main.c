#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

int main(int argc, char **argv) {
    KeySym old, new;
    int old_code;
    Display *display;
    if (!(display = XOpenDisplay("")) ) {
        fprintf(stderr, "Can't open display %s\n", XDisplayName(""));
        return 1;
    }

    while (argc > 1) {
        old = XStringToKeysym(*argv++);
        new = XStringToKeysym(*argv++);
        argc--, argc--;
        old_code = XKeysymToKeycode(display, old);
        XChangeKeyboardMapping(display, old_code, 1, &new, 1);
    }
    XFlush(display);
    XCloseDisplay(display);
    return 0;
}