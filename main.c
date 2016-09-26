#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <xcb/xcb.h>

#define GLOB_KEY_DUMMY 'E'
#define GLOB_KEY_DUMMY_REL 'K'

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
                        printf ("%s",*modifier);
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

        /* event processing */

        xcb_generic_event_t *event;

        /* loop: while is connection - waiting for the event, triggering the event according to its type */

    while ( (event = xcb_wait_for_event (connection)) ) {
        switch (event->response_type & ~0x80) {
            case XCB_EXPOSE: {
                xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

                printf ("Window %"PRIu32" exposed. Region to be redrawn at location (%"PRIu16",%"PRIu16"), with dimension (%"PRIu16",%"PRIu16")\n",
                        expose->window, expose->x, expose->y, expose->width, expose->height );
                break;
            }

            case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;

                printf ("Mouse moved in window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                        motion->event, motion->event_x, motion->event_y );
                break;
            }
            case XCB_ENTER_NOTIFY: {
                xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;

                printf ("Mouse entered window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                        enter->event, enter->event_x, enter->event_y );
                break;
            }
            case XCB_LEAVE_NOTIFY: {
                xcb_leave_notify_event_t *leave = (xcb_leave_notify_event_t *)event;

                printf ("Mouse left window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                        leave->event, leave->event_x, leave->event_y );
                break;
            }
            case XCB_KEY_PRESS: {
                xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
                print_modifiers(kp->state);
                /* print info */
                printf ("Key %d pressed in window %"PRIu32"\n",kp->detail, kp->event);
                kp->detail = GLOB_KEY_DUMMY;
                /* check: */
                printf ("Symbol %d: changed in window %"PRIu32"\n",kp->detail, kp->event);
                break;
            }
            case XCB_KEY_RELEASE: {
                xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
                print_modifiers(kr->state);

                printf ("Key %d released in window %"PRIu32"\n",kr->detail, kr->event);
                kr->detail = GLOB_KEY_DUMMY_REL;
                /* check: */
                printf ("Symbol %d: changed in window %"PRIu32"\n",kr->detail, kr->event);
                break;
            }
            default:
                /* Unknown event type, ignore it */
                printf ("Unknown event: %"PRIu8"\n",
                        event->response_type);
                break;
        }

        free (event);
    }

    return 0;
}

