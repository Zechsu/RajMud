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
    if (opened) {
        return notify_fail("It is opened already.\n");
    }
    return 1;
}

varargs int can_close(object who) {
    if (!who) {
        who = this_player();
    }
    if (!opened) {
        return notify_fail("It is closed already.\n");
    }
    return 1;
}

varargs mixed event_open(object who) {
    if (!can_open()) {
        return 0;
    }
    write("You open " + TO->query_short() + ".\n");
    opened = 1;
    return 1;
}

varargs mixed event_close(object who) {
    if (!can_close()) {
        return notify_fail("You can't close that.\n");
    }
    write("You close " + TO->query_short() + ".\n");
    opened = 0;
    return 1;
}
