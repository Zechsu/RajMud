#include <globals.h>

int opened;

int is_locked();

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
mixed event_open() {
    if (!can_open()) {
        return "You can't open that.\n";
    }
    if (is_locked()) {
        return "It is locked.\n";
    }
    if (opened) {
        return "It is open already.\n";
    }
    opened = 1;
    return 1;
}

int event_close() {
    if (opened) {
        opened = 0;
        return 1;
    }
    return 0;
}
