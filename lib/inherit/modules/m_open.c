#include "include/m_lock.h"
#include "include/m_description.h"

private int opened;

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

varargs int can_close(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

// TODO: Move all those checks in the can_open() function
varargs mixed event_open(object who) {
    if (!can_open()) {
        return notify_fail("You can't open that.\n");
    }
    if (is_locked()) {
        return notify_fail("It is locked.\n");
    }
    if (opened) {
        return notify_fail("It is open already.\n");
    }
    if (TO->is_door()) {
        write("You open the door.\n");
    }
    else {
        write("You open " + TO->query_short() + ".\n");
    }
    opened = 1;
    return 1;
}

varargs mixed event_close(object who) {
    if (!can_close()) {
        return notify_fail("You can't close that.\n");
    }
    if (!opened) {
        return notify_fail("It is closed already.\n");
    }
    if (TO->is_door()) {
        write("You close the door.\n");
    }
    else {
        write("You close " + TO->query_short() + ".\n");
    }
    opened = 0;
    return 1;
}
