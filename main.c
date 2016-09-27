#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <ctype.h>


int main ()
{
    Display* d = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(d);
    Window curFocus;
    char buf[17];
    KeySym ks;
    XComposeStatus comp;
    int len, revert;

    XGetInputFocus (d, &curFocus, &revert);
    XSelectInput(d, curFocus, KeyReleaseMask|FocusChangeMask);

    for(;;)
    {
        XEvent event;
        XNextEvent(d, &event);
        switch (event.type)
        {
            case FocusOut:
                printf ("Focus changed!\n");
                printf ("Old focus is %d\n", (int)curFocus);
                if (curFocus != root)
                    XSelectInput(d, curFocus, 0);
                XGetInputFocus (d, &curFocus, &revert);
                printf ("New focus is %d\n", (int)curFocus);
                if (curFocus == PointerRoot)
                    curFocus = root;
                XSelectInput(d, curFocus, KeyPressMask|KeyReleaseMask|FocusChangeMask);
                break;

            case KeyPress:

                printf ("Got key!\n");
                len = XLookupString(&event.xkey, buf, 16, &ks, &comp);
                if (len > 0 && isprint(buf[0]))
                {
                    buf[len]=0; // set last byte as null-terminator
                    printf("String is: %s\n", buf);
                }
                else //KeyReleased
                {
                    printf ("Key is: %d\n", (int)ks);
                }

        }

    }
    return 0;
}