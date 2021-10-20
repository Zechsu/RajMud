#include <globals.h>

int opened;

int is_open() {
    return opened;
}

void toggle_opened() {
    opened = !opened;
}

varargs int can_open(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

// TODO: Figure out if can_open() should be called inside the event.
int event_open() {
    if (can_open()) {
        if (!opened) {
            opened = 1;
            return 1;
        }
    }
    return 0;
}

int event_close() {
    if (opened) {
        opened = 0;
        return 1;
    }
    return 0;
}
