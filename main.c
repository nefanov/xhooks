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

        return 0;
}
