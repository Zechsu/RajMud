#include <lib.h>
#include <modules.h>

inherit LIB_CONTAINER;
inherit M_OPEN;
inherit M_LOCK;

void create() {
    ::create();
}

varargs int can_open(object who) {
    if (!who) {
        who = this_player();
    }
    if (is_locked()) {
        return notify_fail("It is locked.\n");
    }
    return m_open::can_open(who);
}

int can_put(object who) {
    if (!is_open()) {
        return notify_fail("It is closed.\n");
    }
    return container::can_put();
}

varargs mixed event_look_in(object who) {
    if (!is_open()) {
        return notify_fail("It is closed.\n");
    }
    return container::event_look_in(who);
}