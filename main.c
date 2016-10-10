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

    /*........*/

    KeySym	oldsym, symbol;
    int	nF2Keycode;

    /*........*/
    oldsym = XStringToKeysym ("A");
    symbol = XStringToKeysym ("B");
    nF2Keycode = XKeysymToKeycode (display, oldsym);
    XChangeKeyboardMapping (display, nF2Keycode, 1, &symbol, 1);

    XFlush(display);
    XCloseDisplay(display);
    return 0;
}