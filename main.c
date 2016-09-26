#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <xcb/xcb.h>


/* print names of modifiers according to given bitmask */

void print_modifiers (uint32_t mask) {
        const char *MODIFIERS[] = {
                "Shift", "Lock", "Ctrl", "Alt",
                "Mod2", "Mod3", "Mod4", "Mod5",
                "Button1", "Button2", "Button3", "Button4", "Button5"
        };

        printf ("Modifier mask: ");
        for (const char **modifier = MODIFIERS ; mask; mask >>= 1, ++modifier) {
                if (mask & 1)
                        printf (*modifier);
        }
        printf ("\n");
        return;
}

int main() {
        /* Open the connection to X server */
        xcb_connection_t *connection = xcb_connect(NULL,NULL);

        /* Get the 1st screen */
        xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup (connection)).data;

        /* Create the window */
        xcb_window_t window = xcb_generate_id (connection);

        uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t values[2] = {screen->white_pixel,
                              XCB_EVENT_MASK_EXPOSURE       |
                              XCB_EVENT_MASK_BUTTON_PRESS   |
                              XCB_EVENT_MASK_BUTTON_RELEASE |
                              XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                              XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE };

        xcb_create_window (connection,
                       0,                             /* depth               */
                       window,
                       screen->root,                  /* parent window       */
                       0, 0,                          /* x, y                */
                       150, 150,                      /* width, height       */
                       10,                            /* border_width        */
                       XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                       screen->root_visual,           /* visual              */
                       mask, values ); /* masks */

        /* Map the window on the screen */
        xcb_map_window (connection, window);

        xcb_flush (connection);


        return 0;
}
